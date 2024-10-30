#ifndef CAMERA_H
#define CAMERA_H

#include "VEC3.H"
#include "RAY.H"

class Camera {
public:
    Camera(double aspectRatio = 1.0, double vfov = 90, double defocusAngle = 0, double focusDist = 10,
        int imageWidth = 100, vec3 lookfrom = vec3(0,0,0), vec3 lookat = vec3(0,0,-1), vec3 vup = vec3(0,1,0));
    
    Ray getRay(int x, int y) const;

private:
    vec3 sampleSquare() const;
    vec3 defocusDiskSample() const;
    
    vec3 mCenter;           // Camera center
    vec3 mPixel00Loc;       // Location of pixel 0, 0
    vec3 mPixelDeltaU;      // Offset to pixel to the right
    vec3 mPixelDeltaV;      // Offset to pixel below
    double mDefocusAngle;    // Variation angle of rays through each pixel
    vec3 mDefocusDiskU;     // Defocus disk horizontal radius
    vec3 mDefocusDiskV;     // Defocus disk vertical radius
};

#endif