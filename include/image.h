#ifndef IMAGE_H
#define IMAGE_H

// Structure to represent a grayscale PGM image
typedef struct {
    int width;
    int height;
    unsigned char* data;
} PGMImage;

// Function declarations for image handling
PGMImage* createPGMImage(int width, int height);
void freePGMImage(PGMImage* image);

#endif  // IMAGE_H
