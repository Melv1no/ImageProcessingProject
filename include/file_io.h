#ifndef FILE_IO_H
#define FILE_IO_H

#include "image.h"

// External declaration for loadedImage
extern PGMImage* loadedImage;

// Function declarations for file IO
int loadImage(const char* filename);
void saveImage(const char* outputFilename);
void cleanupImage();

#endif  // FILE_IO_H
