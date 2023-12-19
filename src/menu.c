/*
 * Author: Melvin OLIVET
 * Date: {{publish_date}}
 * Description: menu
 */

#include <stdio.h>
#include <string.h>

#include "menu.h"
#include "file_io.h"
#include "effects.h"

#define MAX_FILENAME_SIZE 100
#define PPM_FILE_EXT ".ppm"
#define PGM_FILE_EXT ".pgm"

void displayApplyEffectMenu() {
    int mainMenuChoice;
    int subMenuChoice;
    double angle;

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
    scanf("%d", &mainMenuChoice);

    switch (mainMenuChoice) {
        case 1:
            printf("\nBlur level:\n");
            printf("1. Low\n2. Medium\n3. Strong\n4. Very Strong\n");

            printf("Enter your choice: ");
            scanf("%d", &subMenuChoice);
            if (subMenuChoice > 4) {
            break;
                }
            applyBlurEffect(subMenuChoice);
        break;
        case 2:
            applyMirrorEffect();
        break;
        case 3:
            applyImageSize();
        break;
        case 4:
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
    char outputFilename[MAX_FILENAME_SIZE];

    printf("Enter the filename to save the image: ");
    scanf("%s", outputFilename);

    char* extension = strrchr(outputFilename, '.');
    if (!extension || (strcmp(extension, PGM_FILE_EXT) && strcmp(extension, PPM_FILE_EXT))) {
        fprintf(stderr, "Error: Invalid or unsupported file extension.\n");
        return;
    }

    if (strcmp(extension, PGM_FILE_EXT) == 0) {
        savePGMImage(outputFilename);
    } else {
        savePPMImage(outputFilename);
    }
}

void debug() {
    // Chargez une image initiale (remplacez "example.ppm" par le chemin de votre image)
    loadPPMImage("C:\\sample.ppm");
    loadPGMImage("C:\\sample.pgm");

    // Appliquez une séquence d'effets prédéfinis pour les images PPM
    applyBlurEffect(2);  // Applique un flou moyen
    savePPMImage("result_blur.ppm");
    cleanupImages();
    loadPPMImage("C:\\sample.ppm");
    loadPGMImage("C:\\sample.pgm");
    applyMirrorEffect();
    savePPMImage("result_mirror.ppm");
    savePGMImage("result_mirror.pgm");
    cleanupImages();
    loadPPMImage("C:\\sample.ppm");
    loadPGMImage("C:\\sample.pgm");
    applyImageSize();
    savePPMImage("result_resize.ppm");
    cleanupImages();
    loadPPMImage("C:\\sample.ppm");
    loadPGMImage("C:\\sample.pgm");
    applyImageRotation(45.0);  // Rotation de 45 degrés
    savePPMImage("result_rotation.ppm");
    cleanupImages();
    loadPPMImage("C:\\sample.ppm");
    loadPGMImage("C:\\sample.pgm");
    generateMipmap();
    savePPMImage("result_mipmap.ppm");
    savePGMImage("result_mipmap.pgm");
    cleanupImages();
    loadPPMImage("C:\\sample.ppm");
    loadPGMImage("C:\\sample.pgm");
    applyNegativeEffect();
    savePPMImage("result_negative.ppm");
    savePGMImage("result_negative.pgm");
    cleanupImages();
    loadPPMImage("C:\\sample.ppm");
    loadPGMImage("C:\\sample.pgm");
    applyGrayscaleEffect();
    savePPMImage("result_grayscale.ppm");
    savePGMImage("result_grayscale.pgm");
    cleanupImages();
    loadPPMImage("C:\\sample.ppm");
    loadPGMImage("C:\\sample.pgm");
    applyPixelizationEffect();
    savePPMImage("result_pixelization.ppm");
    savePGMImage("result_pixelization.pgm");
    cleanupImages();
    loadPPMImage("C:\\sample.ppm");
    loadPGMImage("C:\\sample.pgm");
    applySobelEffect();
    savePPMImage("result_sobel.ppm");
    savePGMImage("result_sobel.pgm");
    cleanupImages();
    loadPPMImage("C:\\sample.ppm");
    loadPGMImage("C:\\sample.pgm");
    applyGaussianEffect();
    savePPMImage("result_gaussian.ppm");
    savePGMImage("result_gaussian.pgm");
    cleanupImages();
    loadPPMImage("C:\\sample.ppm");
    loadPGMImage("C:\\sample.pgm");
    // Appliquez une séquence d'effets prédéfinis pour les images PGM
    applyBlurEffect(2);  // Applique un flou moyen
    savePGMImage("result_blur.pgm");
    savePPMImage("result_blur.ppm");
    cleanupImages();
    loadPPMImage("C:\\sample.ppm");
    loadPGMImage("C:\\sample.pgm");
    applyImageSize();
    savePGMImage("result_resize.pgm");
    savePPMImage("result_resize.ppm");
    cleanupImages();
    loadPPMImage("C:\\sample.ppm");
    loadPGMImage("C:\\sample.pgm");
    applyImageRotation(45.0);  // Rotation de 45 degrés
    savePGMImage("result_rotation.pgm");
    savePPMImage("result_rotation.ppm");
    cleanupImages();
    loadPPMImage("C:\\sample.ppm");
    loadPGMImage("C:\\sample.pgm");
    applyNegativeEffect();
    savePGMImage("result_negative.pgm");
    savePPMImage("result_negative.ppm");
    cleanupImages();
    loadPPMImage("C:\\sample.ppm");
    loadPGMImage("C:\\sample.pgm");
    applyGrayscaleEffect();
    savePGMImage("result_grayscale.pgm");
    savePPMImage("result_grayscale.ppm");
    cleanupImages();
}
