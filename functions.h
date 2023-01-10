#pragma once
using namespace std;
#include "vector"
#include "string"
#include <fstream>
#include <iostream>
#include <fstream>
#include "config.h"
#include <gtk/gtk.h>

vector<string> get_args(int argc,char **argv){
  vector<string> ret;
  ret.resize(argc);
  for(int i = 0; i < argc;i++){
    ret[i] = argv[i];
  }
  return ret;
}

bool file_exists(string file_path){
    ifstream file;
    file.open(file_path);
    return (bool)file;
}

string get_home_directory(){return getenv("HOME");}

string get_home_directory_in_path(string path){
  string ret("");
  if(path[0] == '~'){
    path.erase(0, 1);
    ret = getenv("HOME") + path;
  }else{
    ret = path;
  }
  return ret;
}

template <typename X>
void print(X s){
  cout << s << endl;
}

char* pass_string_to_array(string s){
  char chars[NUM_CHARS_STR];
  for(int i = 0;i < min(NUM_CHARS_STR,(int)s.size());i++){
    chars[i] = s[i];
  }
  return chars;
}

GtkIconTheme* get_icon_theme(){
  GtkIconTheme* ret;
  string main_icon_theme_path = string("/usr/share/icons/") + main_icon_theme;
  if(main_icon_theme.size() == 0){
    ret = gtk_icon_theme_get_default();
  }else{
    ret = gtk_icon_theme_get_default();
    

    const char *main_icon_path = main_icon_theme_path.c_str();
    const char **icon_path = &main_icon_path;
    print(main_icon_theme_path);
    printf(icon_path[0]);
    cout << endl;
    
    gtk_icon_theme_set_search_path(ret,icon_path,1);

    gchar** paths;
    gint n_elements;
    gtk_icon_theme_get_search_path(ret,&paths,&n_elements);
    print("icons paths");
    print(n_elements);
    for(int i = 0;i<n_elements;i++){
      printf(paths[i]);
      cout << endl;
    }
  }
  
  return ret;
}