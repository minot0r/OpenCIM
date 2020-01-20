#include "../headers/cim.h"

bm_file* open(char* file_name) {
    FILE* file_ptr = fopen(file_name, "rb+"); // Open for both reading and writing in binary mode.
    if(file_ptr == NULL) {
        fprintf(stderr, "Error while trying to open %s. Code: %d.", file_name, ERR_FILE_OPEN);
        exit(ERR_FILE_OPEN);
    }

    bm_file_header_object fho;
    fread(&fho, BM_DEFAULT_FH_SIZE, 1, file_ptr);

    bm_fhd* file_header = malloc(sizeof(bm_fhd));
    if(file_header == NULL) {
        fprintf(stderr, "Can't allocate memory for bm_fhd. Code: %d.", ERR_NO_MEM);
        exit(ERR_NO_MEM);
    }
    file_header->h_size = (uint16_t) BM_DEFAULT_FH_SIZE;
    file_header->f_size = *(uint32_t*) &(fho[2]);

    bm_image_header_object iho;
    fread(&iho, BM_DEFAULT_IH_SIZE, 1, file_ptr);

    bm_ihd* image_header = malloc(sizeof(bm_ihd));
    if(image_header == NULL) {
        fprintf(stderr, "Can't allocate memory for bm_ihd. Code: %d.", ERR_NO_MEM);
        exit(ERR_NO_MEM);
    }

    image_header->h_size = *(uint32_t*) &(iho[0]);
    image_header->bpp    = *(uint16_t*) &(iho[14]);
    image_header->width  = *(uint32_t*) &(iho[4]);
    image_header->height = *(uint32_t*) &(iho[8]);

    bm_file* bmfile = malloc(sizeof(bm_file));
    if(bmfile == NULL) {
        fprintf(stderr, "Can't allocate memory for bm_file. Code: %d", ERR_NO_MEM);
        exit(ERR_NO_MEM);
    }

    rewind(file_ptr);

    bmfile->file = file_ptr;
    bmfile->file_header = file_header;
    bmfile->image_header = image_header;

    return bmfile;
}

void close(bm_file* file) {
    fclose(file->file);
    free(file->file_header);
    free(file->image_header);
    free(file);
}

void display_bm_fh(bm_fhd* fhd) {
    printf("Header size: %db\nFile size: %db\n", fhd->h_size, fhd->f_size);
}

void display_bm_ih(bm_ihd* ihd) {
    printf("Header size: %db\nBpP: %db/p\nWidth: %dpx\nHeight: %dpx\n", ihd->h_size, ihd->bpp, ihd->width, ihd->height);
}

void paint(bm_file* file, char* to, void (*func)(uint16_t* r, uint16_t* g, uint16_t* b, uint16_t* a)) {
    FILE* output_file = fopen(to, "wb");
    
    rewind(file->file);

    uint32_t headers_size = file->file_header->h_size + file->image_header->h_size;
    uint8_t* headers_data = malloc(sizeof(uint8_t) * headers_size);
    fread(headers_data, sizeof(uint8_t), headers_size, file->file);
    fwrite(headers_data, sizeof(uint8_t), headers_size, output_file);

    free(headers_data);

    uint8_t padding = (4 - ((file->image_header->width * file->image_header->bpp / 8) % 4)) % 4;

    uint32_t bytes_read = 0;
    uint32_t lines_read = 0;

    while(bytes_read < file->file_header->f_size - headers_size) {
        if(bytes_read == (lines_read + 1) * file->image_header->width * (file->image_header->bpp / 8) + lines_read * padding) {
            uint8_t* zeros = malloc(sizeof(uint8_t) * padding);
            fread(zeros, 1, padding, file->file);
            fwrite(zeros, 1, padding, output_file);
            free(zeros);
            bytes_read += padding;
            lines_read++;
        } else {
            uint8_t size = file->image_header->bpp / 8 % 4 == 0 ? file->image_header->bpp / 32 : file->image_header->bpp / 24;
            uint16_t r, g, b, a = 0;
            fread(&b, size, 1, file->file);
            fread(&g, size, 1, file->file);
            fread(&r, size, 1, file->file);
            if(file->image_header->bpp / 8 % 4 == 0)
                fread(&a, size, 1, file->file);
            
            func(&r, &g, &b, &a);

            fwrite(&b, size, 1, output_file);
            fwrite(&g, size, 1, output_file);
            fwrite(&r, size, 1, output_file);

            if(file->image_header->bpp / 8 % 4 == 0)
                fwrite(&a, size, 1, output_file);

                
            bytes_read += file->image_header->bpp / 8;
        }
        printf("Bytes read %db\n", bytes_read);
    }

    fclose(output_file);
}

void grayscale(uint16_t* r, uint16_t* g, uint16_t* b, uint16_t* a) {
    uint16_t mean = (*r + *g + *b) / 3;
    *r = mean; *g = mean; *b = mean;
}

void invert1(uint16_t* r, uint16_t* g, uint16_t* b, uint16_t* a) {
    uint16_t temp = *r;
    *r = *g; *g = *b; *b = temp;
}

void invert2(uint16_t* r, uint16_t* g, uint16_t* b, uint16_t* a) {
    if(a != 0) {
        *r = *a - *r;
        *g = *a - *g;
        *b = *a - *b;
    } else {
        *r = 255 - *r;
        *g = 255 - *g;
        *b = 255 - *b;
    }
}