/* Dot product with upwind gradient */
/*
  Copyright (C) 2009 University of Texas at Austin
  
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "error.h"
#include "alloc.h"
#include "decart.h"

#include "upgrad.h"

#ifndef _sf_upgrad_h

typedef struct Sf_Upgrad *sf_upgrad;
/* abstract data type */
/*^*/

#endif

struct Sf_Upgrad {
    int *order;
    unsigned char **update;
    float **ww;
};

static int ndim, nt, ss[3];
static const int *nn;
static float dd[3];
static const float *t0;

static int fermat(const void *a, const void *b)
/* comparison for traveltime sorting from small to large */
{
    float ta, tb;

    ta = t0[*(int *)a];
    tb = t0[*(int *)b];

    if (ta >  tb) return 1;
    if (ta == tb) return 0;
    return -1;
}

sf_upgrad sf_upgrad_init(int mdim        /* number of dimensions */,
			 const int *mm   /* [dim] data size */,
			 const float *d  /* [dim] data sampling */)
/*< initialize >*/
{
    sf_upgrad upg;
    int i;

    if (mdim > 3) sf_error("%s: dim=%d > 3",__FILE__,mdim);

    ndim = mdim;
    nn = mm;

    nt = 1;
    for (i=0; i < ndim; i++) {
	ss[i] = nt;
	nt *= nn[i];
	dd[i] = 1.0/(d[i]*d[i]);
    }

    upg = (sf_upgrad) sf_alloc(1,sizeof(*upg));

    upg->update = sf_ucharalloc2(2,nt);
    upg->ww = sf_floatalloc2(ndim+1,nt);
    upg->order = sf_intalloc(nt);

    return upg;
}

void sf_upgrad_set(sf_upgrad upg, const float *r0 /* reference */)
/*< supply reference >*/
{
    int i, m, it, jt, ii[3], a, b;
    unsigned char *up;
    float t, t2;

    t0 = r0;

    /* sort from small to large traveltime */
    for (it = 0; it < nt; it++) {
	upg->order[it] = it;
    }
    qsort(upg->order, nt, sizeof(int), fermat);
     
    for (it = 0; it < nt; it++) {
	jt = upg->order[it];

	sf_line2cart(ndim,nn,jt,ii);
	up = upg->update[it];
	up[0] = up[1] = 0;
	t = t0[jt];
	upg->ww[it][ndim] = 0.;
	for (i=0, m=1; i < ndim; i++, m <<= 1) {
	    a = jt-ss[i];
	    b = jt+ss[i];
	    if ((ii[i] == 0) || 
		(ii[i] != nn[i]-1 && 1==fermat(&a,&b))) {
		if (b < 0 || b >= nt) continue;
		up[1] |= m;
		t2 = t0[b];
	    } else {
		if (a < 0 || a >= nt) continue;
		t2 = t0[a];
	    }

	    if (t2 < t) {
		up[0] |= m;
		upg->ww[it][i] = (t-t2)*dd[i];
		upg->ww[it][ndim] += upg->ww[it][i];
	    }	    
	}
    }
}

void sf_upgrad_close(sf_upgrad upg)
/*< free allocated storage >*/
{
    free(*(upg->ww));
    free(upg->ww);
    free(*(upg->update));
    free(upg->update);
    free(upg->order);
    free(upg);
}

void sf_upgrad_solve(sf_upgrad upg,
		     const float *rhs /* right-hand side */, 
		     float *x         /* solution */,
		     const float *x0  /* initial solution */)
/*< inverse operator >*/
{
    int it, jt, i, m, j;
    unsigned char *up;
    float num, den;
   
    for (it = 0; it < nt; it++) {
	jt = upg->order[it];

	num = rhs[jt];
	up = upg->update[it];
	den = upg->ww[it][ndim]; /* denominator */

	if (den == 0.) { /* at the source, use boundary conditions */
	    x[jt] = (NULL != x0)? x0[jt]: 0.;
	    continue;
	}

	for (i=0, m=1; i < ndim; i++, m <<= 1) {
	    if (up[0] & m) {
		j = (up[1] & m)? jt+ss[i]:jt-ss[i];		
		num += upg->ww[it][i]*x[j];		
	    }
	}
	
	x[jt] = num/den;
    }
}

