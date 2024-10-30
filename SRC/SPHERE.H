#ifndef SPHERE_H
#define SPHERE_H

#include "SCENEOBJ.H"
#include "MATH.H"

class Sphere: public SceneObject {
public:
    Sphere(const vec3& center, double radius, Material* mat): 
        mCenter(center), 
        mRadius(fmax(0, radius)),
        mMat(mat) {}
    
    ~Sphere();

    virtual bool hit(const Ray& ray, double tmin, double tmax, HitRecord& rec) const;

private:
    vec3 mCenter;
    double mRadius;
    Material* mMat;
};

#endif