#ifndef MATH_H
#define MATH_H

#include <stdlib.h>
#include <math.h>

#define M_PI 3.14159265358979323846

static inline double fabs(double n) {
    return n < 0.0 ? 0.0 - n : n;
}

static inline int min(int n0, int n1) {
    return n1 ^ ((n0 ^ n1) & -(n0 < n1));
} 

static inline int max(int n0, int n1) {
    return n1 ^ ((n0 ^ n1) & -(n0 > n1));
} 

static inline double fmin(double n0, double n1) {
    return (n0 < n1) ? n0 : n1;
}

static inline double fmax(double n0, double n1) {
    return (n0 > n1) ? n0 : n1;
}

static inline double degree2radian(double angle) {
    return angle * M_PI / 180.0;
}

static inline double clamp(double v, double lo, double hi) {
    return v < lo ? lo: v > hi ? hi:v;
}

static inline double randd() {
    return rand() / (RAND_MAX + 1.0);
}

static inline double randd(double min, double max) {
    return min + (max - min) * randd();
}

double invSqrt(double n);

#endif