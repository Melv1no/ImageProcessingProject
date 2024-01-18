#include "gui.h"
#include <gtk/gtk.h>
#include "file_io.h"
#include "effects.h"
#define MAX_FILENAME_SIZE 100
#define PPM_FILE_EXT ".ppm"
#define PGM_FILE_EXT ".pgm"


static cairo_surface_t *image_surface = NULL;
GtkTextBuffer* log_buffer;
char oldfilename;
cairo_surface_t* cairoSurface;

void append_to_log(const char* format, ...) {
    printf(format);
    va_list args;
    va_start(args, format);
    gchar* formatted_text = g_strdup_vprintf(format, args);
    va_end(args);
    GtkTextIter end;
    gtk_text_buffer_get_end_iter(log_buffer, &end);
    gtk_text_buffer_insert(log_buffer, &end, formatted_text, -1);
    g_free(formatted_text);
}

void onClick_menu_item_exit(GtkWidget* widget, gpointer data) {
    gtk_main_quit();
}

void onClick_menu_item_save(GtkWidget* widget, gpointer data) {
    GtkWidget* dialog;
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
    if (res == GTK_RESPONSE_ACCEPT) {
        char* folder_path;
        GtkFileChooser* chooser = GTK_FILE_CHOOSER(dialog);
        folder_path = gtk_file_chooser_get_filename(chooser);
        g_print("Selected Folder: %s\n", folder_path);

        append_to_log("Your image saved as: ");
        append_to_log("oldfilename");
        append_to_log("\n");
        savePGMImage("oldfilename.pgm");
        g_free(folder_path);
    }

    gtk_widget_destroy(dialog);
}

void onClick_menu_item_mirror(GtkWidget* widget, gpointer data) {
    append_to_log("Mirror menu item clicked.\n");
}

void onClick_menu_item_negative(GtkWidget* widget, gpointer data) {

    /*if (loadedPGMImage != NULL) {
        append_to_log("Negative effect applied.\n");
        applyNegativeEffect(loadedPGMImage);
        /*image_surface = cairo_image_surface_create_for_data(
                            loadedPGMImage->data,
                            CAIRO_FORMAT_A8,
                            loadedPGMImage->width,
                            loadedPGMImage->height,
                            loadedPGMImage->width
             );
    }
    else if (loadedPPMImage != NULL) {
        append_to_log("Negative effect applied.\n");
        applyNegativeEffect(loadedPPMImage);
        image_surface = cairo_image_surface_create_for_data(
                                    loadedPPMImage->data,
                                    CAIRO_FORMAT_A8,
                                    loadedPPMImage->width,
                                    loadedPPMImage->height,
                                    loadedPPMImage->width
                     );
    }
    else {
        append_to_log("Firstly load image.\n");
    }*/

}

void onClick_menu_item_open(GtkWidget* widget, gpointer data) {
    GtkWidget* dialog;
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
    if (res == GTK_RESPONSE_ACCEPT) {
        char* filename;

        GtkFileChooser* chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename(chooser);
        g_print("Selected File: %s\n", filename);
        char* extension = strrchr(filename, '.');
        if (extension != NULL) {
            if (strcmp(extension, PGM_FILE_EXT) == 0) {
                if (loadPGMImage(filename) == 0) {
                    printf("PGM Image loaded successfully.\n");
                    append_to_log("PGM Image loaded successfully.\n");
                    image_surface = cairo_image_surface_create_for_data(
                                  loadedPGMImage->data,
                                  CAIRO_FORMAT_A8,
                                  loadedPGMImage->width,
                                  loadedPGMImage->height,
                                  loadedPGMImage->width
                   );
                }
                else {
                    printf("Failed to load the PGM image. Exiting.\n");
                    append_to_log("Failed to load the PGM image. Exiting.\n");
                    return;
                }
            }
            else if (strcmp(extension, PPM_FILE_EXT) == 0) {
                if (loadPPMImage(filename) == 0) {
                    printf("PPM Image loaded successfully.\n");
                    append_to_log("PPM Image loaded successfully.\n");
                    image_surface = cairo_image_surface_create_for_data(
                                    loadedPPMImage->data,
                                    CAIRO_FORMAT_A8,
                                    loadedPPMImage->width,
                                    loadedPPMImage->height,
                                    loadedPPMImage->width);
                }
                else {
                    printf("Failed to load the PPM image. Exiting.\n");
                    append_to_log("Failed to load the PPM image. Exiting.\n");
                    return;
                }
            }
            else {
                printf("Unsupported file format. Exiting.\n");
                append_to_log("Unsupported file format. Exiting.\n");
                return;
            }
        }
        else {
            printf("Invalid filename. Exiting.\n");
            append_to_log("Invalid filename. Exiting.\n");
            return;
        }
        g_free(filename);
    }
    gtk_widget_destroy(dialog);
}

