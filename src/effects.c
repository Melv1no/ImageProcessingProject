#include "effects.h"

#include <stdio.h>
#include <stdlib.h>

#include "math.h"
#include "file_io.h"
#include "image.h"

void applyBlurEffect(int level) {
    if (isPGMImageLoaded) {
        PGMImage* blurredImage = createPGMImage(loadedPGMImage->width, loadedPGMImage->height);

        int kernelSize = 2 * level + 1;
        int halfKernelSize = kernelSize / 2;

        for (int row = halfKernelSize; row < loadedPGMImage->height - halfKernelSize; ++row) {
            for (int col = halfKernelSize; col < loadedPGMImage->width - halfKernelSize; ++col) {
                unsigned int sum = 0;
                for (int i = -halfKernelSize; i <= halfKernelSize; ++i) {
                    for (int j = -halfKernelSize; j <= halfKernelSize; ++j) {
                        sum += loadedPGMImage->data[(row + i) * loadedPGMImage->width + (col + j)];
                    }
                }
                blurredImage->data[row * loadedPGMImage->width + col] = sum / (kernelSize * kernelSize);
            }
        }
        for (int i = 0; i < loadedPGMImage->width * loadedPGMImage->height; ++i) {
            loadedPGMImage->data[i] = blurredImage->data[i];
        }
        freePGMImage(blurredImage);
    } else if (isPPMImageLoaded) {
        PPMImage* blurredImage = createPPMImage(loadedPPMImage->width, loadedPPMImage->height);

        int kernelSize = 2 * level + 1;
        int halfKernelSize = kernelSize / 2;

        for (int row = halfKernelSize; row < loadedPPMImage->height - halfKernelSize; ++row) {
            for (int col = halfKernelSize; col < loadedPPMImage->width - halfKernelSize; ++col) {
                unsigned int sum = 0;
                for (int i = -halfKernelSize; i <= halfKernelSize; ++i) {
                    for (int j = -halfKernelSize; j <= halfKernelSize; ++j) {
                        sum += loadedPPMImage->data[3 * ((row + i) * loadedPPMImage->width + (col + j))];
                    }
                }
                blurredImage->data[3 * (row * loadedPPMImage->width + col)] = sum / (kernelSize * kernelSize);
            }
        }
        for (int i = 0; i < loadedPPMImage->width * loadedPPMImage->height * 3; ++i) {
            loadedPPMImage->data[i] = blurredImage->data[i];
        }
        freePPMImage(blurredImage);
    }
    printf("Effect applied: Blur (Level %d)\n", level);
}

