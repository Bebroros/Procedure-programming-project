#ifndef make_screenshot
#define make_screenshot
#include <X11/Xlib.h>

struct image
{
    Display* display;
    XImage* image_ptr;
    XWindowAttributes attrs;
};

struct image make_fullscreen_screenshot();
struct image make_window_screenshot();

#endif
