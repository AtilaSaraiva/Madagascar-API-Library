project('Madagascar_API','c','cpp','fortran')

subdir('librsf')
subdir('librsfpp')
subdir('librsff90')

install_subdir(meson.build_root()/'librsff90/librsff90.a.p',
        install_dir: 'include',
        strip_directory: true,
        exclude_files: ['depscan.dd', 'fortran.c.o', 'rsff90.dat', 'rsf.f90.o'])

pkg_mod = import('pkgconfig')
pkg_mod.generate(libraries : librsf,
                 version : '3.2',
                 name : 'c_madagapi',
                 filebase : 'c_madagapi',
                 description : 'C lang Madagascar API library for devs')

pkg_mod.generate(libraries : [librsfpp,librsf],
                 version : '3.2',
                 name : 'cpp_madagapi',
                 requires: 'c_madagapi',
                 filebase : 'cpp_madagapi',
                 description : 'C++ lang Madagascar API library for devs')

pkg_mod.generate(libraries : [librsff90,librsf],
                 version : '3.2',
                 name : 'f90_madagapi',
                 requires: 'c_madagapi',
                 filebase : 'f90_madagapi',
                 description : 'Fortran lang Madagascar API library for devs')

## Testing libraries
executable('clip', 'clip.c',
        dependencies: librsf_dep)

executable('clipcpp', 'clip.cc',
        dependencies: [librsfpp_dep, librsf_dep])

# libpgf90 = dependency('pgf90', required: true)
# f90compiler = find_program('gfortran')

executable('clipf90', 'clip.f90',
        dependencies: librsff90_dep,
        link_language : 'fortran')
