#ifndef SPHERE_H
#define SPHERE_H

#include "SCENEOBJ.H"

#define fmax( n0,  n1) (n0 > n1) ? n0 : n1

class Sphere: public SceneObject {
public:
    Sphere(const vec3& center, float radius): mCenter(center), mRadius(fmax(0, radius)) {}

    int hit(const Ray& ray, float rayTmin, float rayTmax, HitRecord& rec) const;

private:
    vec3 mCenter;
    float mRadius;
};

#endif