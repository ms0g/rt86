#include "RAYTRCR.H"
#include "RENDERER.H"
#include "COLOR.H"

#define WIDTH 320
#define HEIGHT 200

void RayTracer::update(void) {
 
}

void RayTracer::draw(Renderer* renderer) {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            color pixelColor = color((float)x / (WIDTH-1), (float)y / (HEIGHT-1), 0.0);
            
            unsigned char vgaColor = pixel2Vga(pixelColor);

			_putpixel(x, y, vgaColor);
        }
    }
}