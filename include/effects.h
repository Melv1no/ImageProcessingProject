#ifndef EFFECTS_H
#define EFFECTS_H

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif

#include "image.h"

// External declaration for loadedPGMImage and loadedPPMImage
extern PGMImage* loadedPGMImage;
extern PPMImage* loadedPPMImage;

// Function declarations for image effects
void applyBlurEffect();
void applyMirrorEffect();
void applyImageSize();
void applyImageRotation(double angle);
void generateMipmap();
void applyNegativeEffect();
void applyGrayscaleEffect();
void applyPixelizationEffect();
void applySobelEffect();
void applyGaussianEffect();
#endif  // EFFECTS_H
