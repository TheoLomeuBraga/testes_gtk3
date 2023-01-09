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
#include "minimizer.h"
using json = nlohmann::json;

GtkWidget *window;
int win_pos_x = 0;

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

  
  if(!j["position"].get<string>().compare("right")){
    win_pos_x = res_x - icon_res;
  }

  icon_res = j["icon_res"].get<int>();
  add_pos_y = j["add_pos_y"].get<int>();
  aways_active = j["aways_active"].get<int>();
  skip_taskbar_hint = j["skip_taskbar_hint"].get<int>();
  centralize = j["centralize"].get<int>();
  vertical = j["vertical"].get<int>();
  seconds_to_update_applets = j["seconds_to_update_applets"].get<float>();

  components = {};
  json components_json = j["components"].get<vector<json>>();
  for(json comp : components_json){
    string type = comp["type"].get<string>();
    if(!type.compare("launcher")){

      string icon = get_home_directory_in_path(comp["icon"].get<string>());
      string name = comp["name"].get<string>();
      string command = comp["command"].get<string>();
      components.push_back(make_shared<launcher>(launcher(icon,name,command)));

    }else if (!type.compare("clock")){
      string icon = get_home_directory_in_path(comp["icon"].get<string>());
      string command = comp["command"].get<string>();
      components.push_back(make_shared<watch>(watch(icon,command)));
    }else if (!type.compare("minimizer")){
      string icon = get_home_directory_in_path(comp["icon"].get<string>());
      string name = comp["name"].get<string>();
      components.push_back(make_shared<minimizer>(minimizer(window,icon,name)));
    }
  }

  
}



//maximize window
void maximize_window(GtkWidgetClass* widget_class,const char* callback_name,GCallback callback_symbol) {
    gtk_window_present(GTK_WINDOW(window));
}

vector<string> args;
int main (int argc,char **argv)
{
  //init gtk
  //g_thread_init (NULL);
  gdk_threads_init();
  gdk_threads_enter();

  gtk_init(&argc, &argv);
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  //load config
  args = get_args(argc,argv);
  if(args.size() == 2 && file_exists(get_home_directory_in_path(args[1]))){
    load_setings(get_home_directory_in_path(args[1]));
    print("a");
  }else{
    if(file_exists("./config.json")){
      load_setings("./config.json");
      print("b");
    }
    else if (file_exists(get_home_directory_in_path("~/.config/theogtkpanel/config.json"))){
      load_setings(get_home_directory_in_path("~/.config/theogtkpanel/config.json"));
      print("c");
    }
  }
  
   
  
  

  
  
  

  
  //ocultar , posicionar e sobre posicionar
  gtk_window_set_title (GTK_WINDOW (window), "Théo gtk panel");
  gtk_window_set_decorated(GTK_WINDOW(window),false);
  gtk_window_set_skip_taskbar_hint(GTK_WINDOW(window),skip_taskbar_hint);
  gtk_window_set_keep_above(GTK_WINDOW(window),aways_active);
  gtk_window_set_default_size (GTK_WINDOW (window), icon_res, icon_res*components.size());
  //keep maximized
  //g_signal_connect(G_OBJECT(window), "window-state-event", G_CALLBACK(maximize_window), NULL);
  
  gtk_window_move(GTK_WINDOW (window),win_pos_x,((res_y/2 - icon_res/2)/1.25) + add_pos_y);
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