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
    Metal(const color& albedo, float fuzz) : albedo(albedo), mFuzz(fuzz < 1 ? fuzz: 1) {}

    virtual bool scatter(const Ray& in, const HitRecord& rec, color& attenuation, Ray& scattered) const {
        vec3 reflected = reflect(in.direction(), rec.normal);
        reflected = unit(reflected) + randomUnitVec() * mFuzz;
        scattered = Ray(rec.p, reflected);
        attenuation = albedo;
        return (bool)(dot(scattered.direction(), rec.normal) > 0);
    }

private:
    color albedo;
    float mFuzz;
};

class Dielectric: public Material {
public:
    Dielectric(float refractionIndex) : mRefractionIndex(refractionIndex) {}

    virtual bool scatter(const Ray& in, const HitRecord& rec, color& attenuation, Ray& scattered) const {
        // the glass surface absorbs nothing.
        attenuation = color(1.0, 1.0, 1.0);
        
        float ri = rec.frontFace ? (1.0 / mRefractionIndex) : mRefractionIndex;

        vec3 unitDir = unit(in.direction());
        float cosTheta = fmin(dot(-unitDir, rec.normal), 1.0);
        float invSinTheta = invSqrt(1.0 - cosTheta * cosTheta);
        bool cannotRefract = (bool)(ri / invSinTheta > 1.0);

        vec3 dir;
        if (cannotRefract || reflectance(cosTheta, ri) > randf()) {
            dir = reflect(unitDir, rec.normal);
        } else {
            dir = refract(unitDir, rec.normal, ri);
        }

        scattered = Ray(rec.p, dir);
        return true;
    }

private:
    float mRefractionIndex;

    float reflectance(float cosine, float refractionIndex) const {
        // Use Schlick's approximation for reflectance.
        float r0 = (1 - refractionIndex) / (1 + refractionIndex);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }
};

#endif