project(
  'wlclipblock',
  'c',
  default_options: [
    'warning_level=3',
    'c_std=c2x',
    'default_library=static',
  ],
)

add_project_arguments('-D_DEFAULT_SOURCE', language: 'c')

files = [
  'src/main.c',
]

c_args = [
  '-Wno-pedantic',
  '-Wno-error=unused-function',
  '-Wno-error=unused-parameter',
  '-Wno-error=unused-but-set-parameter',
  '-Wno-error=unused-but-set-variable',
  '-Wno-error=unused-variable',
  '-Wno-error=unused-value',
  '-Wno-error=unused-label',
  '-Wno-error=unused-const-variable',
  '-Wno-error=unused-result',
  # HACK: stop vscode's intellisense from complaining about missing c2x features
  '-include', meson.source_root() / 'c2xcompat.h',
]

funchook_helper = subproject('funchook-helper')
funchook = funchook_helper.get_variable('funchook')

funchook_helper_dep = funchook_helper.get_variable('DEP_FUNCHOOK_HELPER')
distorm_dep = funchook.dependency('distorm')
dl_dep = dependency('dl', include_type: 'system')

wayland_protocols_dep = dependency(
  'wayland-protocols',
  version: '>=1.17',
)
wayland_protocols_dir = wayland_protocols_dep.get_variable('pkgdatadir')

wayland_scanner_dep = dependency('wayland-scanner', native: true)
wayland_scanner = find_program(
  wayland_scanner_dep.get_variable('wayland_scanner'),
  native: true,
)

protocols = {
  'primary-selection-unstable-v1':
    wayland_protocols_dir / 'unstable/primary-selection/primary-selection-unstable-v1.xml',
}

foreach name, path : protocols
  files += custom_target(
    name.underscorify() + '_server_h',
    input: path,
    output: '@BASENAME@-protocol.h',
    command: [wayland_scanner, 'server-header', '@INPUT@', '@OUTPUT@'],
  )
endforeach

wlclipblock = shared_library(
  meson.project_name(),
  files,
  install: true,
  dependencies: [
    funchook_helper_dep,
    distorm_dep,
    dl_dep,
  ],
  link_args: [
    '-Wl,--version-script', meson.project_source_root() / 'version.map',
  ],
  c_args: c_args,
)
