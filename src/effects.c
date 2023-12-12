#include "effects.h"

#include <stdio.h>

#include "image.h"  // Incluez le fichier d'en-tête pour les images

// Definition of loadedImage

void applyBlurEffect() {
    // Check if an image is loaded
    if (loadedImage == NULL) {
        fprintf(stderr, "Error: No image loaded.\n");
        return;
    }

    // Implement the logic for applying the blur effect
    printf("Effect applied: Blur\n");
}

void applyMirrorEffect() {
    // Check if an image is loaded
    if (loadedImage == NULL) {
        fprintf(stderr, "Error: No image loaded.\n");
        return;
    }

    // Calculate the middle column
    int middleColumn = loadedImage->width / 2;

    // Iterate through each row and swap pixels across the middle column
    for (int row = 0; row < loadedImage->height; ++row) {
        for (int col = 0; col < middleColumn; ++col) {
            int leftIndex = row * loadedImage->width + col;
            int rightIndex = row * loadedImage->width + (loadedImage->width - 1 - col);

            // Swap pixel values
            unsigned char temp = loadedImage->data[leftIndex];
            loadedImage->data[leftIndex] = loadedImage->data[rightIndex];
            loadedImage->data[rightIndex] = temp;
        }
    }

    printf("Effect applied: Mirror\n");
}
