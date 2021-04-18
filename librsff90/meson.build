sources = ['rsf.f90','fortran.c']


openmp = dependency('openmp', required : false)
librsff90 = static_library('rsff90',sources,
                    include_directories: [incdirC],
                    dependencies : [librsf_dep,cblas,openmp],
                    install : true,
                    link_language : 'fortran',
                    c_args : ['-DGFORTRAN','-DNAGf90Fortran'],
                    f_args : ['-Mpreprocess','-DGFORTRAN','-DNAGf90Fortran'])

librsff90_dep = declare_dependency(link_with : librsff90)
