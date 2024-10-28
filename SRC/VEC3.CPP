#include "VEC3.H"
#include "MATH.H"
#include "BOOL.H"

void normalize(vec3& v) {
    v *= invLen(v);
}

float invLen(const vec3& v) {
    return invSqrt(lenSquared(v));
}

float lenSquared(const vec3& v) {
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

void sadd(vec3& v, float scalar) {
    v.x += scalar;
    v.y += scalar;
    v.z += scalar;
}

float dot(const vec3& v0, const vec3& v1) {
    return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;

}

bool nearZero(const vec3& v) {
    // Return true if the vector is close to zero in all dimensions.
    return (bool)((fabs(v.x) < 1e-8) && (fabs(v.y) < 1e-8) && (fabs(v.z) < 1e-8));
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

vec3 random() {
    return vec3(randf(), randf(), randf());
}

vec3 random(float min, float max) {
    return vec3(randf(min, max), randf(min, max), randf(min, max));
}

vec3 randomUnitVec() {
    while (true) {
        vec3 p = random(-1, 1);
        float lensq = p.x * p.x + p.y * p.y + p.z * p.z;
        
        if (1e-160 < lensq && lensq <= 1) {
            return unit(p);
        }      
    }
}

vec3 randomOnHemisphere(const vec3& normal) {
    vec3 onUnitSphere = randomUnitVec();
    
    if (dot(onUnitSphere, normal) > 0.0) // In the same hemisphere as the normal
        return onUnitSphere;
    
    return -onUnitSphere;
}

vec3 reflect(const vec3& v, const vec3& n) {
    return v - n * 2 * dot(v, n);
}

vec3 refract(const vec3& uv, const vec3& n, float etaiOverEtat) {
    float cos_theta = fmin(dot(-uv, n), 1.0);
    vec3 rayOutPerp = (uv + n * cos_theta) * etaiOverEtat;
        
    vec3 rayOutParallel = n / -invSqrt(fabs(1.0 - lenSquared(rayOutPerp)));
    
    return rayOutPerp + rayOutParallel;
}