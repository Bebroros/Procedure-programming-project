#ifndef PNG_ENCODE_H
#define PNG_ENCODE_H
#include <png.h>
#include <stdlib.h>
#include "make_screenshot.h"
#include <X11/Xutil.h>

int convert_to_png(struct image *img, char *filename);

#endif //PNG_ENCODE_H