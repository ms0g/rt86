#include "VEC3.H"
#include "MATH.H"

void normalize(vec3& v) {
    float length = invLen(v);
    
    v.x *= length;
    v.y *= length;
    v.z *= length;
}

float invLen(const vec3& v) {
    return invSqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

void sadd(vec3& v, float scalar) {
    v.x += scalar;
    v.y += scalar;
    v.z += scalar;
}

float dot(const vec3& v0, const vec3& v1) {
    return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;

}

vec3 cross(const vec3& v0, const vec3& v1) {
    vec3 result;

    result.x = v0.y * v1.z - v0.z * v1.y;
    result.y = v0.z * v1.x - v0.x * v1.z;
    result.z = v0.x * v1.y - v0.y * v1.x;

    return result;
}

vec3 unit(const vec3& v) {
    return v * invLen(v);
}