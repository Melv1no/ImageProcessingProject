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

    // Check if an image is loaded
    if (loadedPGMImage == NULL) {
        fprintf(stderr, "Error: No image loaded.\n");
        return;
    }

    // Display the effect menu
    printf("\nChoose an Effect:\n");
    printf("1. Blur\n");
    printf("2. Mirror\n");  // Ajoutez d'autres effets au besoin
    printf("3. Back to Main Menu\n");

    // Get user choice
    printf("Enter your choice: ");
    scanf("%d", &choice);

    // Process user choice
    switch (choice) {
        case 1:
            applyBlurEffect();
        break;
        case 2:
            applyMirrorEffect();  // Ajoutez d'autres cas pour les autres effets
        break;
        case 3:
            printf("Returning to the main menu.\n");
        break;
        default:
            printf("Invalid choice. Returning to the main menu.\n");
    }
}
void saveImage() {
    // Check if an image is loaded
    if (loadedPGMImage == NULL && loadedPPMImage == NULL) {
        fprintf(stderr, "Error: No image loaded.\n");
        return;
    }

    // Ask the user for the output filename and folder
    char outputFilename[100];  // Adjust the size based on your needs


    printf("Enter the filename to save the image: ");
    scanf("%s", outputFilename);



    // Determine the file extension
    char* extension = strrchr(outputFilename, '.');
    if (extension == NULL) {
        fprintf(stderr, "Error: File extension not found.\n");
        return;
    }

    // Save the image based on the file extension
    if (strcmp(extension, ".pgm") == 0) {
        savePGMImage(outputFilename);
    } else if (strcmp(extension, ".ppm") == 0) {
        savePPMImage(outputFilename);
    } else {
        fprintf(stderr, "Error: Unsupported file extension.\n");
    }
}

