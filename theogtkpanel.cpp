using namespace std;
#include <gtk/gtk.h>

#include "launcher.h"
#include "vector"
#include <memory>
#include <fstream>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

vector<shared_ptr<component>> components = {
  make_shared<launcher>(launcher("/home/theo/testes_gtk3/built/icons/browser.png","firefox","firefox &")),
  make_shared<launcher>(launcher("thunar","thunar","thunar &")),
  make_shared<launcher>(launcher("thunar","thunar","thunar &")),
  make_shared<launcher>(launcher("thunar","thunar","thunar &")),
  make_shared<launcher>(launcher("thunar","thunar","thunar &")),
  make_shared<launcher>(launcher("thunar","thunar","thunar &")),
  make_shared<launcher>(launcher("thunar","thunar","thunar &")),
};


void load_setings(string path){
  GdkRectangle workarea = {0};
  gdk_monitor_get_workarea(gdk_display_get_primary_monitor(gdk_display_get_default()),&workarea);
  res_x = workarea.width;
  res_y = workarea.height;

  //load json
  ifstream jfile(path);
  json j = json::parse(jfile);


  icon_res = j["icon_res"].get<int>();
  add_pos_y = j["add_pos_y"].get<int>();
  aways_active = j["aways_active"].get<int>();
  skip_taskbar_hint = j["skip_taskbar_hint"].get<int>();
  centralize = j["centralize"].get<int>();
  vertical = j["vertical"].get<int>();

  
  
}


int main (int argc,char **argv)
{
  gtk_init(&argc, &argv);
  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  
  load_setings("./config.json");
  
  //theme
  GtkSettings *default_settings = gtk_settings_get_default();
  g_object_set(default_settings, "gtk-button-images", TRUE, NULL);
    
  gtk_window_set_title (GTK_WINDOW (window), "hello world");
  //ocultar , posicionar e sobre posicionar
  gtk_window_set_decorated(GTK_WINDOW(window),false);
  gtk_window_set_skip_taskbar_hint(GTK_WINDOW(window),skip_taskbar_hint);
  gtk_window_set_keep_above(GTK_WINDOW(window),aways_active);
  gtk_window_set_default_size (GTK_WINDOW (window), icon_res, icon_res*components.size());
  gtk_window_move(GTK_WINDOW (window),0,((res_y/2 - icon_res/2)/1.5) + add_pos_y);
  if(centralize){gtk_window_set_position(GTK_WINDOW (window),GTK_WIN_POS_CENTER_ALWAYS);}

  GtkWidget *box;
  if(vertical){
    box = gtk_vbox_new(TRUE, 1);
  }else{
    box = gtk_hbox_new(TRUE, 1);
  }
  gtk_container_add(GTK_CONTAINER(window), box);

  

  //render_things
  for(int i = 0; i < components.size();i++){
      components[i]->render(box);
  }


  //display
  gtk_widget_show_all(window);
  gtk_main();


  
}