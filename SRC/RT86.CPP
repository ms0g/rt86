#include <conio.h>
#include "COLOR.H"
#include "VGA.H"

#define WIDTH 320
#define HEIGHT 200

void main(void) {
    _initMode(MODE_VGA_13H);

    _waitvretrace();

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            color pixelColor = color((float)x / (WIDTH-1), (float)y / (HEIGHT-1), 0.0);
            
			_putpixel(x, y, pixel2vga(pixelColor));
        }
    }

    getch();
    _initMode(MODE_VGA_3H);
}
