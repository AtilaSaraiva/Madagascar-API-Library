sources = ['rsf.f90','fortran.c']

openmp = dependency('openmp', required : false)
librsff90 = static_library('rsff90',sources,
                    include_directories: [incdirC],
                    dependencies : [librsf_dep,cblas,openmp],
                    install : true,
                    c_args : ['-static-libgfortran','-DGFORTRAN','-DNAGf90Fortran'])

librsff90_dep = declare_dependency(link_with : librsff90)
