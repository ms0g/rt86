#include <conio.h>
#include <math.h>
#include "COLOR.H"
#include "VGA.H"
#include "RAY.H"
#include "VEC3.H"

#define WIDTH 320
#define HEIGHT 200

float hitSphere(const vec3& center, float radius, const Ray& r) {
    vec3 oc = center - r.origin();
    float a = dot(r.direction(), r.direction());
    float h = dot(r.direction(), oc);
    float c = dot(oc, oc) - radius*radius;
    float discriminant = h * h - a * c;

    if (discriminant < 0) {
        return -1.0;
    }
    
    return (h - sqrt(discriminant)) / a;
}

color rayColor(const Ray& ray) {
    float t = hitSphere(vec3(0, 0, -1), 0.5, ray);
    
    if (t > 0.0) {
        vec3 N = unit(ray.at(t) - vec3(0, 0, -1));
        return color(N.x+1, N.y+1, N.z+1) * 0.5;
    }

    vec3 unit_direction = unit(ray.direction());
    float a = 0.5*(unit_direction.y + 1.0);
    return color(1.0, 1.0, 1.0)*(1.0-a) + color(0.5, 0.7, 1.0)*a;
}

void main(void) {
    float aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = (int)(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera

    float focal_length = 1.0;
    float viewport_height = 2.0;
    float viewport_width = viewport_height * ((float)image_width/image_height);
    vec3 camera_center = vec3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    vec3 viewport_u = vec3(viewport_width, 0, 0);
    vec3 viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    vec3 pixel_delta_u = viewport_u / image_width;
    vec3 pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    vec3 viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    vec3 pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v) * 0.5;

    _initMode(MODE_VGA_13H);

    _waitvretrace();

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            vec3 pixel_center = pixel00_loc + (pixel_delta_u * x) + (pixel_delta_v * y);
            vec3 ray_direction = pixel_center - camera_center;
            Ray ray(camera_center, ray_direction);

            color pixelColor = rayColor(ray);
			_putpixel(x, y, pixel2vga(pixelColor));
        }
    }

    getch();
    _initMode(MODE_VGA_3H);
}
