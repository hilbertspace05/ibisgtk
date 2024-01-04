#include "buttons.h"
#include "viewer.h"

Buttons::Buttons(GtkWidget *win) {
    next_button = gtk_button_new_from_icon_name("go-next", GTK_ICON_SIZE_BUTTON);
    gtk_widget_set_name(next_button, "circular-button");
    g_signal_connect(next_button, "clicked", G_CALLBACK(on_next_page), NULL);

    prev_button = gtk_button_new_from_icon_name("go-previous", GTK_ICON_SIZE_BUTTON);
    gtk_widget_set_name(prev_button, "circular-button");
    g_signal_connect(prev_button, "clicked", G_CALLBACK(on_previous_page), NULL);

    zoom_in_button = gtk_button_new_from_icon_name("zoom-in", GTK_ICON_SIZE_BUTTON);
    gtk_widget_set_name(zoom_in_button, "circular-button");
    g_signal_connect(zoom_in_button, "clicked", G_CALLBACK(on_zoom_in), NULL);

    zoom_out_button = gtk_button_new_from_icon_name("zoom-out", GTK_ICON_SIZE_BUTTON);
    gtk_widget_set_name(zoom_out_button, "circular-button");
    g_signal_connect(zoom_out_button, "clicked", G_CALLBACK(on_zoom_out), NULL);

    up_button = gtk_button_new_from_icon_name("go-up", GTK_ICON_SIZE_BUTTON);
    gtk_widget_set_name(up_button, "circular-button");
    g_signal_connect(up_button, "clicked", G_CALLBACK(scroll_up), NULL);

    down_button = gtk_button_new_from_icon_name("go-down", GTK_ICON_SIZE_BUTTON);
    gtk_widget_set_name(down_button, "circular-button");
    g_signal_connect(down_button, "clicked", G_CALLBACK(scroll_down), NULL);

    left_button = gtk_button_new_from_icon_name("go-previous", GTK_ICON_SIZE_BUTTON);
    gtk_widget_set_name(left_button, "circular-button");
    g_signal_connect(left_button, "clicked", G_CALLBACK(scroll_left), NULL);

    right_button = gtk_button_new_from_icon_name("go-next", GTK_ICON_SIZE_BUTTON);
    gtk_widget_set_name(right_button, "circular-button");
    g_signal_connect(right_button, "clicked", G_CALLBACK(scroll_right), NULL);

    //GtkWidget *fullscreen_button = gtk_button_new_with_label("Toggle Fullscreen");
    //g_signal_connect(fullscreen_button, "clicked", G_CALLBACK(on_fullscreen_toggle), win);
    fullscreen_button = gtk_button_new_with_label("Fullscreen");
    g_signal_connect(fullscreen_button, "clicked", G_CALLBACK(on_fullscreen_button_clicked), win);
    gtk_widget_set_halign(fullscreen_button, GTK_ALIGN_END);
    gtk_widget_set_valign(fullscreen_button, GTK_ALIGN_START);
}

gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
        switch (event->keyval) {
            case GDK_KEY_Up:
                scroll_up();
                break;
            case GDK_KEY_Down:
                scroll_down();
                break;
            case GDK_KEY_comma:
                scroll_left();
                break;
            case GDK_KEY_period:
                scroll_right();
                break;
            case GDK_KEY_minus:
                on_zoom_out(widget, user_data);
                break;
            case GDK_KEY_equal:
                on_zoom_in(widget, user_data);
                break;
            case GDK_KEY_Left:
                on_previous_page(widget, user_data);
                break;
            case GDK_KEY_Right:
                on_next_page(widget, user_data);
                break;
            default:
                return FALSE;
        }
        return TRUE;
    }