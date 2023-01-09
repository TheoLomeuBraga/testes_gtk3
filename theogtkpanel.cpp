using namespace std;
#include <gtk/gtk.h>
#include <pthread.h>


#include "functions.h"
#include "launcher.h"
#include "watch.h"
#include "component.h"

#include "vector"
#include <memory>
#include <fstream>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

vector<shared_ptr<component>> components = {
  make_shared<launcher>(launcher("/home/theo/testes_gtk3/built/icons/start.png","start","rofi -show drun -show-icons &")),
  make_shared<launcher>(launcher("/home/theo/testes_gtk3/built/icons/browser.png","firefox","firefox &")),
  make_shared<launcher>(launcher("/home/theo/testes_gtk3/built/icons/file.png","pcmanfm","pcmanfm &")),
  make_shared<launcher>(launcher("/home/theo/testes_gtk3/built/icons/cmd.png","GNOME Terminal","gnome-terminal &")),
  make_shared<watch>(watch("/home/theo/testes_gtk3/built/icons/clock.png","")),
  
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



vector<string> args;
int main (int argc,char **argv)
{
  //init gtk
  //g_thread_init (NULL);
  gdk_threads_init ();
  gdk_threads_enter ();

  gtk_init(&argc, &argv);
  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  //load config
  args = get_args(argc,argv);
  if(args.size() > 1){
    load_setings(args[1]);
  }else{
    load_setings("./config.json");
  }

  
  
  
  

  //GtkSettings *default_settings = gtk_settings_get_default();
  //g_object_set(default_settings, "gtk-button-images", TRUE, NULL);
    
  

  
  //ocultar , posicionar e sobre posicionar
  gtk_window_set_title (GTK_WINDOW (window), "Théo gtk panel");
  gtk_window_set_decorated(GTK_WINDOW(window),false);
  gtk_window_set_skip_taskbar_hint(GTK_WINDOW(window),skip_taskbar_hint);
  gtk_window_set_keep_above(GTK_WINDOW(window),aways_active);
  gtk_window_set_default_size (GTK_WINDOW (window), icon_res, icon_res*components.size());
  gtk_window_move(GTK_WINDOW (window),0,((res_y/2 - icon_res/2)/1.25) + add_pos_y);
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
  gdk_threads_leave();

  
}