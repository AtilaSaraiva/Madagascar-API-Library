sources = '''aastretch.c adjnull.c alloc.c axa.c banded.c bigsolver.c blas.c box.c butter.c c99.c causint.c ccdstep.c ccgstep.c cconjgrad.c ccopy.c cell.c celltrace.c cdstep.c cgstep.c chain.c clist.c cmatmult.c conjgrad.c conjprec.c copy.c cosft.c ctriangle.c ctrianglen.c decart.c deriv.c divn.c dottest.c doubint.c dtrianglen.c edge.c eno.c eno2.c eno3.c error.c fftlabel.c file.c files.c freqfilt.c freqfilt2.c ftutil.c fzero.c gaussel.c getpar.c gmres.c grad2fill.c halfint.c helicon.c helix.c hilbert.c igrad1.c igrad2.c impl2.c int1.c int2.c int3.c interp.c interp_spline.c irls.c komplex.c llist.c lsint2.c mask.c math1.c matmult2.c multidivn.c multidivnL1.c neighbors.c omptools.c parallel.c point.c polydiv.c pqueue.c pweno.c randn.c recfilt.c repeat.c runge.c quantile.c quadratic.c sharpen.c sharpinv.c simtab.c slice.c spline.c stack.c stretch.c stretch4.c system.c tent2.c timer.c tinysolver.c triangle.c triangle1.c triangle2.c trianglen.c tridiagonal.c upgrad.c vector.c wavelet.c weight.c weight2.c kiss_fft.c kiss_fftr.c mt19937ar.c'''.split(' ')


incdirC = include_directories('include')
subdir('include')

cblas = dependency('cblas', required : true)
add_project_arguments(['-DRSF_VERSION="3.2"'], language : 'c')

cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required : true)
librsf = static_library('rsf',sources,
                 include_directories: incdirC,
                 install : true,
                 dependencies : [m_dep, cblas])

librsf_dep = declare_dependency(include_directories : incdirC,
        link_with : librsf)
