// file_io.h

#ifndef FILE_IO_H
#define FILE_IO_H

#include "image.h"

extern PGMImage* loadedImage;

int loadImage(const char* filename);
void saveModifiedImage(const char* outputFilename);
void cleanupImage();

#endif // FILE_IO_H
