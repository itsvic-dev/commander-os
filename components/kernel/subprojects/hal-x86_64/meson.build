project(
  'hal-x86_64', 'cpp',
  version: '0.1',
  default_options: ['warning_level=3', 'cpp_std=c++20']
)

hal_common_proj = subproject('hal-common')
hal_common_dep = hal_common_proj.get_variable('hal_common_dep')

hal = static_library(
    'hal-x86_64',

    'src/basic.cpp',

    include_directories: include_directories('inc'),
    dependencies: hal_common_dep,
)

hal_dep = declare_dependency(
    link_with: hal,
    dependencies: hal_common_dep,
)
