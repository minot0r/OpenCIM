#ifndef CIM_H
#define CIM_H

#include <stdio.h> // FILE*, NULL, printf, frprintf... etc
#include <stdlib.h> // malloc, free, exit... etc
#include <stdint.h> // int8_t, uint8_t... etc
#include <string.h> // memcpy

// Default bmp file header size
#define BM_DEFAULT_FH_SIZE 14
// Default bmp image header size
#define BM_DEFAULT_IH_SIZE 40

#define ERR_FILE_OPEN 1
#define ERR_NO_MEM 2

/*
 * BitMap File header data
 * Contains the header size in bytes => h_size
 *              file size in bytes   => f_size
 */
typedef struct bm_fhd {
    uint16_t h_size;
    uint32_t f_size;
} bm_fhd;

/*
 * BitMap Image header data
 * Contains the image header size in bytes => h_size
 *          the number of bytes per pixel  => bbp
 *          the image width in pixels      => width
 *          the image height in pixels     => height
 */
typedef struct bm_ihd {
    uint16_t h_size;
    uint8_t  bpp;
    uint32_t width;
    uint32_t height;
} bm_ihd;

typedef struct bm_file {
    bm_fhd* file_header;
    bm_ihd* image_header;
    FILE*  file;
} bm_file;

typedef char bm_file_header_object[BM_DEFAULT_FH_SIZE];
typedef char bm_image_header_object[BM_DEFAULT_IH_SIZE];

bm_file* open(char*);
void close(bm_file*);
void display_bm_fh(bm_fhd*);
void display_bm_ih(bm_ihd*);
void paint(bm_file*, char*, void (*)(uint16_t*, uint16_t*, uint16_t*, uint16_t*));
void grayscale(uint16_t*, uint16_t*, uint16_t*, uint16_t*);
void invert1(uint16_t*, uint16_t*, uint16_t*, uint16_t*);


#endif // ifndef CIM_H