#include <gtk/gtk.h>

typedef struct {
  GtkWidget *entry; // pointer to input field (gtkentry)
  GtkWidget *label; // pointer to textlabel (gtklabel)
} Widgets;

static void on_button_clicked(GtkButton *button, gpointer user_data) {
  Widgets *widgets = (Widgets *)user_data;

  const gchar *text = gtk_entry_get_text(GTK_ENTRY(widgets->entry));
  gtk_label_set_text(GTK_LABEL(widgets->label), text);
}
int main(int argc, char **argv) {

  gtk_init(&argc, &argv);

  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "GTK+ Erweiterung");
  gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_container_add(GTK_CONTAINER(window), vbox);

  // using malloc for memory reservation
  Widgets *widgets = g_malloc(sizeof(Widgets));

  // generate input fiel (gtkentry)
  widgets->entry = gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(vbox), widgets->entry, TRUE, TRUE, 0);

  widgets->label = gtk_label_new("The text will appear here!");
  gtk_box_pack_start(GTK_BOX(vbox), widgets->label, TRUE, TRUE, 0);

  // make button
  GtkWidget *button = gtk_button_new_with_label("Show the written text");
  g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), widgets);
  gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);

  gtk_widget_show_all(window);
  gtk_main();

  // reset memory when gtk_main ends
  g_free(widgets);

  return 0;
}
