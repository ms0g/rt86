#ifndef MATH_H
#define MATH_H

static inline int min(int n0, int n1) {
    return (n0 < n1) ? n0 : n1;
} 

static inline int max(int n0, int n1) {
    return (n0 > n1) ? n0 : n1;
} 

static inline float fmin(float n0, float n1) {
    return (n0 < n1) ? n0 : n1;
}

static inline float fmax(float n0, float n1) {
    return (n0 > n1) ? n0 : n1;
}

double invSqrt(double n);

#endif