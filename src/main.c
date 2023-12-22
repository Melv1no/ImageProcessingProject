/*
 * Author: Melvin OLIVET
 * Date: {{publish_date}}
 * Description: main function
 */

#include <stdio.h>
#include <string.h>

#include "menu.h"
#include "file_io.h"
#include "gui.h"
#include <gtk/gtk.h>

#define MAX_FILENAME_SIZE 100
#define PPM_FILE_EXT ".ppm"
#define PGM_FILE_EXT ".pgm"


int main(int argc, char *argv[])
{
#ifdef _WIN32

    int choice;
    char filename[MAX_FILENAME_SIZE];

    printf("Enter the filename of the image to load: ");
    scanf("%s", filename);

    char* extension = strrchr(filename, '.');
    if (extension != NULL) {
        if (strcmp(extension, PGM_FILE_EXT) == 0) {
            if (loadPGMImage(filename) == 0) {
                printf("PGM Image loaded successfully.\n");
            } else {
                printf("Failed to load the PGM image. Exiting.\n");
                return 1;
            }
        } else if (strcmp(extension, PPM_FILE_EXT) == 0) {
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
        printf("\nImage Processing Menu:\n");
        printf("1. Apply Effect\n");
        printf("2. Save Image\n");
        printf("3. Load other image\n");
        printf("4. developer tools\n");
        printf("99. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayApplyEffectMenu();
                break;
            case 2:
                saveImage();
                break;
            case 3:
                cleanupImages();
                main(NULL,NULL);
                break;
            case 4:
                debug();
                break;
            case 99:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 99);

    return 0;

#else
    create_gui(argc, argv);
#endif
}
