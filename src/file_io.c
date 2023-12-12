// file_io.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_io.h"


PGMImage* loadedPGMImage = NULL;
PPMImage* loadedPPMImage = NULL;

// Implement other functions...


int loadPGMImage(const char* filename) {
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
    loadedPGMImage = createPGMImage(width, height);

    // Read image data
    fread(loadedPGMImage->data, sizeof(unsigned char), width * height, file);

    fclose(file);
    printf("Image loaded successfully.\n");
    return 0;
}

int loadPPMImage(const char* filename) {
    // Implementation for loading PPM image
    // ...
}

void savePGMImage(const char* outputFilename) {
    // Check if an image is loaded
    if (loadedPGMImage == NULL) {
        fprintf(stderr, "Error: No image loaded.\n");
        return;
    }

    // Construct the full path for the output file in the "output" folder
    char outputPath[100];  // Adjust the size based on your needs
    snprintf(outputPath, sizeof(outputPath), "output/%s", outputFilename);

    // Open the output file for writing
    FILE* file = fopen(outputPath, "wb");

    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file for writing.\n");
        return;
    }

    // Write PGM header
    fprintf(file, "P5\n%d %d\n255\n", loadedPGMImage->width, loadedPGMImage->height);

    // Write image data
    fwrite(loadedPGMImage->data, sizeof(unsigned char), loadedPGMImage->width * loadedPGMImage->height, file);

    fclose(file);
    printf("Image saved successfully to %s.\n", outputPath);
}

void savePPMImage(const char* outputFilename) {
    // Implementation for saving PPM image
    // ...
}

void cleanupImages() {
    // Free memory for loaded images
    if (loadedPGMImage != NULL) {
        freePGMImage(loadedPGMImage);
    }
    if (loadedPPMImage != NULL) {
        freePPMImage(loadedPPMImage);
    }
}
