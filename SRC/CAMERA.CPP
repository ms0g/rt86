#include "CAMERA.H"

Camera::Camera(float aspectRatio, int imageWidth): mAspectRatio(aspectRatio), mImageWidth(imageWidth)  {
    mImageHeight = (int)(mImageWidth / mAspectRatio);
    mImageHeight = (mImageHeight < 1) ? 1 : mImageHeight;

    float focalLength = 1.0;
    float viewportHeight = 2.0;
    float viewportWidth = viewportHeight * ((float)mImageWidth/mImageHeight);
    mCenter = vec3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    vec3 viewport_u = vec3(viewportWidth, 0, 0);
    vec3 viewport_v = vec3(0, -viewportHeight, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    mPixelDeltaU = viewport_u / mImageWidth;
    mPixelDeltaV = viewport_v / mImageHeight;

    // Calculate the location of the upper left pixel.
    vec3 viewportUpperLeft = mCenter - vec3(0, 0, focalLength) - viewport_u/2 - viewport_v/2;
    mPixel00Loc = viewportUpperLeft + (mPixelDeltaU + mPixelDeltaV) * 0.5;
}

vec3 Camera::pixelCenter(int x, int y) {
    return  mPixel00Loc + (mPixelDeltaU * x) + (mPixelDeltaV * y);
}