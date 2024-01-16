project(
    'flanterm', 'c',
    version: '0.1',
    default_options: ['warning_level=3']
)

flanterm_inc = include_directories('src')

flanterm = static_library(
    'flanterm',
    'src/flanterm.c',
    'src/backends/fb.c',

    include_directories: flanterm_inc,
)

flanterm_dep = declare_dependency(
    link_with: flanterm,
    include_directories: flanterm_inc,
)
