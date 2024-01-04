#ifndef BUTTONS_H
#define BUTTONS_H

#include <gtk/gtk.h>

gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data);

class Buttons {
public:
    GtkWidget *next_button;
    GtkWidget *prev_button;
    GtkWidget *zoom_in_button;
    GtkWidget *zoom_out_button;
    GtkWidget *fullscreen_button;
    GtkWidget *up_button;
    GtkWidget *down_button;
    GtkWidget *left_button;
    GtkWidget *right_button;

    Buttons(GtkWidget *win);
};

#endif // BUTTONS_H