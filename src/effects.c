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

    // Implement the logic for applying the mirror effect
    printf("Effect applied: Mirror\n");
}
