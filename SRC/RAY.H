#ifndef RAY_H
#define RAY_H

#include "VEC3.H"

class Ray {
public:
    Ray() {}

    Ray(const vec3& origin, const vec3& direction) : mOrigin(origin), mDirection(direction) {}

    const vec3& origin() const  { return mOrigin; }
    
    const vec3& direction() const { return mDirection; }

    vec3 at(double t) const {
        return mOrigin + (mDirection * t);
    }

private:
    vec3 mOrigin;
    vec3 mDirection;
};

#endif