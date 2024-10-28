#include "SPHERE.H"
#include "MATERIAL.H"

Sphere::~Sphere() {
    delete mMat;
}

bool Sphere::hit(const Ray& ray, float tmin, float tmax, HitRecord& rec) const {
    vec3 oc = mCenter - ray.origin();
    float a = dot(ray.direction(), ray.direction());
    float h = dot(ray.direction(), oc);
    float c = dot(oc, oc) - mRadius * mRadius;
    float discriminant = h * h - a * c;
    
    if (discriminant < 0)
        return false;

    float sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    float root = (h - sqrtd) / a;
    if (root <= tmin || tmax <= root) {
        root = (h + sqrtd) / a;
        if (root <= tmin || tmax <= root)
            return false;
    }

    rec.t = root;
    rec.p = ray.at(rec.t);
    
    vec3 outwardNormal = (rec.p - mCenter) / mRadius;
    rec.setFaceNormal(ray, outwardNormal);
    rec.mat = mMat;

    return true;
}