#include <wayland-client-core.h>
#include <wayland-client.h>

#include <stdio.h>

int main(int arg, char *argv[])
{
    struct wl_display *display = wl_display_connect(NULL);
    if (!display) {
        fprintf(stderr, "Failed to connect to Wayland display.\n");
        return 1;
    }
    fprintf(stderr, "connection established!\n");

    wl_display_disconnect(display);
    return 0;
}
