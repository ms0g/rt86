#include "CAMERA.H"
#include "MATH.H"

Camera::Camera(double aspectRatio, double vfov, double defocusAngle, double focusDist, int imageWidth, vec3 lookfrom, vec3 lookat, vec3 vup) {
    int imageHeight = (int)(imageWidth / aspectRatio);
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;
    
    mCenter = lookfrom;
    mDefocusAngle = defocusAngle;
    
    double theta = degree2radian(vfov);
    double h = tan(theta/2);
    double viewportHeight = 2.0 * h * focusDist;
    double viewportWidth = viewportHeight * ((double)imageWidth/imageHeight);

     // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
    vec3 w = unit(lookfrom - lookat);
    vec3 u = unit(cross(vup, w));
    vec3 v = cross(w, u);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    vec3 viewport_u = u * viewportWidth;
    vec3 viewport_v = v * -viewportHeight;

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    mPixelDeltaU = viewport_u / imageWidth;
    mPixelDeltaV = viewport_v / imageHeight;

    // Calculate the location of the upper left pixel.
    vec3 viewportUpperLeft = mCenter - w * focusDist - (viewport_u + viewport_v) * 0.5;
    mPixel00Loc = viewportUpperLeft + (mPixelDeltaU + mPixelDeltaV) * 0.5;

    // Calculate the camera defocus disk basis vectors.
    double defocusRadius = focusDist * tan(degree2radian(defocusAngle / 2));
    mDefocusDiskU = u * defocusRadius;
    mDefocusDiskV = v * defocusRadius;
}

Ray Camera::getRay(int x, int y) const {
    // Construct a camera ray originating from the origin and directed at randomly sampled
    // point around the pixel location x, y.

    vec3 offset = sampleSquare();
    vec3 pixelSample = mPixel00Loc + (mPixelDeltaU * (x + offset.x)) + (mPixelDeltaV * (y + offset.y));

    vec3 rayOrig = (mDefocusAngle <= 0) ? mCenter : defocusDiskSample();;
    vec3 rayDir = pixelSample - rayOrig;

    return Ray(rayOrig, rayDir);
}

vec3 Camera::sampleSquare() const {
    // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
    return vec3(randd() - 0.5, randd() - 0.5, 0);
}

vec3 Camera::defocusDiskSample() const {
    // Returns a random point in the camera defocus disk.
    vec3 p = randomInUnitDisk();
    return mCenter + (mDefocusDiskU * p.x) + (mDefocusDiskV * p.y);
}