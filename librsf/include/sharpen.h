/* This file is automatically generated. DO NOT EDIT! */

#ifndef _sf_sharpen_h
#define _sf_sharpen_h


void sf_sharpen_init(int n1     /* data size */,
		     float perc /* quantile percentage */,
		     float fact /* multiplicative factor */);
/*< initialize >*/


void sf_sharpen_close(void);
/*< free allocated storage >*/


float sf_sharpen(const float *pp);
/*< compute weight for sharpening regularization >*/


void sf_csharpen(const sf_complex *pp);
/*< compute weight for sharpening regularization >*/

#endif
