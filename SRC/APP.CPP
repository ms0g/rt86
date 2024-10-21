#include "APP.H"
#include "RAYTRCR.H"
#include "RENDERER.H"
#include "KEYBRD.H"

App::App() {
    renderer = new Renderer();

    rayTracer = new RayTracer();

    initkb();

    isRunning = 1;
}

App::~App() {
    delete renderer;

    delete rayTracer;

    exitkb();
}

void App::loop(void) {
     while (isRunning) {
        processInput();
        update();
        render();
    }
}

void App::processInput(void) {
    char key = kbhit();

    if (key == ESC) {
        isRunning = 0;
    }
}

void App::update(void) {
    rayTracer->update();
}

void App::render(void) {
    renderer->clear(0x0);
    
    rayTracer->draw(renderer);

    renderer->updateBuffer();
}
