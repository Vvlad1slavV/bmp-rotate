#include <stdio.h>
#include "bmp_io.h"
#include "bmp_struct.h"
#include "util.h"
#include "error.h"
#include "bmp_rotate.h"
#include <stdlib.h>

#define STANDART_OUT_FILE "output.bmp"

void usage() {
    fprintf(stderr, "Usage: ./bmp-rotate input_name.bmp [output_name_1.bmp..output_name_n.bmp]\n");
    exit(1);
}

int main( int argc, char** argv ) {
    if (argc < 2) {
        usage();
        err("Not enough arguments \n" );
    }

    const char *input_path = argv[1];
    const char *output_path;

    struct image *img = bmp_malloc();

    FILE *input_file = fopen(input_path, "rb");
    uint8_t read_status = from_bmp(input_file,img);

    struct status read_descr = descriptions[read_status];
    printf("%s\n",read_descr.err_descr);

    if (read_descr.err_code != 0) exit(read_descr.err_code);
    fclose(input_file);

    struct image* bmp_rotate = rotate(img);
    bmp_free(img);
    if (argc < 3) {
        output_path = STANDART_OUT_FILE;
        FILE *output = fopen(output_path, "wb");
        if (!output) {
            printf("File '%s' acces error\n", output_path);
            exit(1);
        }
        uint8_t write_status = to_bmp(output, bmp_rotate);
        struct status write_descr = descriptions[write_status];
        printf("%s\n",write_descr.err_descr);
        if (read_descr.err_code != 0) printf("%u", read_descr.err_code);
        fclose(output);
    } else {
        for (int i = 2; i < argc; i++) {
            output_path = argv[i];
            FILE *output = fopen(output_path, "wb");
            uint8_t write_status = to_bmp(output, bmp_rotate);
            struct status write_descr = descriptions[write_status];
            printf("%s\n",write_descr.err_descr);
            if (read_descr.err_code != 0) printf("%u", read_descr.err_code);
            fclose(output);
        }
    }
    return 0;
}
