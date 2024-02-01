#include <wayland-client.h>

#include <stdint.h>
#include <stdio.h>
#include <string.h>

struct our_state
{
    // ...
    struct wl_compositor *compositor;
    // ...
};

static void registry_handle_global(void *data,
                                   struct wl_registry *wl_registry,
                                   uint32_t name,
                                   const char *interface,
                                   uint32_t version)
{
    struct our_state *state = data;
    if (strcmp(interface, wl_compositor_interface.name) == 0) {
        state->compositor = wl_registry_bind(wl_registry, name, &wl_compositor_interface, 4);
    }

    printf("interface: '%s', version: %d, name: %d\n", interface, version, name);
}

static void registry_handle_global_remove(void *data, struct wl_registry *registry, uint32_t name)
{
    // This space deliberately left blank
}

static const struct wl_registry_listener registry_listener = {
    .global = registry_handle_global,
    .global_remove = registry_handle_global_remove,
};

int main(int argc, char *argv[])
{
    struct our_state state = { 0 };
    struct wl_display *display = wl_display_connect(NULL);
    struct wl_registry *registry = wl_display_get_registry(display);
    wl_registry_add_listener(registry, &registry_listener, NULL);
    wl_display_roundtrip(display);
    return 0;
}
