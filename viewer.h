#ifndef VIEWER_H
#define VIEWER_H

#include <gtk/gtk.h>
#include <mupdf/fitz.h>

extern fz_context *ctx;
extern fz_document *doc;
extern fz_pixmap *pix;
extern GtkWidget *darea;
extern double zoom_level;
extern GtkAdjustment *vadjustment;
extern GtkAdjustment *hadjustment;

gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data);
void load_page(int page_number);
void on_next_page(GtkWidget *widget, gpointer user_data);
void on_previous_page(GtkWidget *widget, gpointer user_data);
void on_zoom_in(GtkWidget *widget, gpointer user_data);
void on_zoom_out(GtkWidget *widget, gpointer user_data);
void on_fullscreen_button_clicked(GtkWidget *widget, gpointer user_data);
void init_scrolled_window(GtkScrolledWindow *scrolled_window);
void scroll_up();
void scroll_down();
void scroll_left();
void scroll_right();

#endif