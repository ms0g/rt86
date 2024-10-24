#include <conio.h>
#include <float.h>
#include "COLOR.H"
#include "VGA.H"
#include "RAY.H"
#include "VEC3.H"
#include "SCENE.H"
#include "SPHERE.H"
#include "CAMERA.H"

#define WIDTH 320
#define HEIGHT 200

color rayColor(const Ray& ray, const Scene& scene) {
    HitRecord rec;
    if (scene.hit(ray, 0, FLT_MAX, rec)) {
        return (rec.normal + color(1,1,1)) * 0.5;
    }

    vec3 unit_direction = unit(ray.direction());
    float a = 0.5 * (unit_direction.y + 1.0);
    return color(1.0, 1.0, 1.0)*(1.0 - a) + color(0.5, 0.7, 1.0) * a;
}

void main(void) {
    Scene scene;
    scene.add(new Sphere(vec3(0,0,-1), 0.5));
    scene.add(new Sphere(vec3(0,-100.5,-1), 100));

    Camera cam(16.0 / 9.0, 400);
   
    _initMode(MODE_VGA_13H);

    _waitvretrace();

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            vec3 pixel_center = cam.pixelCenter(x, y);
            vec3 ray_direction = pixel_center - cam.center();
            Ray ray(cam.center(), ray_direction);

            color pixelColor = rayColor(ray, scene);
			_putpixel(x, y, pixel2vga(pixelColor));
        }
    }

    getch();
    _initMode(MODE_VGA_3H);
}
