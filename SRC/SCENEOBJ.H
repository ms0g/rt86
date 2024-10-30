#ifndef SCENEOBJ_H
#define SCENEOBJ_H

#include "RAY.H"
#include "BOOL.H"

class Material;
struct HitRecord {
    vec3 p;
    vec3 normal;
    Material* mat;
    double t;
    bool frontFace;

    void setFaceNormal(const Ray& ray, const vec3& outwardNormal) {
        // Sets the hit record normal vector.
        // NOTE: the parameter `outward_normal` is assumed to have unit length.

        frontFace = (bool)(dot(ray.direction(), outwardNormal) < 0);
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class SceneObject {
public:
    virtual ~SceneObject() {}

    virtual bool hit(const Ray& ray, double tmin, double tmax, HitRecord& rec) const = 0;
};

#endif