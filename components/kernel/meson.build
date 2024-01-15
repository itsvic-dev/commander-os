project(
  'kernel', 'cpp',
  version: '0.1',
  default_options: ['warning_level=3']
)

limine_inc = include_directories(get_option('limine_inc'))

exe = executable(
  'kernel', 'kernel.cpp',

  link_args: [
    '-T' + meson.source_root() / 'linker.ld',
    '-nostdlib', '-fPIE', '-ffreestanding',
    '-Wl,-z', '-Wl,text',
    '-Wl,-z', '-Wl,max-page-size=0x1000',
  ],
  cpp_args: [
    '-ffreestanding', '-fno-stack-protector', '-fno-stack-check', '-fno-lto',
    '-fPIE',
    '-m64',
  ],
  link_depends: [
    meson.source_root() / 'linker.ld'
  ],
  include_directories: [
    limine_inc
  ],
  install: true
)
