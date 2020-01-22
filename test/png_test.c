#include <stdio.h>
#include "../headers/cim.h"
#include "../headers/filters.h"

int main(int argc, char* argv[]) {
    if(argc < 2) exit(1);
    png_file* file = png_open(argv[1]);
    display_png_fh(file->file_header);
    return 0;
}
