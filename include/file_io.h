#ifndef FILE_IO_H
#define FILE_IO_H
#include "image.h"

extern int isPGMImageLoaded;
extern int isPPMImageLoaded;

int loadPGMImage(const char* filename);
int loadPPMImage(const char* filename);

void savePGMImage(const char* outputFilename);
void savePPMImage(const char* outputFilename);
void cleanupImages();

#endif