void applyMirrorEffect() {
    if (loadedPGMImage != NULL) {
        // PGM Image Mirror Effect
        // Calculate the middle column
        int middleColumn = loadedPGMImage->width / 2;

        for (int row = 0; row < loadedPGMImage->height; ++row) {
            for (int col = 0; col < middleColumn; ++col) {
                int leftIndex = row * loadedPGMImage->width + col;
                int rightIndex = row * loadedPGMImage->width + (loadedPGMImage->width - 1 - col);

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

void applyImageSize() {

    int newWidth, newHeight;

    printf("Enter the new width and height (e.g., 1920x1080): ");
    scanf("%dx%d", &newWidth, &newHeight);
    if(loadedPGMImage != NULL) {
        PGMImage* resizedImage = createPGMImage(newWidth, newHeight);

        double widthScale = (double)loadedPGMImage->width / newWidth;
        double heightScale = (double)loadedPGMImage->height / newHeight;

        for (int row = 0; row < newHeight; ++row) {
            for (int col = 0; col < newWidth; ++col) {

                int originalRow = (int)(row * heightScale);
                int originalCol = (int)(col * widthScale);

                resizedImage->data[row * newWidth + col] = loadedPGMImage->data[originalRow * loadedPGMImage->width + originalCol];
            }
        }

        // Replace the original image with the resized image
        freePGMImage(loadedPGMImage);
        loadedPGMImage = resizedImage;

        printf("PGM Image resized to %dx%d.\n", newWidth, newHeight);
    }else if(loadedPPMImage != NULL){


    // Create a temporary PPM image with the new dimensions
    PPMImage* resizedImage = createPPMImage(newWidth, newHeight);

    // Calculate the scaling factors for width and height
    double widthScale = (double)loadedPPMImage->width / newWidth;
    double heightScale = (double)loadedPPMImage->height / newHeight;

    // Resize the image using nearest-neighbor interpolation
    for (int row = 0; row < newHeight; ++row) {
        for (int col = 0; col < newWidth; ++col) {
            // Calculate the corresponding pixel in the original image
            int originalRow = (int)(row * heightScale);
            int originalCol = (int)(col * widthScale);

            // Copy the pixel from the original image to the resized image
            resizedImage->data[row * newWidth + col] = loadedPPMImage->data[originalRow * loadedPPMImage->width + originalCol];
        }
    }

    // Replace the original image with the resized image
    freePPMImage(loadedPPMImage);
    loadedPPMImage = resizedImage;

    printf("PPM Image resized to %dx%d.\n", newWidth, newHeight);
    }
}

void applyImageRotation(double angle) {


    // Convert angle to radians
    double radians = angle * M_PI / 180.0;

    // Determine the type of image (PGM or PPM)
    int isPGM = (loadedPGMImage != NULL);

    // Set dimensions based on the type of image
    int width, height;
    if (isPGM) {
        width = loadedPGMImage->width;
        height = loadedPGMImage->height;
    } else { // PPM
        width = loadedPPMImage->width;
        height = loadedPPMImage->height;
    }

    // Create a temporary image with the same dimensions
    PGMImage* rotatedPGMImage = createPGMImage(width, height);
    PPMImage* rotatedPPMImage = createPPMImage(width, height);

    // Iterate through each pixel in the destination image
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            // Convert coordinates to center-relative
            int centerX = width / 2;
            int centerY = height / 2;
            int relX = col - centerX;
            int relY = row - centerY;

            // Rotate coordinates
            int newX = round(relX * cos(radians) - relY * sin(radians));
            int newY = round(relX * sin(radians) + relY * cos(radians));

            // Convert back to absolute coordinates
            newX += centerX;
            newY += centerY;

            // Check if the new coordinates are within bounds
            if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
                // Copy pixel value from source to destination
                if (isPGM) {
                    rotatedPGMImage->data[newY * width + newX] = loadedPGMImage->data[row * width + col];
                } else { // PPM
                    rotatedPPMImage->data[newY * width + newX] = loadedPPMImage->data[row * width + col];
                }
            }
        }
    }

    // Replace the original image with the rotated image
    if (isPGM) {
        freePGMImage(loadedPGMImage);
        loadedPGMImage = rotatedPGMImage;
        printf("PGM Image rotated by %f degrees.\n", angle);
    } else { // PPM
        freePPMImage(loadedPPMImage);
        loadedPPMImage = rotatedPPMImage;
        printf("PPM Image rotated by %f degrees.\n", angle);
    }
}

void applyPixelizationEffect(int blockSize) {


    if (loadedPGMImage != NULL) {
        // For PGM images
        int imageWidth = loadedPGMImage->width;
        int imageHeight = loadedPGMImage->height;
        unsigned char* imageData = loadedPGMImage->data;

        // Calculate the number of blocks in each dimension
        int blocksX = (int)ceil((double)imageWidth / blockSize);
        int blocksY = (int)ceil((double)imageHeight / blockSize);

        // Create a temporary image to store the pixelated result
        PGMImage* pixelatedImage = createPGMImage(imageWidth, imageHeight);

        // Apply the pixelation effect
        for (int blockX = 0; blockX < blocksX; ++blockX) {
            for (int blockY = 0; blockY < blocksY; ++blockY) {
                // Calculate the bounds of the current block
                int startX = blockX * blockSize;
                int startY = blockY * blockSize;
                int endX = fmin(startX + blockSize, imageWidth);
                int endY = fmin(startY + blockSize, imageHeight);

                // Calculate the average color of the current block
                int avgIntensity = 0;
                int pixelCount = 0;

                for (int x = startX; x < endX; ++x) {
                    for (int y = startY; y < endY; ++y) {
                        int index = y * imageWidth + x;
                        avgIntensity += imageData[index];
                        pixelCount++;
                    }
                }

                avgIntensity /= pixelCount;

                // Fill the current block with the average intensity
                for (int x = startX; x < endX; ++x) {
                    for (int y = startY; y < endY; ++y) {
                        int index = y * imageWidth + x;
                        pixelatedImage->data[index] = avgIntensity;
                    }
                }
            }
        }

        // Replace the original PGM image with the pixelated image
        freePGMImage(loadedPGMImage);
        loadedPGMImage = pixelatedImage;

        printf("Effect applied: Pixelation (PGM)\n");

    } else if (loadedPPMImage != NULL) {
        // For PPM images
        int imageWidth = loadedPPMImage->width;
        int imageHeight = loadedPPMImage->height;
        unsigned char* imageData = loadedPPMImage->data;

        // Calculate the number of blocks in each dimension
        int blocksX = (int)ceil((double)imageWidth / blockSize);
        int blocksY = (int)ceil((double)imageHeight / blockSize);

        // Create a temporary image to store the pixelated result
        PPMImage* pixelatedImage = createPPMImage(imageWidth, imageHeight);

        // Apply the pixelation effect
        for (int blockX = 0; blockX < blocksX; ++blockX) {
            for (int blockY = 0; blockY < blocksY; ++blockY) {
                // Calculate the bounds of the current block
                int startX = blockX * blockSize;
                int startY = blockY * blockSize;
                int endX = fmin(startX + blockSize, imageWidth);
                int endY = fmin(startY + blockSize, imageHeight);

                // Calculate the average color of the current block
                int avgRed = 0, avgGreen = 0, avgBlue = 0;
                int pixelCount = 0;

                for (int x = startX; x < endX; ++x) {
                    for (int y = startY; y < endY; ++y) {
                        int index = (y * imageWidth + x) * 3;  // For PPM images, each pixel has three components (RGB)
                        avgRed += imageData[index];
                        avgGreen += imageData[index + 1];
                        avgBlue += imageData[index + 2];
                        pixelCount++;
                    }
                }

                avgRed /= pixelCount;
                avgGreen /= pixelCount;
                avgBlue /= pixelCount;

                // Fill the current block with the average color
                for (int x = startX; x < endX; ++x) {
                    for (int y = startY; y < endY; ++y) {
                        int index = (y * imageWidth + x) * 3;
                        pixelatedImage->data[index] = avgRed;
                        pixelatedImage->data[index + 1] = avgGreen;
                        pixelatedImage->data[index + 2] = avgBlue;
                    }
                }
            }
        }

        // Replace the original PPM image with the pixelated image
        freePPMImage(loadedPPMImage);
        loadedPPMImage = pixelatedImage;

        printf("Effect applied: Pixelation (PPM)\n");
    }
}

void applyNegativeEffect() {


    if (loadedPGMImage != NULL) {
        // For PGM images
        int imageWidth = loadedPGMImage->width;
        int imageHeight = loadedPGMImage->height;
        unsigned char* imageData = loadedPGMImage->data;

        // Create a temporary image to store the negative result
        PGMImage* negativeImage = createPGMImage(imageWidth, imageHeight);

        // Apply the negative effect
        for (int i = 0; i < imageWidth * imageHeight; ++i) {
            negativeImage->data[i] = 255 - imageData[i];
        }

        // Replace the original PGM image with the negative image
        freePGMImage(loadedPGMImage);
        loadedPGMImage = negativeImage;

        printf("Effect applied: Negative (PGM)\n");

    } else if (loadedPPMImage != NULL) {
        // For PPM images
        int imageWidth = loadedPPMImage->width;
        int imageHeight = loadedPPMImage->height;
        unsigned char* imageData = loadedPPMImage->data;

        // Create a temporary image to store the negative result
        PPMImage* negativeImage = createPPMImage(imageWidth, imageHeight);

        // Apply the negative effect
        for (int i = 0; i < imageWidth * imageHeight * 3; ++i) {
            negativeImage->data[i] = 255 - imageData[i];
        }

        // Replace the original PPM image with the negative image
        freePPMImage(loadedPPMImage);
        loadedPPMImage = negativeImage;

        printf("Effect applied: Negative (PPM)\n");
    }
}

void applyGrayscaleEffect() {


    if (loadedPGMImage != NULL) {
        // For PGM images
        int imageWidth = loadedPGMImage->width;
        int imageHeight = loadedPGMImage->height;
        unsigned char* imageData = loadedPGMImage->data;

        // The grayscale conversion logic for PGM images (already grayscale)

        printf("Effect applied: Convert to Grayscale (PGM)\n");

    } else if (loadedPPMImage != NULL) {
        // For PPM images
        int imageWidth = loadedPPMImage->width;
        int imageHeight = loadedPPMImage->height;
        unsigned char* imageData = loadedPPMImage->data;

        // Create a temporary PGM image to store the grayscale result
        PGMImage* grayscaleImage = createPGMImage(imageWidth, imageHeight);

        // Convert the PPM image to grayscale (average of R, G, B values)
        for (int i = 0; i < imageWidth * imageHeight; ++i) {
            grayscaleImage->data[i] = (imageData[i * 3] + imageData[i * 3 + 1] + imageData[i * 3 + 2]) / 3;
        }

        // Replace the original PPM image with the grayscale image
        freePPMImage(loadedPPMImage);
        loadedPGMImage = grayscaleImage;

        printf("Effect applied: Convert to Grayscale (PPM)\n");
    }
}

unsigned char getPixelValue(const unsigned char* data, int width, int x, int y) {
    return data[y * width + x];
}

void setPixelValue(unsigned char* data, int width, int x, int y, unsigned char value) {
    data[y * width + x] = value;
}

void generateMipmap() {
    int baseWidth, baseHeight;
    unsigned char* baseData;

    // Determine the image type and set baseWidth, baseHeight, and baseData accordingly
    if (loadedPGMImage != NULL) {
        baseWidth = loadedPGMImage->width;
        baseHeight = loadedPGMImage->height;
        baseData = loadedPGMImage->data;
    } else if (loadedPPMImage != NULL) {
        baseWidth = loadedPPMImage->width;
        baseHeight = loadedPPMImage->height;
        baseData = loadedPPMImage->data;
    } else {
        fprintf(stderr, "Error: No image loaded.\n");
        return;
    }

    while (baseWidth > 1 && baseHeight > 1) {
        // Create a smaller image with half the width and height
        int newWidth = baseWidth / 2;
        int newHeight = baseHeight / 2;
        unsigned char* newData;

        if (loadedPGMImage != NULL) {
            newData = malloc(newWidth * newHeight * sizeof(unsigned char));

            // Downsample using nearest-neighbor interpolation for PGM image
            for (int y = 0; y < newHeight; ++y) {
                for (int x = 0; x < newWidth; ++x) {
                    // Sample the pixel value from the original image
                    unsigned char sample = getPixelValue(baseData, baseWidth, x * 2, y * 2);
                    // Set the pixel value in the new image
                    setPixelValue(newData, newWidth, x, y, sample);
                }
            }
        } else { // loadedPPMImage != NULL
            newData = malloc(newWidth * newHeight * 3 * sizeof(unsigned char));

            // Downsample using nearest-neighbor interpolation for PPM image
            for (int y = 0; y < newHeight; ++y) {
                for (int x = 0; x < newWidth; ++x) {
                    for (int c = 0; c < 3; ++c) {
                        // Sample the pixel value from the original image
                        unsigned char sample = getPixelValue(baseData, baseWidth * 3, x * 2 * 3, y * 2) / 3;
                        // Set the pixel value in the new image
                        setPixelValue(newData, newWidth * 3, x * 3, y, sample);
                    }
                }
            }
        }

        // Free the previous data and update the image
        free(baseData);
        baseData = newData;
        baseWidth = newWidth;
        baseHeight = newHeight;

        // Output for demonstration purposes
        printf("Generated Mipmap level: %dx%d\n", baseWidth, baseHeight);
    }

    // Update the loaded image with the final Mipmap level
    if (loadedPGMImage != NULL) {
        loadedPGMImage->width = baseWidth;
        loadedPGMImage->height = baseHeight;
        loadedPGMImage->data = baseData;
    } else { // loadedPPMImage != NULL
        loadedPPMImage->width = baseWidth;
        loadedPPMImage->height = baseHeight;
        loadedPPMImage->data = baseData;
    }
}

void applySobelEffect() {


    // Créer une image temporaire pour stocker le résultat du filtre de Sobel
    PGMImage* sobelImage = createPGMImage(loadedPGMImage->width, loadedPGMImage->height);

    // Définir les noyaux de Sobel pour la détection de contour
    int sobelKernelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int sobelKernelY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Appliquer le filtre de Sobel
    for (int row = 1; row < loadedPGMImage->height - 1; ++row) {
        for (int col = 1; col < loadedPGMImage->width - 1; ++col) {
            int gx = 0, gy = 0;

            // Appliquer le noyau de Sobel en X et Y
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    gx += sobelKernelX[i + 1][j + 1] * loadedPGMImage->data[(row + i) * loadedPGMImage->width + (col + j)];
                    gy += sobelKernelY[i + 1][j + 1] * loadedPGMImage->data[(row + i) * loadedPGMImage->width + (col + j)];
                }
            }

            // Calculer le gradient total
            int gradient = (int)sqrt(gx * gx + gy * gy);

            // Limiter la valeur du gradient à 255
            sobelImage->data[row * loadedPGMImage->width + col] = (unsigned char)(gradient > 255 ? 255 : gradient);
        }
    }

    // Copier l'image résultante dans l'image originale
    for (int i = 0; i < loadedPGMImage->width * loadedPGMImage->height; ++i) {
        loadedPGMImage->data[i] = sobelImage->data[i];
    }

    // Libérer l'image temporaire
    freePGMImage(sobelImage);

    printf("Effet appliqué : Détection de contour (Sobel)\n");
}