void sf_upgrad_inverse(sf_upgrad upg,
		       float *rhs       /* right-hand side */,
		       const float *x   /* solution */,
		       const float *x0  /* initial solution */)
/*< adjoint of inverse operator >*/
{
    int it, jt, i, m, j;
    unsigned char *up;
    float den, w;

    for (it = 0; it < nt; it++) {
	rhs[it] = 0.;
    }
   
    for (it = nt-1; it >= 0; it--) {
	jt = upg->order[it];

	rhs[jt] += x[jt];

	up = upg->update[it];
	den = upg->ww[it][ndim];

	if (den == 0.) { /* at the source, use boundary conditions */
	    rhs[jt] = (NULL != x0)? x0[jt]: 0.;
	} else {
	    rhs[jt] = rhs[jt]/den;
	}

	for (i=0, m=1; i < ndim; i++, m <<= 1) {
	    if (up[0] & m) {
		j = (up[1] & m)? jt+ss[i]:jt-ss[i];
		w = upg->ww[it][i]*rhs[jt];
		rhs[j] += w;
	    }
	}
    }
}

void sf_upgrad_forw(sf_upgrad upg,
		    const float *x /* solution */,
		    float *rhs     /* right-hand side */)
/*< forward operator >*/
{
    int it, jt, i, m, j;
    unsigned char *up;
    float num, x2;
   
    for (it = 0; it < nt; it++) {
	jt = upg->order[it];

	x2 = x[jt];
	up = upg->update[it];
	num = 0.;

	for (i=0, m=1; i < ndim; i++, m <<= 1) {
	    if (up[0] & m) {
		j = (up[1] & m)? jt+ss[i]:jt-ss[i];		
		num += upg->ww[it][i]*(x2-x[j]);		
	    }
	}
	
	rhs[jt] = num;
    }
}

void sf_upgrad_grad(sf_upgrad upg,
		    const float *x /* input */,
		    float **grad   /* gradient */)
/*< forward operator >*/
{
    int it, jt, i, m, j;
    unsigned char *up;
    float x2;
   
    for (it = 0; it < nt; it++) {
	jt = upg->order[it];

	x2 = x[jt];
	up = upg->update[it];

	for (i=0, m=1; i < ndim; i++, m <<= 1) {
	    if (up[0] & m) {
		j = (up[1] & m)? jt+ss[i]:jt-ss[i];		
		grad[i][jt] = x2-x[j];		
	    } else {
		grad[i][jt] = 0.0f;
	    }
	}
    }
}

void sf_upgrad_adj(sf_upgrad upg,
		   float *x         /* solution */,
		   const float *rhs /* right-hand side */)
/*< adjoint operator >*/
{
    int it, jt, i, m, j;
    unsigned char *up;
    float w;

    for (it = 0; it < nt; it++) {
	x[it] = 0.;
    }
   
    for (it = nt-1; it >= 0; it--) {
	jt = upg->order[it];
	up = upg->update[it];

	for (i=0, m=1; i < ndim; i++, m <<= 1) {
	    if (up[0] & m) {
		j = (up[1] & m)? jt+ss[i]:jt-ss[i];
		w = upg->ww[it][i]*rhs[jt];

		x[jt] += w;
		x[j]  -= w;
	    }
	}
    }
}

void sf_upgrad_grad_adj(sf_upgrad upg,
			float *x     /* output */,
			float **grad /* gradient */)
/*< adjoint gradient operator >*/
{
    int it, jt, i, m, j;
    unsigned char *up;
    float w;

    for (it = 0; it < nt; it++) {
	x[it] = 0.;
    }
   
    for (it = nt-1; it >= 0; it--) {
	jt = upg->order[it];
	up = upg->update[it];

	for (i=0, m=1; i < ndim; i++, m <<= 1) {
	    if (up[0] & m) {
		j = (up[1] & m)? jt+ss[i]:jt-ss[i];
		w = grad[i][jt];

		x[jt] += w;
		x[j]  -= w;
	    }
	}
    }
}
