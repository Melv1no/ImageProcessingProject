#include "gui.h"
#include <gtk/gtk.h>
#include "file_io.h"
#include "effects.h"
#include <stdbool.h>
#define MAX_FILENAME_SIZE 100
#define PPM_FILE_EXT ".ppm"
#define PGM_FILE_EXT ".pgm"


GtkTextBuffer *log_buffer;
GtkWidget *image_drawing_area;

void displayImage()
{
    if (loadedPGMImage != NULL)
    {
        PGMImage *pgmImage = loadedPGMImage;
        if (pgmImage != NULL && pgmImage->data != NULL)
        {
            GdkPixbuf *pixbuf = gdk_pixbuf_new_from_data(
                    pgmImage->data,
                    GDK_COLORSPACE_RGB,
                    FALSE,
                    8,
                    pgmImage->width,
                    pgmImage->height,
                    pgmImage->width * 3,
                    NULL,
                    NULL);

            // Get the aspect ratio of the image
            double aspect_ratio = (double)pgmImage->width / (double)pgmImage->height;

            // Calculate the maximum size that maintains the aspect ratio
            int max_width = gtk_widget_get_allocated_width(image_drawing_area);
            int max_height = gtk_widget_get_allocated_height(image_drawing_area);
            int display_width, display_height;

            display_width = 600;
            display_height = 300;

            // Scale the image to fit within the calculated dimensions
            GdkPixbuf *scaled_pixbuf = gdk_pixbuf_scale_simple(
                    pixbuf,
                    display_width,
                    display_height,
                    GDK_INTERP_BILINEAR);

            gtk_image_set_from_pixbuf(GTK_IMAGE(image_drawing_area), scaled_pixbuf);

            g_object_unref(pixbuf);
            g_object_unref(scaled_pixbuf);
        }
    }
    else if (loadedPPMImage != NULL)
    {
        PPMImage *ppmImage = loadedPPMImage;
        if (ppmImage != NULL && ppmImage->data != NULL)
        {
            GdkPixbuf *pixbuf = gdk_pixbuf_new_from_data(
                    ppmImage->data,
                    GDK_COLORSPACE_RGB,
                    FALSE,
                    8,
                    ppmImage->width,
                    ppmImage->height,
                    ppmImage->width * 3,
                    NULL,
                    NULL);

            // Get the aspect ratio of the image
            double aspect_ratio = (double)ppmImage->width / (double)ppmImage->height;

            // Calculate the maximum size that maintains the aspect ratio
            int max_width = gtk_widget_get_allocated_width(image_drawing_area);
            int max_height = gtk_widget_get_allocated_height(image_drawing_area);
            int display_width, display_height;

            display_width = 600;
            display_height = 300;

            // Scale the image to fit within the calculated dimensions
            GdkPixbuf *scaled_pixbuf = gdk_pixbuf_scale_simple(
                    pixbuf,
                    display_width,
                    display_height,
                    GDK_INTERP_BILINEAR);

            gtk_image_set_from_pixbuf(GTK_IMAGE(image_drawing_area), scaled_pixbuf);

            g_object_unref(pixbuf);
            g_object_unref(scaled_pixbuf);
        }
    }
    // Add conditions for other image types if needed
}



void append_to_log(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    gchar *formatted_text = g_strdup_vprintf(format, args);

    va_end(args);

    GtkTextIter end;
    gtk_text_buffer_get_end_iter(log_buffer, &end);

    gtk_text_buffer_insert(log_buffer, &end, formatted_text, -1);

    g_free(formatted_text);
}

void onClick_menu_item_save(GtkWidget *widget, gpointer data)
{
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER;
    gint res;

    dialog = gtk_file_chooser_dialog_new("Select Folder",
                                         GTK_WINDOW(data),
                                         action,
                                         "_Cancel",
                                         GTK_RESPONSE_CANCEL,
                                         "_Save",
                                         GTK_RESPONSE_ACCEPT,
                                         NULL);

    res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *folder_path;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        folder_path = gtk_file_chooser_get_filename(chooser);
        g_print("Selected Folder: %s\n", folder_path);

        // Now, you have the folder_path where the user wants to save the image.
        // You can implement the logic to save the image to this folder.
        append_to_log("Your image saved as: ");
        append_to_log(folder_path);
        append_to_log("\n");


        savePGMImage("/mnt/c/test.pgm");
        g_free(folder_path);
    }

    gtk_widget_destroy(dialog);

    // Append the log message


}

void onClick_menu_item_exit(GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}

void onClick_menu_item_mirror(GtkWidget *widget, gpointer data)
{
    // Your code for "Mirror" menu item click handling goes here
    // Append the log message
    append_to_log("Mirror menu item clicked.\n");
}

void onClick_menu_item_negative(GtkWidget *widget, gpointer data)
{
    // Your code for "Negative" menu item click handling goes here
    // Append the log message
    if(loadedPGMImage != NULL){
        append_to_log("Negative effect applied.\n");
        applyNegativeEffect(loadedPGMImage);
        displayImage();
    }else if( loadedPPMImage != NULL){
        append_to_log("Negative effect applied.\n");
        applyNegativeEffect(loadedPPMImage);
        displayImage();
    }else{
        append_to_log("Firstly load image.\n");
    }
}

