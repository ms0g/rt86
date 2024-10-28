#ifndef MATH_H
#define MATH_H

#include <stdlib.h>
#include <math.h>

#define M_PI 3.14159265358979323846

static inline float fabs(float n) {
    return n < 0.0 ? 0.0 - n : n;
}

static inline int min(int n0, int n1) {
    return n1 ^ ((n0 ^ n1) & -(n0 < n1));
} 

static inline int max(int n0, int n1) {
    return n1 ^ ((n0 ^ n1) & -(n0 > n1));
} 

static inline float fmin(float n0, float n1) {
    return (n0 < n1) ? n0 : n1;
}

static inline float fmax(float n0, float n1) {
    return (n0 > n1) ? n0 : n1;
}

static inline float degree2radian(float angle) {
    return angle * M_PI / 180.0;
}

static inline float clamp(float v, float lo, float hi) {
    return v < lo ? lo: v > hi ? hi:v;
}

static inline float randf() {
    return rand() / (RAND_MAX + 1.0);
}

static inline float randf(float min, float max) {
    return min + (max - min) * randf();
}

double invSqrt(double n);

#endif