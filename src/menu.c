#include <stdio.h>
#include "menu.h"
#include "file_io.h"
#include "image.h"
#include "transformations.h"  // Include the transformations header

#include "effects.h"

// External declarations for image variables
extern int imageWidth;
extern int imageHeight;
extern unsigned char* imageData;


void applyEffect() {
    int choice;

    // Check if an image is loaded
    if (loadedImage == NULL) {
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
    if (loadedImage == NULL) {
        fprintf(stderr, "Error: No image loaded.\n");
        return;
    }

    // Ask the user for the output filename
    char outputFilename[100];  // Adjust the size based on your needs
    printf("Enter the filename to save the image: ");
    scanf("%s", outputFilename);

    // Save the image (implement saveImage function in file_io.c)
    saveModifiedImage(outputFilename);  // <-- Call the correct function here
}

