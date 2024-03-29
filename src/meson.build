protocols = {
  'primary-selection-unstable-v1':
    DIR_WAYLAND_PROTOCOLS / 'unstable/primary-selection/primary-selection-unstable-v1.xml',
}

protocol_files = []
foreach name, path : protocols
  protocol_files += custom_target(
    name.underscorify() + '_server_h',
    input: path,
    output: '@BASENAME@-protocol.h',
    command: [PROG_WAYLAND_SCANNER, 'server-header', '@INPUT@', '@OUTPUT@'],
  )
endforeach

shared_library(
  meson.project_name(),
  ['main.c'] + protocol_files,
  install: true,
  dependencies: [
    DEP_FUNCHOOK_HELPER,
    DEP_DISTORM,
    DEP_DL,
  ],
  link_args: [
    '-Wl,--version-script', meson.project_source_root() / 'version.map',
  ],
)
