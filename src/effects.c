#include "effects.h"

#include <stdio.h>

#include "file_io.h"
#include "image.h"  // Incluez le fichier d'en-tête pour les images

// Definition of loadedImage

void applyBlurEffect() {
    // Check if an image is loaded
    if (loadedPGMImage == NULL) {
        fprintf(stderr, "Error: No image loaded.\n");
        return;
    }

    // Create a temporary image to store the blurred result
    PGMImage* blurredImage = createPGMImage(loadedPGMImage->width, loadedPGMImage->height);

    // Apply the blur effect with a 9x9 filter
    for (int row = 4; row < loadedPGMImage->height - 4; ++row) {
        for (int col = 4; col < loadedPGMImage->width - 4; ++col) {
            // Apply a 9x9 box blur
            unsigned int sum = 0;
            for (int i = -4; i <= 4; ++i) {
                for (int j = -4; j <= 4; ++j) {
                    sum += loadedPGMImage->data[(row + i) * loadedPGMImage->width + (col + j)];
                }
            }
            blurredImage->data[row * loadedPGMImage->width + col] = sum / 81;  // 9x9 = 81
        }
    }

    // Copy the blurred result back to the original image
    for (int i = 0; i < loadedPGMImage->width * loadedPGMImage->height; ++i) {
        loadedPGMImage->data[i] = blurredImage->data[i];
    }

    // Free the temporary image
    freePGMImage(blurredImage);

    printf("Effect applied: Strong Blur\n");
}


void applyMirrorEffect() {
    // Check if an image is loaded
    if (loadedPGMImage == NULL) {
        fprintf(stderr, "Error: No image loaded.\n");
        return;
    }

    // Calculate the middle column
    int middleColumn = loadedPGMImage->width / 2;

    // Iterate through each row and swap pixels across the middle column
    for (int row = 0; row < loadedPGMImage->height; ++row) {
        for (int col = 0; col < middleColumn; ++col) {
            int leftIndex = row * loadedPGMImage->width + col;
            int rightIndex = row * loadedPGMImage->width + (loadedPGMImage->width - 1 - col);

            // Swap pixel values
            unsigned char temp = loadedPGMImage->data[leftIndex];
            loadedPGMImage->data[leftIndex] = loadedPGMImage->data[rightIndex];
            loadedPGMImage->data[rightIndex] = temp;
        }
    }

    printf("Effect applied: Mirror\n");
}
