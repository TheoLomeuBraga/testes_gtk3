using namespace std;
#include <gtk/gtk.h>

#include "launcher.h"
#include "vector"
#include <memory>

vector<shared_ptr<component>> components = {
  make_shared<launcher>(launcher("/home/theo/testes_gtk3/built/icons/browser.png","firefox","firefox &")),
  make_shared<launcher>(launcher("","thunar","thunar &")),
  //make_shared<launcher>(launcher("","firefox","firefox &")),
};





int main (int argc,char **argv)
{
  gtk_init(&argc, &argv);
  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  

  
  //theme
  GtkSettings *default_settings = gtk_settings_get_default();
  g_object_set(default_settings, "gtk-button-images", TRUE, NULL);
    
  gtk_window_set_title (GTK_WINDOW (window), "hello world");
  //ocultar , posicionar e sobre posicionar
  gtk_window_set_decorated(GTK_WINDOW(window),false);
  gtk_window_set_skip_taskbar_hint(GTK_WINDOW(window),true);
  //gtk_window_set_keep_above(GTK_WINDOW(window),true);
  gtk_window_set_default_size (GTK_WINDOW (window), 100, 400);
  gtk_window_move(GTK_WINDOW (window),0,100);
  //gtk_window_set_position(GTK_WINDOW (window),GTK_WIN_POS_CENTER_ALWAYS);

  GtkWidget *vbox = gtk_vbox_new(TRUE, 1);
  gtk_container_add(GTK_CONTAINER(window), vbox);

  //render_things
  for(int i = 0; i < components.size();i++){
      components[i]->render(vbox);
  }


  //display
  gtk_widget_show_all(window);
  gtk_main();


  
}