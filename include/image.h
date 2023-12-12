// image.h
#ifndef IMAGE_H
#define IMAGE_H

// Structure to represent a grayscale PGM image
typedef struct {
    int width;
    int height;
    unsigned char* data;
} PGMImage;

// Structure to represent a color PPM image
typedef struct {
    int width;
    int height;
    unsigned char* data;  // RGB triplets: R1, G1, B1, R2, G2, B2, ...
} PPMImage;

// Function declarations for image handling
PGMImage* createPGMImage(int width, int height);
void freePGMImage(PGMImage* image);

PPMImage* createPPMImage(int width, int height);
void freePPMImage(PPMImage* image);

#endif  // IMAGE_H
