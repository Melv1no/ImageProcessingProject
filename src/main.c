#include <stdio.h>
#include <string.h>

#include "menu.h"
#include "file_io.h"
#include "image.h"

// Definition of image variables
int imageWidth;
int imageHeight;
unsigned char* imageData;

// Definition of loadedImage


int main() {
    int choice;
    char filename[100];  // Adjust the size based on your needs

    // Load an image before entering the menu
    printf("Enter the filename of the image to load: ");
    scanf("%s", filename);

    // Determine the image type based on the file extension
    char* extension = strrchr(filename, '.');
    if (extension != NULL) {
        if (strcmp(extension, ".pgm") == 0) {
            if (loadPGMImage(filename) == 0) {
                printf("PGM Image loaded successfully.\n");
            } else {
                printf("Failed to load the PGM image. Exiting.\n");
                return 1;
            }
        } else if (strcmp(extension, ".ppm") == 0) {
            if (loadPPMImage(filename) == 0) {
                printf("PPM Image loaded successfully.\n");
            } else {
                printf("Failed to load the PPM image. Exiting.\n");
                return 1;
            }
        } else {
            printf("Unsupported file format. Exiting.\n");
            return 1;
        }
    } else {
        printf("Invalid filename. Exiting.\n");
        return 1;
    }
    do {
        // Display the menu
        printf("\nImage Processing Menu:\n");
        printf("1. Apply Effect\n");
        printf("2. Save Image\n");
        printf("3. Exit\n");

        // Get user choice
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Process user choice
        switch (choice) {
            case 1:
                // Call function to handle effect
                    applyEffect();
            break;
            case 2:
                // Call function to save image
                    saveImage();
            break;
            case 3:
                printf("Exiting...\n");
            break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 4);

    return 0;
}
