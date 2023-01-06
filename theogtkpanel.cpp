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
    

    //ocultar , posicionar e sobre posicionar
    gtk_window_set_decorated(GTK_WINDOW(window),false);
    gtk_window_set_skip_taskbar_hint(GTK_WINDOW(window),true);
    //gtk_window_set_keep_above(GTK_WINDOW(window),true);
    gtk_window_set_default_size (GTK_WINDOW (window), 100, 400);
    gtk_window_move(GTK_WINDOW (window),0,100);
    //gtk_window_set_position(GTK_WINDOW (window),GTK_WIN_POS_CENTER_ALWAYS);

    //create grid
    grid = gtk_grid_new();
    gtk_widget_set_margin_left(grid, 6);
    gtk_widget_set_margin_top(grid, 6);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 6);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 6);


    for(int i = 0; i < components.size();i++){
      components[i]->render(grid);
    }
    gtk_container_add (GTK_CONTAINER(window), grid);

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