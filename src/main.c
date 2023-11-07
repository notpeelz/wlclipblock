#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <funchook.h>
#include <wayland-server.h>
#include <funchook-helper.h>
#include "primary-selection-unstable-v1-protocol.h"

#define str(s) #s

static fhh_hook_state_t wl_resource_post_event_array_hook_state = {};
static void wl_resource_post_event_array_hook(
  struct wl_resource* resource,
  uint32_t opcode,
  union wl_argument* args
) {
  FHH_ASSERT_HOOK_SIG_MATCHES(wl_resource_post_event_array);
  auto func = FHH_GET_ORIGINAL_FUNC(wl_resource_post_event_array);

  if (
    resource != nullptr
    && resource->object.interface != nullptr
    && resource->object.interface->name != nullptr
    && strcmp(resource->object.interface->name, str(wl_registry)) == 0
    && strcmp(args[1].s, str(zwp_primary_selection_device_manager_v1)) == 0
  ) {
    return;
  }

  func(resource, opcode, args);
}

__attribute__((constructor))
static void init() {
  FHH_INSTALL(RTLD_DEFAULT, wl_resource_post_event_array);
}
