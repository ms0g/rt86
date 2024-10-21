#ifndef COLOR_H
#define COLOR_H

#include "VEC3.H"

typedef vec3 color;

unsigned char rgb2vga(int r, int g, int b);

unsigned char pixel2Vga(const color& pixel);

#endif