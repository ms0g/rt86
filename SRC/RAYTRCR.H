#ifndef RAYTRACER_H
#define RAYTRACER_H

class Renderer;
class RayTracer {
public:
    void update(void);

    void draw(Renderer* renderer);

};

#endif