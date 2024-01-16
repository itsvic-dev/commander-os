project(
  'kernel', 'cpp',
  version: '0.1',
  default_options: ['warning_level=3', 'cpp_std=c++20']
)

# kernel building setup
add_global_arguments(
  '-ffreestanding',
  '-fno-stack-protector',
  '-fno-stack-check',
  '-fno-lto',
  '-fno-rtti',
  '-m64',
  '-march=x86-64',
  '-mno-80387',
  '-mno-mmx',
  '-mno-sse',
  '-mno-sse2',
  language: 'cpp'
)

limine_inc = include_directories(get_option('limine_inc'))
limine_dep = declare_dependency(
  include_directories: limine_inc,
)

hal_proj = subproject('hal-' + host_machine.cpu())
hal_dep = hal_proj.get_variable('hal_dep')

exe = executable(
  'kernel',
  
  'src/start.cpp',
  'src/basic.cpp',
  'src/cppglue.cpp',

  'src/drivers/fb/liminefb.cpp',

  dependencies: [limine_dep, hal_dep],

  link_args: [
    '-T' + meson.source_root() / 'linker.ld',
    '-nostdlib', '-ffreestanding',
    '-Wl,-z', '-Wl,text',
    '-Wl,-z', '-Wl,max-page-size=0x1000',
  ],
  pie: true,
  link_depends: [
    meson.source_root() / 'linker.ld'
  ],
  include_directories: [
    include_directories('inc'),
  ],
  install: true,
)
