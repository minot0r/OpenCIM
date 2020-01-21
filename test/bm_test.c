#include <stdio.h>
#include "../headers/cim.h"

int main(void) {
    bm_file* file = open("files/399728.bmp");
    display_bm_fh(file->file_header);
    display_bm_ih(file->image_header);
    printf("Computing...\n");
    paint(file, "files/1.bmp", red_filter);
    paint(file, "files/2.bmp", blue_filter);
    paint(file, "files/3.bmp", green_filter);
    paint(file, "files/4.bmp", red_channel);
    paint(file, "files/5.bmp", blue_channel);
    paint(file, "files/6.bmp", green_channel);
    paint(file, "files/7.bmp", grayscale);
    paint(file, "files/8.bmp", invert2);
    close(file);
    printf("Done.\n");
    return 0;
}