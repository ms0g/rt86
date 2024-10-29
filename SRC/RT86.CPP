#include <conio.h>
#include <float.h>
#include "COLOR.H"
#include "VGA.H"
#include "RAY.H"
#include "VEC3.H"
#include "SCENE.H"
#include "SPHERE.H"
#include "CAMERA.H"
#include "MATERIAL.H"

#define WIDTH 320
#define HEIGHT 200
#define SAMPLES_PER_PIXEL 75
#define PIXEL_SAMPLES_SCALE 1.0 / SAMPLES_PER_PIXEL
#define MAX_DEPTH 50
// Camera Settings
#define ASPECT_RATIO 4.0 / 3.0
#define VFOV 20
#define DEFOCUS_ANGLE 0.6
#define FOCUS_DIST 10.0
#define LOOKFROM    vec3(13,2,3)
#define LOOKAT      vec3(0,0,0)
#define VUP         vec3(0,1,0)

color rayColor(const Ray& ray, int depth, const Scene& scene) {
    if (depth <= 0) {
        return color(0, 0, 0);
    }

    HitRecord rec;
    if (scene.hit(ray, 0.001, FLT_MAX, rec)) {
        Ray scattered;
        color attenuation;
        if (rec.mat->scatter(ray, rec, attenuation, scattered)) {
            return attenuation * rayColor(scattered, depth - 1, scene);
        }
       
        return color(0, 0, 0);
    }

    vec3 unitDir = unit(ray.direction());
    float a = 0.5 * (unitDir.y + 1.0);
    return color(1.0, 1.0, 1.0) * (1.0 - a) + color(0.5, 0.7, 1.0) * a;
}

void main(void) {
    Scene scene;
    scene.add(new Sphere(vec3( 0.0, -100, -1.0), 100.0, new Lambertian(color(0.5, 0.5, 0.5))));   // Ground
    
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            float choose_mat = randf();
            vec3 center(a + 0.9 * randf(), 0.2, b + 0.9 * randf());

            if (pow(invLen(center - vec3(4, 0.2, 0)), -1) > 0.9) {
                Material* sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    vec3 albedo = random() * random();
                    sphere_material = new Lambertian(albedo);
                    scene.add(new Sphere(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    vec3 albedo = random(0.5, 1);
                    float fuzz = randf(0, 0.5);
                    sphere_material = new Metal(albedo, fuzz);
                    scene.add(new Sphere(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = new Dielectric(1.5);
                    scene.add(new Sphere(center, 0.2, sphere_material));
                }
            }
        }
    }

    scene.add(new Sphere(vec3(0, 1, 0), 1.0, new Dielectric(1.5)));

    scene.add(new Sphere(vec3(-4, 1, 0), 1.0, new Lambertian(color(0.4, 0.2, 0.1))));

    scene.add(new Sphere(vec3(4, 1, 0), 1.0, new Metal(color(0.7, 0.6, 0.5), 0.0)));

    Camera cam(ASPECT_RATIO, VFOV, DEFOCUS_ANGLE, FOCUS_DIST, WIDTH, LOOKFROM, LOOKAT, VUP);
   
    _initMode(MODE_VGA_13H);

    _waitvretrace();

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            color pixelColor(0, 0, 0);
            
            for (int i = 0; i < SAMPLES_PER_PIXEL; ++i) {
                Ray r = cam.getRay(x, y);
                pixelColor += rayColor(r, MAX_DEPTH, scene);
            }
            
            _putpixel(x, y, pixel2vga(pixelColor * PIXEL_SAMPLES_SCALE));
        }
    }

    getch();
    _initMode(MODE_VGA_3H);
}
