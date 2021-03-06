/* This file is automatically generated. DO NOT EDIT! */

#ifndef _sf_c99_h
#define _sf_c99_h


#include <math.h>


#if !defined (__cplusplus) && !defined(NO_COMPLEX) && defined(__STDC__) && ((__STDC_VERSION__ >= 199901L) || defined(__ICC))


#define SF_HAS_COMPLEX_H


/* The following from C99 - must define for C90 */
#include <complex.h>
#undef I
#ifdef sun
#define I (1.0fi)
#else
#define I _Complex_I
#endif


typedef float complex sf_complex;
typedef double complex sf_double_complex;


#else


#include "kiss_fft.h"
typedef kiss_fft_cpx sf_complex;
typedef struct {
    double r, i;
} sf_double_complex;


#endif


#ifdef SF_HAS_COMPLEX_H


float complex sf_cmplx(float re, float im);
/*< complex number >*/


double complex sf_dcmplx(double re, double im);
/*< complex number >*/


#else


kiss_fft_cpx sf_cmplx(float re, float im);
/*< complex number >*/


sf_double_complex sf_dcmplx(double re, double im);
/*< complex number >*/


#endif


#if !defined(__cplusplus) && !defined(SF_HAS_COMPLEX_H)


#if !defined(hpux) && !defined(__hpux)


float copysignf(float x, float y);
/*< float copysign >*/


#endif


float sqrtf(float x);
/*< float sqrt >*/


float logf(float x);
/*< float log >*/


float log10f(float x);
/*< float log10 >*/


float expf(float x);
/*< float exp >*/


float erff(float x);
/*< float erf >*/


float erfcf(float x);
/*< float erfc >*/


#if !defined(hpux) && !defined(__hpux)


float fabsf(float x);
/*< float fabs >*/


#endif


float fmaxf(float x, float y);
/*< float fmax >*/


float fminf(float x, float y);
/*< float fmin >*/


float floorf(float x);
/*< float floor >*/


float ceilf(float x);
/*< float ceil >*/


float roundf(float x);
/*< round to nearest integer >*/


float fmodf(float x, float y);
/*< float fmod >*/


float cosf(float x);
/*< float cos >*/


float sinf(float x);
/*< float sin >*/


float tanf(float x);
/*< float tan >*/


float acosf(float x);
/*< float acos >*/


float asinf(float x);
/*< float asin >*/


float atanf(float x);
/*< float atan >*/


float atan2f(float x, float y);
/*< float atan2 >*/


float log2f(float x);
/*< float log2 >*/


float coshf(float x);
/*< float cosh >*/


float sinhf(float x);
/*< float sinh >*/


float tanhf(float x);
/*< float tanh >*/


float acoshf(float x);
/*< float acosh >*/


float asinhf(float x);
/*< float asinh >*/


float atanhf(float x);
/*< float atanh >*/


float powf(float x, float y);
/*< float pow >*/


float hypotf(float x, float y);
/*< float hypot >*/


long lrint(double num);
/*< round to integer >*/


long long llround(double num);
/*< round to integer >*/


#if defined(hpux) || defined(__hpux)


long long
strtoll(const char *ptr, const char **endptr, int base);
/*< strtoll replacement >*/


unsigned long long
strtoull(const char *ptr, const char **endptr, int base);
/*< strtoull replacement >*/


#endif


#ifdef sun
extern int finite(double);
#define isfinite(x) finite(x)
#endif


#endif

#endif
