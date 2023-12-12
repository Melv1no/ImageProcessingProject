// file_io.h

#ifndef FILE_IO_H
#define FILE_IO_H

#include "image.h"

// External variables for loaded images
extern PGMImage* loadedPGMImage;
extern PPMImage* loadedPPMImage;

int loadPGMImage(const char* filename);
int loadPPMImage(const char* filename);
void savePGMImage(const char* outputFilename);
void savePPMImage(const char* outputFilename);
void cleanupPGMImage();
void cleanupPPMImage();

#endif // FILE_IO_H
