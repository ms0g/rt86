#ifndef MATERIAL_H
#define MATERIAL_H

#include "SCENEOBJ.H"
#include "COLOR.H"
#include "MATH.H"

class Material {
public:
    virtual ~Material() {}

    virtual bool scatter(const Ray& in, const HitRecord& rec, color& attenuation, Ray& scattered) const {
        (void)in;
        (void)rec;
        (void)attenuation;
        (void)scattered;
        return false;
    }
};

class Lambertian: public Material {
public:
    Lambertian(const color& albedo) : albedo(albedo) {}

    virtual bool scatter(const Ray& in, const HitRecord& rec, color& attenuation, Ray& scattered) const {
        (void)in;
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
    Metal(const color& albedo, double fuzz) : albedo(albedo), mFuzz(fuzz < 1 ? fuzz: 1) {}

    virtual bool scatter(const Ray& in, const HitRecord& rec, color& attenuation, Ray& scattered) const {
        vec3 reflected = reflect(in.direction(), rec.normal);
        reflected = unit(reflected) + randomUnitVec() * mFuzz;
        scattered = Ray(rec.p, reflected);
        attenuation = albedo;
        return (bool)(dot(scattered.direction(), rec.normal) > 0);
    }

private:
    color albedo;
    double mFuzz;
};

class Dielectric: public Material {
public:
    Dielectric(double refractionIndex) : mRefractionIndex(refractionIndex) {}

    virtual bool scatter(const Ray& in, const HitRecord& rec, color& attenuation, Ray& scattered) const {
        // the glass surface absorbs nothing.
        attenuation = color(1.0, 1.0, 1.0);
        
        double ri = rec.frontFace ? (1.0 / mRefractionIndex) : mRefractionIndex;

        vec3 unitDir = unit(in.direction());
        double cosTheta = fmin(dot(-unitDir, rec.normal), 1.0);
        double invSinTheta = invSqrt(1.0 - cosTheta * cosTheta);
        bool cannotRefract = (bool)(ri / invSinTheta > 1.0);

        vec3 dir;
        if (cannotRefract || reflectance(cosTheta, ri) > randd()) {
            dir = reflect(unitDir, rec.normal);
        } else {
            dir = refract(unitDir, rec.normal, ri);
        }

        scattered = Ray(rec.p, dir);
        return true;
    }

private:
    double mRefractionIndex;

    double reflectance(double cosine, double refractionIndex) const {
        // Use Schlick's approximation for reflectance.
        double r0 = (1 - refractionIndex) / (1 + refractionIndex);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }
};

#endif