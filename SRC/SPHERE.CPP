#include "SPHERE.H"
#include "MATERIAL.H"

Sphere::~Sphere() {
    delete mMat;
}

bool Sphere::hit(const Ray& ray, double tmin, double tmax, HitRecord& rec) const {
    vec3 oc = mCenter - ray.origin();
    double a = dot(ray.direction(), ray.direction());
    double h = dot(ray.direction(), oc);
    double c = dot(oc, oc) - mRadius * mRadius;
    double discriminant = h * h - a * c;
    
    if (discriminant < 0)
        return false;

    double sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    double root = (h - sqrtd) / a;
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