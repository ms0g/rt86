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
#define ASPECT_RATIO 4.0 / 3.0
#define MAX_DEPTH 50

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
    scene.add(new Sphere(vec3( 0.0, -100.5, -1.0), 100.0, new Lambertian(color(0.8, 0.8, 0.0))));   // Ground
    scene.add(new Sphere(vec3( 0.0, 0.0, -1.2), 0.5, new Lambertian(color(0.1, 0.2, 0.5))));        // Center
    scene.add(new Sphere(vec3(-1.0, 0.0, -1.0), 0.5, new Dielectric(1.50)));                        // Left
    scene.add(new Sphere(vec3(-1.0, 0.0, -1.0), 0.4, new Dielectric(1.00 / 1.50)));                 // Bubble   
    scene.add(new Sphere(vec3( 1.0, 0.0, -1.0), 0.5, new Metal(color(0.8, 0.6, 0.2), 0.3)));        // Right

    Camera cam(ASPECT_RATIO, WIDTH);
   
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
