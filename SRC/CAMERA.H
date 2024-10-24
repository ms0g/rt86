#ifndef CAMERA_H
#define CAMERA_H

#include "VEC3.H"

class Camera {
public:
    Camera(float aspectRatio = 1.0, int imageWidth = 100);

    vec3 center() const { return mCenter; }
    
    vec3 pixelCenter(int x, int y);

private:
    float mAspectRatio;
    int mImageWidth;  
    int mImageHeight;   // Rendered image height
    vec3 mCenter;       // Camera center
    vec3 mPixel00Loc;   // Location of pixel 0, 0
    vec3 mPixelDeltaU; // Offset to pixel to the right
    vec3 mPixelDeltaV; // Offset to pixel below

};

#endif