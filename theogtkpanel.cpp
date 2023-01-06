using namespace std;
#include <gtk/gtk.h>

#include "launcher.h"
#include "vector"
#include <memory>

vector<shared_ptr<component>> components = {
      make_shared<launcher>(launcher("","firefox","firefox &")),
    };

static void activate (GtkApplication* app,gpointer user_data)
{
    GtkWidget *window;
    
    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "hello world");

    //ocultar e sobre posicionar
    gtk_window_set_decorated(GTK_WINDOW(window),false);
    gtk_window_set_skip_taskbar_hint(GTK_WINDOW(window),true);
    gtk_window_set_keep_above(GTK_WINDOW(window),true);
    gtk_window_set_default_size (GTK_WINDOW (window), 100, 300);

    //create grid
    grid = gtk_grid_new();

    for(int i = 0; i < components.size();i++){
      components[i]->render(window);
    }
    gtk_widget_show_all(window);
}

int main (int argc,char **argv)
{

  GtkApplication *app;
  int status;
  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}