// file_io.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_io.h"


PGMImage* loadedPGMImage = NULL;
PPMImage* loadedPPMImage = NULL;
int isPGMImageLoaded = 0;
int isPPMImageLoaded = 0;
// Implement other functions...


int loadPGMImage(const char* filename) {
    FILE* file = fopen(filename, "rb");
    isPGMImageLoaded = 1;
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
    FILE* file = fopen(filename, "rb");
    isPPMImageLoaded = 1;
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file '%s' for reading or file does not exist.\n", filename);
        return 1;
    }

    // Read the PPM header
    char magicNumber[3];
    int width, height, maxColorValue;

    fscanf(file, "%2s %d %d %d", magicNumber, &width, &height, &maxColorValue);

    // Check if the file is a valid PPM file
    if (strcmp(magicNumber, "P6") != 0 || maxColorValue != 255) {
        fprintf(stderr, "Error: Invalid PPM file format.\n");
        fclose(file);
        return 1;
    }

    // Allocate memory for PPM image data
    loadedPPMImage = createPPMImage(width, height);

    // Read image data
    fread(loadedPPMImage->data, sizeof(unsigned char), width * height * 3, file);  // Multiply by 3 for RGB channels

    fclose(file);
    printf("PPM Image loaded successfully.\n");
    isPPMImageLoaded = 1;  // Set the flag to indicate that a PPM image is loaded
    return 0;
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

    if (loadedPPMImage == NULL) {
        fprintf(stderr, "Error: No PPM image loaded.\n");
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

    fprintf(file, "P6\n%d %d\n255\n", loadedPPMImage->width, loadedPPMImage->height);

    fwrite(loadedPPMImage->data, sizeof(unsigned char), loadedPPMImage->width * loadedPPMImage->height * 3, file);  // Multiply by 3 for RGB channels

    fclose(file);
    printf("PPM Image saved successfully to %s.\n", outputFilename);
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
