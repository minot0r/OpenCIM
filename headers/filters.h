#ifndef FILTERS_H
#define FILTERS_H

#include <stdint.h> // int8_t, uint8_t... etc

#define DEFAULT_THRESHOLD 30

void grayscale(uint16_t*, uint16_t*, uint16_t*, uint16_t*);
void invert1(uint16_t*, uint16_t*, uint16_t*, uint16_t*);
void invert2(uint16_t*, uint16_t*, uint16_t*, uint16_t*);
void red_filter(uint16_t*, uint16_t*, uint16_t*, uint16_t*);
void green_filter(uint16_t*, uint16_t*, uint16_t*, uint16_t*);
void blue_filter(uint16_t*, uint16_t*, uint16_t*, uint16_t*);
void red_channel(uint16_t*, uint16_t*, uint16_t*, uint16_t*);
void green_channel(uint16_t*, uint16_t*, uint16_t*, uint16_t*);
void blue_channel(uint16_t*, uint16_t*, uint16_t*, uint16_t*);

#endif // ifndef FILTERS_H