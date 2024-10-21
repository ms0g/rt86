#ifndef RAY_H
#define RAY_H

#include "VEC3.H"

typedef vec3 point3;

class ray {
public:
    ray() {}

    ray(const point3& origin, const vec3& direction) : mOrigin(origin), mDirection(direction) {}

    const point3& origin() const  { return mOrigin; }
    
    const vec3& direction() const { return mDirection; }

    point3 at(float t) {
        return mOrigin + (mDirection * t);
    }

private:
    point3 mOrigin;
    vec3 mDirection;
};

#endif