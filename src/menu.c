#include <stdio.h>
#include <string.h>

#include "menu.h"
#include "file_io.h"
#include "image.h"
#include "effects.h"

// External declarations for image variables
extern PGMImage* loadedPGMImage;
extern PPMImage* loadedPPMImage;

void applyEffect() {
    int choice;

    if (loadedPGMImage == NULL && loadedPPMImage == NULL) {
        fprintf(stderr, "Error: No image loaded.\n");
        return;
    }

    printf("\nChoose an Effect:\n");
    printf("1. Blur\n");
    printf("2. Mirror\n");
    printf("3. Resize\n");
    printf("4. Rotation\n");
    printf("5. Generate Mipmap\n");
    printf("6. Negative Effect\n");
    printf("7. Grayscale Effect\n");
    printf("8. Pixelization Effect\n");
    printf("9. Sobel Effect\n");
    printf("10. Gaussian Effect\n");
    printf("99. Back to Main Menu\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("\nBlur level:\n");
            printf("1. Low\n");
            printf("2. Medium\n");
            printf("3. Strong\n");
            printf("4. Very Strong\n");

            printf("Enter your choice: ");
            scanf("%d", &choice);
            if (choice > 4) {
                break;
            }
            applyBlurEffect(choice);
            break;
        case 2:
            applyMirrorEffect();
            break;
        case 3:
            applyImageSize();
            break;
        case 4:
            double angle;
            printf("Enter the rotation angle in degrees: ");
            scanf("%lf", &angle);
            applyImageRotation(angle);
            break;
        case 5:
            generateMipmap();
            break;
        case 6:
            applyNegativeEffect();
            break;
        case 7:
            applyGrayscaleEffect();
            break;
        case 8:
            applyPixelizationEffect();
            break;
        case 9:
            applySobelEffect();
        break;
        case 10:
            applyGaussianEffect();
        break;
        case 99:
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
