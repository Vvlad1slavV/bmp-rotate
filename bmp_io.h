#ifndef BMP_ROTATE_BMP_IO_H
#define BMP_ROTATE_BMP_IO_H

#ifndef BMP_IO_H
#define BMP_IO_H
#include "bmp_struct.h"
#include "stdio.h"
enum read_status {
    READ_OK = 100,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER,
    READ_INVALID_PATH
} ;

enum write_status {
    WRITE_OK = 200,
    WRITE_ERROR
} ;

struct image * bmp_malloc();
void bmp_free(struct image* img);
enum read_status from_bmp( FILE* in, struct image* img);
enum write_status to_bmp( FILE* out, struct image const* img );

#endif


#endif //BMP_ROTATE_BMP_IO_H
