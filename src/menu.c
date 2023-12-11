#include <stdio.h>
#include "menu.h"
#include "file_io.h"
#include "image.h"
#include "transformations.h"  // Include the transformations header

// External declarations for image variables
extern int imageWidth;
extern int imageHeight;
extern unsigned char* imageData;

void applyTransformation() {
    // Implement the logic for applying transformations
    // Example: Invert colors
    for (int i = 0; i < imageWidth * imageHeight; ++i) {
        imageData[i] = 255 - imageData[i];
    }

    printf("Transformation applied.\n");
}

void applyEffect() {
    // Implement the logic for applying effects
    // Example: Blur
    printf("Effect applied: Blur\n");
}

void saveImage() {
    // Check if an image is loaded
    if (loadedImage == NULL) {
        fprintf(stderr, "Error: No image loaded.\n");
        return;
    }

    // Implement the logic for saving the image (if needed)
    // Example: Saving image as "output.pgm"
    FILE* file = fopen("output.pgm", "wb");

    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file for writing.\n");
        return;
    }

    // Write PGM header
    fprintf(file, "P5\n%d %d\n255\n", loadedImage->width, loadedImage->height);

    // Write image data
    fwrite(loadedImage->data, sizeof(unsigned char), loadedImage->width * loadedImage->height, file);

    fclose(file);
    printf("Image saved successfully.\n");
}

// New menu function for mirror effect
void applyMirrorEffect() {
    mirrorImage();
}

void cleanupImage() {
    // Free the loaded image data
    if (loadedImage != NULL) {
        freePGMImage(loadedImage);
    }
}