void onClick_menu_item_open(GtkWidget *widget, gpointer data)
{
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;

    dialog = gtk_file_chooser_dialog_new("Open File",
                                         GTK_WINDOW(data),
                                         action,
                                         "_Cancel",
                                         GTK_RESPONSE_CANCEL,
                                         "_Open",
                                         GTK_RESPONSE_ACCEPT,
                                         NULL);

    res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);
        g_print("Selected File: %s\n", filename);
        char *extension = strrchr(filename, '.');
        if (extension != NULL)
        {
            if (strcmp(extension, PGM_FILE_EXT) == 0)
            {
                if (loadPGMImage(filename) == 0)
                {
                    printf("PGM Image loaded successfully.\n");
                    append_to_log("PGM Image loaded successfully.\n");
                    displayImage();
                }
                else
                {
                    printf("Failed to load the PGM image. Exiting.\n");
                    append_to_log("Failed to load the PGM image. Exiting.\n");
                    return;
                }
            }
            else if (strcmp(extension, PPM_FILE_EXT) == 0)
            {
                if (loadPPMImage(filename) == 0)
                {
                    printf("PPM Image loaded successfully.\n");
                    append_to_log("PPM Image loaded successfully.\n");
                    displayImage();
                }
                else
                {
                    printf("Failed to load the PPM image. Exiting.\n");
                    append_to_log("Failed to load the PPM image. Exiting.\n");
                    return;
                }
            }
            else
            {
                printf("Unsupported file format. Exiting.\n");
                append_to_log("Unsupported file format. Exiting.\n");
                return;
            }
        }
        else
        {
            printf("Invalid filename. Exiting.\n");
            append_to_log("Invalid filename. Exiting.\n");
            return;
        }
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

void create_gui(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "ImageProcessingProject");
    gtk_window_set_default_size(GTK_WINDOW(window), 1920, 1080);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a vertical box
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    image_drawing_area = gtk_image_new();

// Set the fixed size of the image_drawing_area
    gtk_widget_set_size_request(image_drawing_area, 600, 300);

    gtk_box_pack_start(GTK_BOX(vbox), image_drawing_area, TRUE, TRUE, 0);


    // Create a menu bar
    GtkWidget *menubar = gtk_menu_bar_new();
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

    // Create a scrolled window for the log box
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    // Set the height of the scrolled window to 1/4 of the window size
    GdkGeometry hints;
    hints.min_height = hints.max_height = 270;
    gtk_window_set_geometry_hints(GTK_WINDOW(scrolled_window), NULL, &hints, GDK_HINT_MIN_SIZE | GDK_HINT_MAX_SIZE);

    gtk_box_pack_end(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0);

    // Create a text view for the log
    GtkWidget *log_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(log_view), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(log_view), FALSE);

    // Get the text buffer associated with the text view
    log_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(log_view));

    // Pack the text view into the scrolled window
    gtk_container_add(GTK_CONTAINER(scrolled_window), log_view);

    // Create menu items and connect signals
    GtkWidget *menu_file = gtk_menu_new();
    GtkWidget *menu_item_file = gtk_menu_item_new_with_label("File");
    GtkWidget *menu_item_open = gtk_menu_item_new_with_label("Open");
    GtkWidget *menu_item_save = gtk_menu_item_new_with_label("Save");
    GtkWidget *menu_item_exit = gtk_menu_item_new_with_label("Exit");

    GtkWidget *menu_effect = gtk_menu_new();
    GtkWidget *menu_item_effect = gtk_menu_item_new_with_label("Effects");
    GtkWidget *menu_item_mirror = gtk_menu_item_new_with_label("Mirror");
    GtkWidget *menu_item_negative = gtk_menu_item_new_with_label("Negative");

    g_signal_connect(menu_item_open, "activate", G_CALLBACK(onClick_menu_item_open), window);
    g_signal_connect(menu_item_save, "activate", G_CALLBACK(onClick_menu_item_save), NULL);
    g_signal_connect(menu_item_exit, "activate", G_CALLBACK(onClick_menu_item_exit), NULL);
    g_signal_connect(menu_item_mirror, "activate", G_CALLBACK(onClick_menu_item_mirror), NULL);
    g_signal_connect(menu_item_negative, "activate", G_CALLBACK(onClick_menu_item_negative), NULL);

    gtk_menu_shell_append(GTK_MENU_SHELL(menu_file), menu_item_open);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_file), menu_item_save);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_file), menu_item_exit);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_effect), menu_item_mirror);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_effect), menu_item_negative);

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item_file), menu_file);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menu_item_file);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item_effect), menu_effect);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menu_item_effect);

    // Display all the elements
    gtk_widget_show_all(window);

    // Start the GTK main loop
    append_to_log("File > Open > Choose your ppm/pgm image.\n");
    gtk_main();
}
