#include "../headers/filters.h"

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

void red_filter(uint16_t* r, uint16_t* g, uint16_t* b, uint16_t* a) {
    uint16_t mean = (*r + *g + *b) / 3;
    if(*r < 255 - DEFAULT_THRESHOLD) {
        *r = mean;
    }    
    *g = mean;
    *b = mean;
}

void green_filter(uint16_t* r, uint16_t* g, uint16_t* b, uint16_t* a) {
    uint16_t mean = (*r + *g + *b) / 3;
    if(*g < 255 - DEFAULT_THRESHOLD) {
        *g = mean;
    }    
    *r = mean;
    *b = mean;
}

void blue_filter(uint16_t* r, uint16_t* g, uint16_t* b, uint16_t* a) {
    uint16_t mean = (*r + *g + *b) / 3;
    if(*b < 255 - DEFAULT_THRESHOLD) {
        *b = mean;
    }    
    *g = mean;
    *r = mean;     
}

void red_channel(uint16_t* r, uint16_t* g, uint16_t* b, uint16_t* a) {
    if(*r > 255 - DEFAULT_THRESHOLD) {
        *r = 255;
    } else {
        *r = 0;
    }
    *g = 0;
    *b = 0;
}

void green_channel(uint16_t* r, uint16_t* g, uint16_t* b, uint16_t* a) {
    if(*g > 255 - DEFAULT_THRESHOLD) {
        *g = 255;
    } else {
        *g = 0;
    }
    *r = 0;
    *b = 0;
}

void blue_channel(uint16_t* r, uint16_t* g, uint16_t* b, uint16_t* a) {
    if(*b > 255 - DEFAULT_THRESHOLD) {
        *b = 255;
    } else {
        *b = 0;
    }
    *r = 0;
    *g = 0;
}