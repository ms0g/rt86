#ifndef COLOR_H
#define COLOR_H

#include "VEC3.H"

typedef vec3 color;

unsigned char rgb2vga(int r, int g, int b);

unsigned char pixel2vga(const color& pixel);

double linear2gamma(double linearComponent);

#endif