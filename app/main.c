#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include "../lib/include/make_screenshot.h"
#include "../lib/include/png_encode.h"


volatile int running = 1;

void sigint_handler() {
    printf("\nStopping the app\n");
    running = 0;
}


int main() {
    Display* display = XOpenDisplay(NULL);
    if (display == NULL) {
        return 1;
    }

    Window root = DefaultRootWindow(display);

    int key1 = XKeysymToKeycode(display, XK_1);
    int key2 = XKeysymToKeycode(display, XK_3);

    unsigned int modifier = ShiftMask | ControlMask;  
    
    XGrabKey(display, key1, modifier, root, True, GrabModeAsync, GrabModeAsync);
    XGrabKey(display, key2, modifier, root, True, GrabModeAsync, GrabModeAsync);

    signal(SIGINT, sigint_handler);
    XEvent event;
    printf("Press CTRL+C to stop this app.\n");
    while(running) {
        if (XPending(display) > 0) {
            XNextEvent(display, &event);

            if (event.type == KeyPress) {
                struct image *img;
                if (event.xkey.keycode == key1) {
                    img = make_fullscreen_screenshot();
                    printf("Making fullscreen screenshot\n");
                } else if (event.xkey.keycode == key2) {
                    img = make_window_screenshot();
                    printf("Making screenshot of the window\n");
                } else {
                    continue;
                }
                time_t t = time(NULL);
                struct tm tm = *localtime(&t);
                char filename[70];
                sprintf(filename, "screenshot_%04d_%02d_%02d_%02d-%02d-%02d.png", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

                convert_to_png(img, filename);
                XDestroyImage(img->image_ptr);
                XCloseDisplay(img->display);
                free(img);

            }
        }
    }

    XUngrabKey(display, key1, modifier, root);
    XUngrabKey(display, key2, modifier, root);
    XCloseDisplay(display);
}