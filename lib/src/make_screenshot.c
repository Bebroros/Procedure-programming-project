#include "../include/make_screenshot.h"


struct image make_fullscreen_screenshot() {
    struct image img;
    img.display = NULL;

    Display* display = XOpenDisplay(NULL);
    if (display == NULL) {
        return img;
    }
    img.display = display;
    Window root_display = DefaultRootWindow(display);

    XGetWindowAttributes(display, root_display, &img.attrs);

    img.image_ptr = XGetImage(display, root_display, 0, 0, img.attrs.width, img.attrs.height, AllPlanes, ZPixmap);

    return img;
}

