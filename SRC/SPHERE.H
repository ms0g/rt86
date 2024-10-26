#ifndef SPHERE_H
#define SPHERE_H

#include "SCENEOBJ.H"
#include "MATH.H"

class Sphere: public SceneObject {
public:
    Sphere(const vec3& center, float radius, Material* mat): 
        mCenter(center), 
        mRadius(fmax(0, radius)),
        mMat(mat) {}
    
    ~Sphere();

    virtual bool hit(const Ray& ray, float tmin, float tmax, HitRecord& rec) const;

private:
    vec3 mCenter;
    float mRadius;
    Material* mMat;
};

#endif