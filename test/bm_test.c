#include <stdio.h>
#include "../headers/cim.h"

int main(void) {
    bm_file* file = open("files/graph.bmp");
    display_bm_fh(file->file_header);
    display_bm_ih(file->image_header);
    paint(file, "files/work_output.bmp", invert2);
    close(file);
    return 0;
}