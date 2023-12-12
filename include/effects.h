#ifndef EFFECTS_H
#define EFFECTS_H
#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif
#include "image.h"

// External declaration for loadedImage
extern PGMImage* loadedImage;

// Function declarations for image effects
void applyBlurEffect();
void applyMirrorEffect();
void applyImageSize();
void applyImageRotation();

#endif  // EFFECTS_H
