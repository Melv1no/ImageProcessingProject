#include <stdio.h>
#include "menu.h"

#include <string.h>

#include "file_io.h"
#include "image.h"

#include "effects.h"

// External declarations for image variables
extern int imageWidth;
extern int imageHeight;
extern unsigned char* imageData;


void applyEffect() {
    int choice;

    if (loadedPGMImage == NULL && loadedPPMImage == NULL) {
        fprintf(stderr, "Error: No image loaded.\n");
        return;
    }

    printf("\nChoose an Effect:\n");
    printf("1. Blur\n");
    printf("2. Mirror\n");
    printf("3. Back to Main Menu\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            applyBlurEffect();
        break;
        case 2:
            applyMirrorEffect();
        break;
        case 3:
            printf("Returning to the main menu.\n");
        break;
        default:
            printf("Invalid choice. Returning to the main menu.\n");
    }
}
void saveImage() {
    if (loadedPGMImage == NULL && loadedPPMImage == NULL) {
        fprintf(stderr, "Error: No image loaded.\n");
        return;
    }

    char outputFilename[100];

    printf("Enter the filename to save the image: ");
    scanf("%s", outputFilename);

    char* extension = strrchr(outputFilename, '.');
    if (extension == NULL) {
        fprintf(stderr, "Error: File extension not found.\n");
        return;
    }

    if (strcmp(extension, ".pgm") == 0) {
        savePGMImage(outputFilename);
    } else if (strcmp(extension, ".ppm") == 0) {
        savePPMImage(outputFilename);
    } else {
        fprintf(stderr, "Error: Unsupported file extension.\n");
    }
}

