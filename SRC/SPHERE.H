#ifndef SPHERE_H
#define SPHERE_H

#include "SCENEOBJ.H"
#include "MATH.H"

class Sphere: public SceneObject {
public:
    Sphere(const vec3& center, float radius): mCenter(center), mRadius(fmax(0, radius)) {}

    virtual bool hit(const Ray& ray, float rayTmin, float rayTmax, HitRecord& rec) const;

private:
    vec3 mCenter;
    float mRadius;
};

#endif