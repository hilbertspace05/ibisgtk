#include <stdio.h>
#include <gtk/gtk.h>
#include <mupdf/fitz.h>
#include "viewer.h"
#include "db.h"

fz_context *ctx;
fz_document *doc;
fz_pixmap *pix;
GtkWidget *darea;
double zoom_level = 1.0;
static gboolean is_fullscreen = FALSE;
GtkAdjustment *vadjustment;
GtkAdjustment *hadjustment;

gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    int width = fz_pixmap_width(ctx, pix);
    int height = fz_pixmap_height(ctx, pix);
    unsigned char *samples = fz_pixmap_samples(ctx, pix);

    // Convert from ARGB to RGBA
    for (int i = 0; i < width * height; i++) {
        unsigned char a = samples[i*4 + 0];
        unsigned char r = samples[i*4 + 1];
        unsigned char g = samples[i*4 + 2];
        unsigned char b = samples[i*4 + 3];
        samples[i*4 + 0] = r;
        samples[i*4 + 1] = g;
        samples[i*4 + 2] = b;
        samples[i*4 + 3] = a;
    }

    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_data(samples, GDK_COLORSPACE_RGB, TRUE, 8, width, height, width * 4, NULL, NULL);
    gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
    cairo_paint(cr);

    g_object_unref(pixbuf);

    return FALSE;
}


void load_page(int page_number) {
    if (ctx == NULL || doc == NULL) {
        printf("Context or document is not initialized\n");
        return;
    }

    if (page_number < 0 || page_number >= fz_count_pages(ctx, doc)) {
        printf("Invalid page number\n");
        return;
    }

    fz_matrix transform;
    transform = fz_scale(zoom_level, zoom_level);

    fz_page *page = fz_load_page(ctx, doc, page_number);
    if (page == NULL) {
        printf("Failed to load page\n");
        return;
    }

    // Aqui, removemos a definição local de pix e usamos a variável global
    if (pix != NULL) {
        fz_drop_pixmap(ctx, pix);
    }
    pix = fz_new_pixmap_from_page_number(ctx, doc, page_number, transform, fz_device_rgb(ctx), 0);
    if (pix == NULL) {
        printf("Failed to create pixmap\n");
        return;
    }

    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_data(pix->samples, GDK_COLORSPACE_RGB, pix->n == 4, 8, pix->w, pix->h, pix->stride, NULL, NULL);
    if (pixbuf == NULL) {
        printf("Failed to create pixbuf\n");
        return;
    }

    gtk_image_set_from_pixbuf(GTK_IMAGE(darea), pixbuf);

    g_object_unref(pixbuf);
}


void on_next_page(GtkWidget *widget, gpointer user_data) {
    int num_pages = fz_count_pages(ctx, doc);
    int last_page = load_last_page();
    printf("Current page before increment: %d\n", last_page);
    if (last_page < num_pages - 1) {
        last_page++;
        printf("Current page after increment: %d\n", last_page);
        save_last_page(last_page);
        load_page(last_page);
        gtk_widget_queue_draw(darea);
    }
}

void on_previous_page(GtkWidget *widget, gpointer user_data) {
    int last_page = load_last_page();
    printf("Current page before decrement: %d\n", last_page);
    if (last_page > 0) {
        last_page--;
        printf("Current page after decrement: %d\n", last_page);
        save_last_page(last_page);
        load_page(last_page);;
        gtk_widget_queue_draw(darea);
    }
}

void on_zoom_in(GtkWidget *widget, gpointer user_data) {
    zoom_level *= 1.1;
    if (zoom_level > 10) {
        zoom_level = 10;
    }
    int last_page = load_last_page();
    load_page(last_page);
    //load_page(current_page);
    if (GTK_IS_WIDGET(darea)) {
        gtk_widget_queue_draw(darea);
    }
}

void on_zoom_out(GtkWidget *widget, gpointer user_data) {
    if (zoom_level > 0.1) {
        zoom_level /= 1.1;
        int last_page = load_last_page();
        load_page(last_page);
        //load_page(current_page);
        if (GTK_IS_WIDGET(darea)) {
            gtk_widget_queue_draw(darea);
        }
    }
}



void on_fullscreen_button_clicked(GtkWidget *widget, gpointer data)
{
    GtkWidget *window = GTK_WIDGET(data);
    if (!is_fullscreen) {
        gtk_window_fullscreen(GTK_WINDOW(window));
        is_fullscreen = TRUE;
    } else {
        gtk_window_unfullscreen(GTK_WINDOW(window));
        is_fullscreen = FALSE;
    }
}

void init_scrolled_window(GtkScrolledWindow *scrolled_window) {
    vadjustment = gtk_scrolled_window_get_vadjustment(scrolled_window);
    hadjustment = gtk_scrolled_window_get_hadjustment(scrolled_window);
}

// Em seguida, defina as funções para rolar para cima, baixo, esquerda e direita
void scroll_up() {
    double value = gtk_adjustment_get_value(vadjustment) - gtk_adjustment_get_step_increment(vadjustment);
    gtk_adjustment_set_value(vadjustment, value);
}

void scroll_down() {
    double value = gtk_adjustment_get_value(vadjustment) + gtk_adjustment_get_step_increment(vadjustment);
    gtk_adjustment_set_value(vadjustment, value);
}

void scroll_left() {
    double value = gtk_adjustment_get_value(hadjustment) - gtk_adjustment_get_step_increment(hadjustment);
    gtk_adjustment_set_value(hadjustment, value);
}

void scroll_right() {
    double value = gtk_adjustment_get_value(hadjustment) + gtk_adjustment_get_step_increment(hadjustment);
    gtk_adjustment_set_value(hadjustment, value);
}