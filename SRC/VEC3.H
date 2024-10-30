#ifndef VEC_H
#define VEC_H

#include "BOOL.H"
 
struct vec3 {
    double x;
    double y;
    double z;
    
    vec3(): x(0.0), y(0.0), z(0.0) {}
    vec3(double x, double y, double z): x(x), y(y), z(z) {}
    vec3(double* v) : x(v[0]), y(v[1]), z(v[2]) {}
    
    vec3 operator-() const {
        return vec3(-x, -y, -z);
    }

    vec3 operator+(const vec3& other) const {
        return vec3(x + other.x,  y + other.y, z + other.z);
    }

    vec3 operator-(const vec3 &other) const {
        return vec3(x - other.x,  y - other.y, z - other.z);
    }

    vec3 operator*(const vec3& other) const {
        return vec3(x * other.x, y * other.y, z * other.z);
    }

    vec3 operator*(double n) const {
        return vec3(x * n, y * n, z * n);
    }

    vec3 operator/(double n) const {
        return *this * (1/n);
    }

    vec3& operator+=(const vec3& other) {
        x += other.x;
        y += other.y;
        z += other.z;

        return *this;
    }

    vec3& operator*=(double n) {
        x *= n;
        y *= n;
        z *= n;
        return *this;
    }

    vec3& operator/=(double n) {
        return *this *= 1/n;
    }
};

void normalize(vec3& v);

double invLen(const vec3& v);

double lenSquared(const vec3& v);

double dot(const vec3& v0, const vec3& v1);

bool nearZero(const vec3& v);

vec3 cross(const vec3& v0, const vec3& v1);

vec3 unit(const vec3& v);

vec3 random();

vec3 random(double min, double max);

vec3 randomUnitVec();

vec3 randomInUnitDisk();

vec3 randomOnHemisphere(const vec3& normal);

vec3 reflect(const vec3& v, const vec3& n);

vec3 refract(const vec3& uv, const vec3& n, double etaiOverEtat);

#endif