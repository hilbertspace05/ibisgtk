#include <gtk/gtk.h>
#include <mupdf/fitz.h>
#include "viewer.h"
#include "buttons.h"


int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    ctx = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED);
    fz_register_document_handlers(ctx);
    doc = fz_open_document(ctx, argv[1]);


    GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(win, "destroy", G_CALLBACK(gtk_main_quit), NULL);


    Buttons buttons(win);


    g_signal_connect(win, "key-press-event", G_CALLBACK(on_key_press), NULL);

    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
        "#circular-button {"
        "  border-radius: 50%;"
        "}",
        -1, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), 
        GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    //GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    //gtk_box_pack_start(GTK_BOX(hbox), buttons.prev_button, FALSE, FALSE, 0);
    //gtk_box_pack_start(GTK_BOX(hbox), buttons.zoom_in_button, FALSE, FALSE, 0);
    //gtk_box_pack_start(GTK_BOX(hbox), buttons.zoom_out_button, FALSE, FALSE, 0);
    //gtk_box_pack_start(GTK_BOX(hbox), buttons.next_button, FALSE, FALSE, 0);
    
    GtkWidget *button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(button_box), buttons.prev_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(button_box), buttons.zoom_in_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(button_box), buttons.zoom_out_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(button_box), buttons.next_button, TRUE, TRUE, 0);

    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_set_center_widget(GTK_BOX(hbox), button_box);


    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);


    darea = gtk_image_new();

    // Crie um novo GtkScrolledWindow
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    init_scrolled_window(GTK_SCROLLED_WINDOW(scrolled_window));

    // Adicione o darea ao GtkScrolledWindow
    gtk_container_add(GTK_CONTAINER(scrolled_window), darea);

    // Adicione o GtkScrolledWindow ao GtkBox em vez do darea
    gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0);

    GtkWidget *hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(hbox2), vbox, TRUE, TRUE, 0);
    GtkWidget *vbox2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *hbox3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget *hbox4 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);


    gtk_box_pack_start(GTK_BOX(vbox2), buttons.fullscreen_button, TRUE, FALSE, 0);
    gtk_widget_set_size_request(GTK_WIDGET(vbox2), 120, 500);
    gtk_box_pack_start(GTK_BOX(hbox3), buttons.up_button, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox4), buttons.left_button, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox4), buttons.down_button, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox4), buttons.right_button, TRUE, FALSE, 0);
    //gtk_widget_set_size_request(GTK_WIDGET(hbox4), 150, 100);

    gtk_box_pack_start(GTK_BOX(hbox2), vbox2, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox2), hbox3, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox2), hbox4, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(win), hbox2);

    gtk_widget_show_all(win);
    //load_page(0);
    gtk_main();

    return 0;
}
