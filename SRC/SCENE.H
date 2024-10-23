#ifndef SCENE_H
#define SCENE_H

#include "SCENEOBJ.H"
#include "VECTOR.H"

class Scene: public SceneObject {
public:
    Scene() {}

    Scene(SceneObject* object) { add(object); }
    
    ~Scene();
    
    void clear() { objects.clear(); }

    void add(SceneObject* object) { objects.push_back(object); }

    int hit(const Ray& ray, float rayTmin, float rayTmax, HitRecord& rec) const;

private:
    vector<SceneObject*> objects;
};

#endif