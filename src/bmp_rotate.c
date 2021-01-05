#include <stdlib.h>
#include <stdio.h>
#include "bmp_rotate.h"

struct image rotate(struct image const img) {
    struct image rotate_img = {};
    rotate_img.height = img.width;
    rotate_img.width = img.height;
    rotate_img.data = (struct pixel *) malloc(img.height * img.width * sizeof(struct pixel));
    for (size_t row = 0; row < img.height; row++) {
        for (size_t col = 0; col < img.width; col++) {
            rotate_img.data[row+((rotate_img.height-col-1) * rotate_img.width)] = img.data[col+row * img.width];
        }
    }
    return rotate_img;
}
