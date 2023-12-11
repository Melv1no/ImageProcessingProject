#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_io.h"
#include "image.h"

// Global variable to store the loaded image
PGMImage* loadedImage = NULL;

int loadImage(const char* filename) {
    FILE* file = fopen(filename, "rb");

    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file '%s' for reading or file does not exist.\n", filename);
        return 1;
    }

    // Read the PGM header
    char magicNumber[3];
    int width, height, maxGrayValue;

    fscanf(file, "%2s %d %d %d", magicNumber, &width, &height, &maxGrayValue);

    // Check if the file is a valid PGM file
    if (strcmp(magicNumber, "P5") != 0 || maxGrayValue != 255) {
        fprintf(stderr, "Error: Invalid PGM file format.\n");
        fclose(file);
        return 1;
    }

    // Allocate memory for image data
    loadedImage = createPGMImage(width, height);

    // Read image data
    fread(loadedImage->data, sizeof(unsigned char), width * height, file);

    fclose(file);
    printf("Image loaded successfully.\n");
    return 0;
}


void saveImage(const char* outputFilename) {
    // Check if an image is loaded
    if (loadedImage == NULL) {
        fprintf(stderr, "Error: No image loaded.\n");
        return;
    }

    // Open the output file for writing
    FILE* file = fopen(outputFilename, "wb");

    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file for writing.\n");
        return;
    }

    // Write PGM header
    fprintf(file, "P5\n%d %d\n255\n", loadedImage->width, loadedImage->height);

    // Write image data
    fwrite(loadedImage->data, sizeof(unsigned char), loadedImage->width * loadedImage->height, file);

    fclose(file);
    printf("Image saved successfully to %s.\n", outputFilename);
}
void cleanupImage() {
    // Free the loaded image data
    if (loadedImage != NULL) {
        freePGMImage(loadedImage);
    }
}
