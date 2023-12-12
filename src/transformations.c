#include "transformations.h"

#include <stdio.h>

#include "image.h"  // Include the image header file

// Definition of loadedImage

void mirrorImage() {
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

    printf("Mirror effect applied.\n");
}
