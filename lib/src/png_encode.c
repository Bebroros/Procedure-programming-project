#include "../include/png_encode.h"


int convert_to_png(struct image *img, char *filename){

    FILE *fp = fopen(filename, "wb");
    if (fp == NULL){
        return -1;
    }

    png_structp png_ptr;
	png_infop info_ptr;
	png_bytep png_row;

    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        fclose(fp);
        return -1;
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_write_struct(&png_ptr, NULL);
        fclose(fp);
        return -1;
    }

	if (setjmp(png_jmpbuf (png_ptr))) {
        png_destroy_write_struct(&png_ptr, NULL);
        fclose(fp);
		return -1;
	}

    png_init_io(png_ptr, fp);

    int width = img->attrs.width;
    int height = img->attrs.height;

    png_set_IHDR(
        png_ptr, 
        info_ptr,  
        width, 
        height,  
        8, 
        PNG_COLOR_TYPE_RGB, 
        PNG_INTERLACE_NONE, 
        PNG_COMPRESSION_TYPE_DEFAULT, 
        PNG_FILTER_TYPE_DEFAULT);

    png_write_info(png_ptr, info_ptr);

    png_row = (png_bytep) malloc(3*width*sizeof(png_byte));
    if (!png_row) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);
        return -1;
    }

    unsigned long red_mask = img->image_ptr->red_mask;
    unsigned long green_mask = img->image_ptr->green_mask;
    unsigned long blue_mask = img->image_ptr->blue_mask;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned long pixel = XGetPixel(img->image_ptr, x, y);
            unsigned char blue = pixel & blue_mask;
            unsigned char green = (pixel & green_mask) >> 8;
            unsigned char red = (pixel & red_mask) >> 16;
            
            png_byte *ptr = &(png_row[x * 3]);
            ptr[0] = red;
            ptr[1] = green;
            ptr[2] = blue;
        }
        png_write_row(png_ptr, png_row);
    }

    png_write_end(png_ptr, NULL);

    free(png_row);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);

    return 0; 
}