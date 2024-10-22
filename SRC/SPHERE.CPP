#include "SPHERE.H"
#include <math.h>

int Sphere::hit(const Ray& ray, float rayTmin, float rayTmax, HitRecord& rec) const {
    vec3 oc = mCenter - ray.origin();
    float a = dot(ray.direction(), ray.direction());
    float h = dot(ray.direction(), oc);
    float c = dot(oc, oc) - mRadius * mRadius;
    float discriminant = h * h - a * c;
    
    if (discriminant < 0)
        return 0;

    float sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    float root = (h - sqrtd) / a;
    if (root <= rayTmin || rayTmax <= root) {
        root = (h + sqrtd) / a;
        if (root <= rayTmin || rayTmax <= root)
            return 0;
    }

    rec.t = root;
    rec.p = ray.at(rec.t);
    
    vec3 outwardNormal = (rec.p - mCenter) / mRadius;
    rec.setFaceNormal(ray, outwardNormal);

    return 1;
}