#include "SCENE.H"

Scene::~Scene() {
    for (int i = 0; i < objects.size(); ++i) {
        delete objects[i];
    }
}

 int Scene::hit(const Ray& ray, float rayTmin, float rayTmax, HitRecord& rec) const {
    HitRecord tempRec;
    int hitAnything = 0;
    float closestSoFar = rayTmax;

    for (int i = 0; i < objects.size(); ++i) {
        if (objects[i]->hit(ray, rayTmin, closestSoFar, tempRec)) {
            hitAnything = 1;
            closestSoFar = tempRec.t;
            rec = tempRec;
        }
    }

    return hitAnything;
 }