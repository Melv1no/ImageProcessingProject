/*
 * Author: Melvin OLIVET
 * Date: {{publish_date}}
 * Description:
 */

#include <stdlib.h>
#include <stdio.h>
#include "image.h"

PGMImage* createPGMImage(int width, int height) {
    PGMImage* image = (PGMImage*)malloc(sizeof(PGMImage));

    if (image == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for PGMImage.\n");
        exit(EXIT_FAILURE);
    }

    image->width = width;
    image->height = height;
    image->data = (unsigned char*)malloc(width * height * sizeof(unsigned char));

    if (image->data == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for image data.\n");
        free(image);
        exit(EXIT_FAILURE);
    }

    return image;
}

PPMImage* createPPMImage(int width, int height) {
    PPMImage* image = (PPMImage*)malloc(sizeof(PPMImage));

    if (image == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for PPMImage.\n");
        exit(EXIT_FAILURE);
    }

    image->width = width;
    image->height = height;
    image->data = (unsigned char*)malloc(3 * width * height * sizeof(unsigned char));

    if (image->data == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for image data.\n");
        free(image);
        exit(EXIT_FAILURE);
    }

    return image;
}

void freePGMImage(PGMImage* image) {
    free(image->data);
    free(image);
}
void freePPMImage(PPMImage* image) {
    free(image->data);
    free(image);
}


