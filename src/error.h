#ifndef BMP_ROTATE_ERROR_STATUS_H
#define BMP_ROTATE_ERROR_STATUS_H
#include <stdio.h>
#include "src/bmp_io.h"

struct status { const char* err_descr; const uint8_t err_code; };

static const struct status descriptions[] = {
        [READ_OK] = { "File loaded successfully", 0},
        [READ_INVALID_SIGNATURE] = { "Invalid signature", 101},
        [READ_INVALID_BITS] = { "Only 24-bit bpm file is supported", 102},
        [READ_INVALID_HEADER] = { "File has invalid header", 103},
        [READ_INVALID_PATH] = { "Input file path not found", 104},
        [WRITE_OK] = { "New .BMP file is saved", 0},
        [WRITE_ERROR] = { "Write ERROR", 201}
};


#endif //BMP_ROTATE_ERROR_STATUS_H