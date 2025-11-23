#include "../include/make_screenshot.h"


struct image* make_fullscreen_screenshot() {
    struct image *img = malloc(sizeof(struct image));
    img->display = NULL;

    Display* display = XOpenDisplay(NULL);
    if (display == NULL) {
        return img;
    }
    img->display = display;
    Window root_display = DefaultRootWindow(display);

    XGetWindowAttributes(display, root_display, &img->attrs);

    img->image_ptr = XGetImage(display, root_display, 0, 0, img->attrs.width, img->attrs.height, AllPlanes, ZPixmap);

    return img;
}

struct image* make_window_screenshot() {
    struct image *img = malloc(sizeof(struct image));

    Display* display = XOpenDisplay(NULL);
    if (display == NULL) {
        return NULL;
    }

    img->display = display;

    Window root_display = DefaultRootWindow(display);

    Window root_returned, child_returned;
    int root_x, root_y, win_x, win_y;
    unsigned int mask;

    XQueryPointer(display, root_display, &root_returned, &child_returned, &root_x, &root_y, &win_x, &win_y, &mask);

    if (child_returned == None) {
        child_returned = root_display;
    }

    XGetWindowAttributes(display, child_returned, &img->attrs);

    img->image_ptr = XGetImage(display, child_returned, 0, 0, img->attrs.width, img->attrs.height, AllPlanes, ZPixmap);

    return img;
}
