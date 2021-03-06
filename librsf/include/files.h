/* This file is automatically generated. DO NOT EDIT! */

#ifndef _sf_files_h
#define _sf_files_h


#include "_bool.h"
#include "file.h"


int sf_filedims (sf_file file, /*@out@*/ int *n);
/*< Find file dimensions.
--- 
Outputs the number of dimensions dim and a dimension array n[dim] >*/


int sf_largefiledims (sf_file file, /*@out@*/ off_t *n);
/*< Find file dimensions.
--- 
Outputs the number of dimensions dim and a dimension array n[dim] >*/


int sf_memsize();
/*< Returns memory size by:
  1. checking RSFMEMSIZE environmental variable
  2. using hard-coded "def" constant
  >*/


off_t sf_filesize (sf_file file);
/*< Find file size (product of all dimensions) >*/


off_t sf_leftsize (sf_file file, int dim);
/*< Find file size for dimensions greater than dim >*/


void sf_cp(sf_file in, sf_file out);
/*< Copy file in to file out >*/


void sf_rm(const char* filename, bool force, bool verb, bool inquire);
/*< Remove an RSF file.
---
force, verb, and inquire flags should behave similar to the corresponding flags in the Unix "rm" command. >*/


off_t sf_shiftdim(sf_file in, sf_file out, int axis);
/*< shift grid after axis by one dimension forward >*/


off_t sf_shiftdim2(sf_file in, sf_file out, int axis);
/*< shift grid after axis by two dimension forward >*/


off_t sf_shiftdimn(sf_file in, sf_file out, int axis, int n);
/*< shift grid after axis by n dimension forward >*/


off_t sf_unshiftdim(sf_file in, sf_file out, int axis);
/*< shift grid after axis by one dimension backward >*/


off_t sf_unshiftdim2(sf_file in, sf_file out, int axis);
/*< shift grid after axis by two dimension backward >*/

#endif