void draw_image(GtkWidget* widget, cairo_t *cr) {
    if (image_surface != NULL) {
        gtk_widget_set_size_request(widget, cairo_image_surface_get_width(image_surface),
                            cairo_image_surface_get_height(image_surface));
        cairo_set_source_surface(cr, image_surface, 0, 0);
        cairo_paint(cr);
    }
}

gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
        draw_image(widget,cr);
    return FALSE;
}

void create_gui(int argc, char* argv[]) {
    gtk_init(&argc, &argv);
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "ImageProcessingProject");
    gtk_window_set_default_size(GTK_WINDOW(window), 960, 540);

    GdkPixbuf* icon = gdk_pixbuf_new_from_file("images/logo.png", NULL);
    if (icon != NULL) {
        gtk_window_set_icon(GTK_WINDOW(window), icon);
    }

    GtkWidget* vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *drawing_area = gtk_drawing_area_new();


    gtk_widget_set_size_request(drawing_area, 300, 150);
    GtkWidget* alignment = gtk_alignment_new(0.5, 0.5, 0, 0);
    gtk_box_pack_start(GTK_BOX(vbox), alignment, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(alignment), drawing_area);

    GtkWidget* menubar = gtk_menu_bar_new();
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

    GtkWidget* scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    GdkGeometry hints;
    hints.min_height = hints.max_height = 270;
    gtk_window_set_geometry_hints(GTK_WINDOW(scrolled_window), NULL, &hints, GDK_HINT_MIN_SIZE | GDK_HINT_MAX_SIZE);
    gtk_box_pack_end(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0);

    GtkWidget* log_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(log_view), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(log_view), FALSE);
    log_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(log_view));

    gtk_container_add(GTK_CONTAINER(scrolled_window), log_view);
    GtkWidget* menu_file = gtk_menu_new();
    GtkWidget* menu_item_file = gtk_menu_item_new_with_label("File");
    GtkWidget* menu_item_open = gtk_menu_item_new_with_label("Open");
    GtkWidget* menu_item_save = gtk_menu_item_new_with_label("Save");
    GtkWidget* menu_item_exit = gtk_menu_item_new_with_label("Exit");

    GtkWidget* menu_effect = gtk_menu_new();
    GtkWidget* menu_item_effect = gtk_menu_item_new_with_label("Effects");
    GtkWidget* menu_item_mirror = gtk_menu_item_new_with_label("Mirror");
    GtkWidget* menu_item_negative = gtk_menu_item_new_with_label("Negative");

    g_signal_connect(menu_item_open, "activate", G_CALLBACK(onClick_menu_item_open), window);
    g_signal_connect(menu_item_save, "activate", G_CALLBACK(onClick_menu_item_save), window);
    g_signal_connect(menu_item_exit, "activate", G_CALLBACK(onClick_menu_item_exit), window);
    g_signal_connect(menu_item_mirror, "activate", G_CALLBACK(onClick_menu_item_mirror), window);
    g_signal_connect(menu_item_negative, "activate", G_CALLBACK(onClick_menu_item_negative), window);
    g_signal_connect(drawing_area, "draw", G_CALLBACK(on_draw_event), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_menu_shell_append(GTK_MENU_SHELL(menu_file), menu_item_open);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_file), menu_item_save);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_file), menu_item_exit);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_effect), menu_item_mirror);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_effect), menu_item_negative);

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item_file), menu_file);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menu_item_file);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item_effect), menu_effect);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menu_item_effect);

    gtk_widget_show_all(window);

    append_to_log("File > Open > Choose your ppm/pgm image.\n");
    gtk_main();
}