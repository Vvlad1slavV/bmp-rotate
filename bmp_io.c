#include <stdlib.h>
#include <stdio.h>
#include "bmp_io.h"
#include "bmp_struct.h"

struct image* bmp_malloc(){
    return (struct image*) malloc(sizeof(struct image));
}
void bmp_free(struct image* img){
    free(img->data);
    free(img);
}

struct bmp_header* bmp_header_malloc(){
    return (struct bmp_header*) malloc(sizeof(struct bmp_header));
}
void bmp_header_free(struct bmp_header* header){
    free(header);
}

struct bmp_header* create_header (struct image const* img) {
    struct bmp_header *header = bmp_header_malloc();

    header->bfType = 0x4D42;
    header->bfileSize = img->width * img->height * sizeof(struct pixel) + img->height * (img->width % 4) +
                        sizeof(struct bmp_header);
    header->bfReserved = 0;
    header->bOffBits = sizeof(struct bmp_header);
    header->biSize = 40;
    header->biWidth = img->width;
    header->biHeight = img->height;
    header->biPlanes = 1;
    header->biBitCount = 24;
    header->biCompression = 0;
    header->biSizeImage = header->bfileSize - header->bOffBits;
    header->biXPelsPerMeter = 0;
    header->biYPelsPerMeter = 0;
    header->biClrUsed = 0;
    header->biClrImportant = 0;
    return header;
}

enum read_status from_bmp( FILE* input, struct image* img){
    if (!input) { return READ_INVALID_PATH; }
    struct bmp_header* header = bmp_header_malloc();
    fread(header, 1, sizeof (struct bmp_header), input);
    if (header->bfType != 0x4D42) { return READ_INVALID_SIGNATURE; }
    if (header->biBitCount != 24){ return READ_INVALID_BITS; }
    if (header->biSize !=40
        || header->biCompression!=0
            || header->bfileSize != header->bOffBits + header->biSizeImage){
        return READ_INVALID_HEADER;
    }
    uint8_t *file_data = (uint8_t *) malloc(header->biSizeImage);
    fseek(input, header->bOffBits, SEEK_SET);
    fread(file_data, 1, header->biSizeImage, input);
    uint64_t data_size = header->biHeight * header->biWidth * sizeof(struct pixel);
    img->data = (struct pixel *) malloc(data_size);
    img->height = header->biHeight;
    img->width = header->biWidth;
    uint16_t padding = header->biWidth % 4;

    for (size_t row = 0; row < header->biHeight; row++) {
        for (size_t col = 0; col < header->biWidth; col++) {
            size_t i_pixel = row * img->width + col;
            img->data[i_pixel] = *(struct pixel *) ((file_data) + sizeof(struct pixel) * (i_pixel) + padding * row);
        }
    }

    free(file_data);
    bmp_header_free(header);
    return READ_OK;
}

enum write_status to_bmp( FILE* output, struct image const* img ){
    struct bmp_header *header = create_header(img);
    uint64_t padding = img->width % 4;
    uint64_t data_size = (img->width + (padding)) * img->height * sizeof(struct pixel);
    uint8_t *data = malloc(data_size);
    for (size_t row = 0; row < img->height; row++) {
        for (size_t col = 0; col < img->width; col++) {
            size_t pixel_i = row * img->width + col;
            *((struct pixel *) (data + sizeof(struct pixel) * pixel_i + row * padding)) = img->data[pixel_i];
        }
    }
    if(!fwrite(header, 1, sizeof(struct bmp_header), output) ||
       !fwrite(data, 1, (img->width + padding) * img->height * sizeof(struct pixel), output)){
        bmp_header_free(header);
        return WRITE_ERROR;
    }
    bmp_header_free(header);
    return WRITE_OK;
}






