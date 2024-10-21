#ifndef APP_H
#define APP_H

class Renderer;
class RayTracer;
class App {
public:
    App();
    
    ~App();

    void loop(void);

private:
    void processInput(void);

    void update(void);

    void render(void);

    Renderer* renderer;

    RayTracer* rayTracer;

    int isRunning;
};

#endif