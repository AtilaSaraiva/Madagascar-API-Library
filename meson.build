project('Madagascar_API','c','cpp','fortran')

subdir('librsf')
subdir('librsfpp')
subdir('librsff90')

pkg_mod = import('pkgconfig')
pkg_mod.generate(libraries : [librsf, librsff90, librsfpp],
                 version : '3.2',
                 name : 'madagapi',
                 filebase : 'madagapi',
                 description : 'Madagascar API library for devs')


## Testing libraries
executable('clip', 'clip.c',
        dependencies: librsf_dep)

executable('clipcpp', 'clip.cc',
        dependencies: [librsfpp_dep, librsf_dep])

# libpgf90 = dependency('pgf90', required: true)
f90compiler = find_program('gfortran')

executable('clipf90', 'clip.f90',
        dependencies: librsff90_dep,
        link_language : 'fortran')
