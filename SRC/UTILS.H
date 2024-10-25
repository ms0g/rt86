#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

static inline float clamp(float v, float lo, float hi) {
    return v < lo ? lo: v > hi ? hi:v;
}

static inline float randf() {
    return rand() / (RAND_MAX + 1.0);
}

#endif