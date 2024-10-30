#include "SCENE.H"

Scene::~Scene() {
    for (int i = 0; i < objects.size(); ++i) {
        delete objects[i];
    }
}

 bool Scene::hit(const Ray& ray, double tmin, double tmax, HitRecord& rec) const {
    HitRecord tempRec;
    bool hitAnything = false;
    double closestSoFar = tmax;

    for (int i = 0; i < objects.size(); ++i) {
        if (objects[i]->hit(ray, tmin, closestSoFar, tempRec)) {
            hitAnything = true;
            closestSoFar = tempRec.t;
            rec = tempRec;
        }
    }

    return hitAnything;
 }