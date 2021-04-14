sources = ['cub.cc', 'rsf.cc']

incdirCpp = include_directories('include')


librsfpp = static_library('rsfpp',sources,
                   include_directories: incdirCpp,
                   install : true,
                   dependencies : [librsf_dep])

librsfpp_dep = declare_dependency(include_directories : incdirCpp,
        link_with : librsfpp)
