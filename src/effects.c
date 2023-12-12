#include "effects.h"

#include <stdio.h>

#include "file_io.h"
#include "image.h"  // Incluez le fichier d'en-tête pour les images

// Definition of loadedImage


void applyBlurEffect() {
    // Check if a PGM or PPM image is loaded
    if (!isPGMImageLoaded && !isPPMImageLoaded) {
        fprintf(stderr, "Error: No image loaded.\n");
        return;
    }

    if (isPGMImageLoaded) {
        // Apply blur effect for PGM image
        PGMImage* blurredImage = createPGMImage(loadedPGMImage->width, loadedPGMImage->height);

        for (int row = 4; row < loadedPGMImage->height - 4; ++row) {
            for (int col = 4; col < loadedPGMImage->width - 4; ++col) {
                unsigned int sum = 0;
                for (int i = -4; i <= 4; ++i) {
                    for (int j = -4; j <= 4; ++j) {
                        sum += loadedPGMImage->data[(row + i) * loadedPGMImage->width + (col + j)];
                    }
                }
                blurredImage->data[row * loadedPGMImage->width + col] = sum / 81;  // 9x9 = 81
            }
        }

        for (int i = 0; i < loadedPGMImage->width * loadedPGMImage->height; ++i) {
            loadedPGMImage->data[i] = blurredImage->data[i];
        }

        freePGMImage(blurredImage);
    } else if (isPPMImageLoaded) {
        // Apply blur effect for PPM image (considering only the first channel)
        PPMImage* blurredImage = createPPMImage(loadedPPMImage->width, loadedPPMImage->height);

        for (int row = 4; row < loadedPPMImage->height - 4; ++row) {
            for (int col = 4; col < loadedPPMImage->width - 4; ++col) {
                unsigned int sum = 0;
                for (int i = -4; i <= 4; ++i) {
                    for (int j = -4; j <= 4; ++j) {
                        sum += loadedPPMImage->data[3 * ((row + i) * loadedPPMImage->width + (col + j))];
                    }
                }
                blurredImage->data[3 * (row * loadedPPMImage->width + col)] = sum / 81;  // 9x9 = 81
            }
        }

        for (int i = 0; i < loadedPPMImage->width * loadedPPMImage->height * 3; ++i) {
            loadedPPMImage->data[i] = blurredImage->data[i];
        }

        freePPMImage(blurredImage);
    }

    printf("Effect applied: Strong Blur\n");
}

void applyMirrorEffect() {
    // Check if an image is loaded
    if (loadedPGMImage == NULL && loadedPPMImage == NULL) {
        fprintf(stderr, "Error: No image loaded.\n");
        return;
    }

    // Apply the mirror effect based on the image type
    if (loadedPGMImage != NULL) {
        // PGM Image Mirror Effect
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

        printf("Effect applied: Mirror (PGM)\n");
    } else if (loadedPPMImage != NULL) {
        int middleColumn = loadedPPMImage->width / 2;

        // Iterate through each row and swap pixels across the middle column for each color channel
        for (int row = 0; row < loadedPPMImage->height; ++row) {
            for (int col = 0; col < middleColumn; ++col) {
                // Calculate the left and right indices for each color channel
                int leftIndex = (row * loadedPPMImage->width + col) * 3;  // Multiply by 3 for RGB channels
                int rightIndex = (row * loadedPPMImage->width + (loadedPPMImage->width - 1 - col)) * 3;

                // Swap pixel values for the red channel
                unsigned char tempRed = loadedPPMImage->data[leftIndex];
                loadedPPMImage->data[leftIndex] = loadedPPMImage->data[rightIndex];
                loadedPPMImage->data[rightIndex] = tempRed;

                // Swap pixel values for the green channel
                unsigned char tempGreen = loadedPPMImage->data[leftIndex + 1];
                loadedPPMImage->data[leftIndex + 1] = loadedPPMImage->data[rightIndex + 1];
                loadedPPMImage->data[rightIndex + 1] = tempGreen;

                // Swap pixel values for the blue channel
                unsigned char tempBlue = loadedPPMImage->data[leftIndex + 2];
                loadedPPMImage->data[leftIndex + 2] = loadedPPMImage->data[rightIndex + 2];
                loadedPPMImage->data[rightIndex + 2] = tempBlue;
            }
        }

        printf("Effect applied: Mirror (PPM)\n");
    }
}