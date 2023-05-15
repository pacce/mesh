project('mesh', 'cpp', version : '0.3.0', default_options : ['warning_level=3', 'cpp_std=c++20'])

includes      = include_directories('include')
dependencies  = [dependency('boost'), dependency('geometry')]

mesh = library(
  meson.project_name()
  , []
  , include_directories : includes
  , dependencies        : dependencies
  , install             : true
  )

mesh_dep = declare_dependency(
  link_with             : mesh
  , include_directories : includes
  , dependencies        : dependencies
  )

if not meson.is_subproject()
  subdir('tests')
endif
