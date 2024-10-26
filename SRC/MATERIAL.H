#ifndef MATERIAL_H
#define MATERIAL_H

#include "SCENEOBJ.H"
#include "COLOR.H"

class Material {
public:
    virtual ~Material() {}

    virtual bool scatter(const Ray& in, const HitRecord& rec, color& attenuation, Ray& scattered) const {
        return false;
    }
};

class Lambertian: public Material {
public:
    Lambertian(const color& albedo) : albedo(albedo) {}

    virtual bool scatter(const Ray& in, const HitRecord& rec, color& attenuation, Ray& scattered) const {
        vec3 scatterDir = rec.normal + randomUnitVec();

        // Catch degenerate scatter direction
        if (nearZero(scatterDir)) {
            scatterDir = rec.normal;
        }
           
        scattered = Ray(rec.p, scatterDir);
        attenuation = albedo;
        return true;
    }

private:
    color albedo;
};

class Metal: public Material {
public:
    Metal(const color& albedo) : albedo(albedo) {}

    virtual bool scatter(const Ray& in, const HitRecord& rec, color& attenuation, Ray& scattered) const {
        vec3 reflected = reflect(in.direction(), rec.normal);
        scattered = Ray(rec.p, reflected);
        attenuation = albedo;
        return true;
    }

private:
    color albedo;
};

#endif