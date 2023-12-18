#ifndef EFFECTS_H
#define EFFECTS_H
#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif
#include "image.h"

extern PGMImage* loadedPGMImage;
extern PPMImage* loadedPPMImage;

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

#endif
