#ifndef SCENEOBJ_H
#define SCENEOBJ_H

#include "RAY.H"

struct HitRecord {
    vec3 p;
    vec3 normal;
    float t;
    int front_face;

    void setFaceNormal(const Ray& ray, const vec3& outwardNormal) {
        // Sets the hit record normal vector.
        // NOTE: the parameter `outward_normal` is assumed to have unit length.

        front_face = dot(ray.direction(), outwardNormal) < 0;
        normal = front_face ? outwardNormal : -outwardNormal;
    }
};

class SceneObject {
public:
    virtual ~SceneObject() {}

    virtual int hit(const Ray& ray, float rayTmin, float rayTmax, HitRecord& rec) const = 0;
};

#endif