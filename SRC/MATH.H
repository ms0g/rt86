#ifndef MATH_H
#define MATH_H

#define M_PI 3.14159265358979323846

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

double invSqrt(double n);

#endif