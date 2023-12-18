#ifndef IMAGE_H
#define IMAGE_H

typedef struct {
    int width;
    int height;
    unsigned char* data;
} PGMImage;

typedef struct {
    int width;
    int height;
    unsigned char* data;
} PPMImage;

PGMImage* createPGMImage(int width, int height);
PPMImage* createPPMImage(int width, int height);

void freePGMImage(PGMImage* image);
void freePPMImage(PPMImage* image);

#endif
