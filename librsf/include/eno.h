/* This file is automatically generated. DO NOT EDIT! */

#ifndef _sf_eno_h
#define _sf_eno_h


#include "_defs.h"


typedef struct Eno *sf_eno;
/* abstract data type */


typedef enum {FUNC, DER, BOTH} der;
/* flag values */


sf_eno sf_eno_init (int order /* interpolation order */, 
		    int n     /* data size */);
/*< Initialize interpolation object. >*/


void sf_eno_close (sf_eno ent);
/*< Free internal storage >*/


void sf_eno_set (sf_eno ent, float* c /* data [n] */);
/*< Set the interpolation table. c can be changed or freed afterwords >*/


void sf_eno_set_wstride (sf_eno ent, float* c /* data [n] */, int stride);
/*< Set the interpolation table. c can be changed or freed afterwords >*/


void sf_eno_apply (sf_eno ent, 
		int i     /* grid location */, 
		float x   /* offset from grid */, 
		float *f  /* output data value */, 
		float *f1 /* output derivative */, 
		der what  /* flag of what to compute */);
/*< Apply interpolation >*/

#endif