void applyGaussianEffect() {


    // Créer une image temporaire pour stocker le résultat de l'effet gaussien
    PGMImage* gaussianImage = createPGMImage(loadedPGMImage->width, loadedPGMImage->height);

    // Définir la taille du noyau gaussien (3x3 par exemple)
    int kernelSize = 3;
    double sigma = 1.0;

    // Calculer la taille du noyau (impair)
    int halfKernelSize = kernelSize / 2;

    // Créer le noyau gaussien
    double** gaussianKernel = (double**)malloc(kernelSize * sizeof(double*));
    for (int i = 0; i < kernelSize; ++i) {
        gaussianKernel[i] = (double*)malloc(kernelSize * sizeof(double));
    }

    // Remplir le noyau gaussien
    double sum = 0.0;
    for (int i = -halfKernelSize; i <= halfKernelSize; ++i) {
        for (int j = -halfKernelSize; j <= halfKernelSize; ++j) {
            gaussianKernel[i + halfKernelSize][j + halfKernelSize] = exp(-(i * i + j * j) / (2 * sigma * sigma));
            sum += gaussianKernel[i + halfKernelSize][j + halfKernelSize];
        }
    }

    // Normaliser le noyau gaussien
    for (int i = 0; i < kernelSize; ++i) {
        for (int j = 0; j < kernelSize; ++j) {
            gaussianKernel[i][j] /= sum;
        }
    }

    // Appliquer le noyau gaussien à chaque pixel de l'image
    for (int row = halfKernelSize; row < loadedPGMImage->height - halfKernelSize; ++row) {
        for (int col = halfKernelSize; col < loadedPGMImage->width - halfKernelSize; ++col) {
            double sum = 0.0;
            for (int i = -halfKernelSize; i <= halfKernelSize; ++i) {
                for (int j = -halfKernelSize; j <= halfKernelSize; ++j) {
                    sum += loadedPGMImage->data[(row + i) * loadedPGMImage->width + (col + j)] * gaussianKernel[i + halfKernelSize][j + halfKernelSize];
                }
            }
            gaussianImage->data[row * loadedPGMImage->width + col] = (unsigned char)sum;
        }
    }

    // Copier l'image résultante dans l'image originale
    for (int i = 0; i < loadedPGMImage->width * loadedPGMImage->height; ++i) {
        loadedPGMImage->data[i] = gaussianImage->data[i];
    }

    // Libérer le noyau gaussien
    for (int i = 0; i < kernelSize; ++i) {
        free(gaussianKernel[i]);
    }
    free(gaussianKernel);

    // Libérer l'image temporaire
    freePGMImage(gaussianImage);

    printf("Effet appliqué : Effet gaussien\n");
}