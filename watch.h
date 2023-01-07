using namespace std;
#include <gtk/gtk.h>
#include <iostream>
#include "component.h"




class watch : public component{
public:
    char *icon,*command;
    watch(){}

    watch(char icon[NUM_CHARS_str],char command[NUM_CHARS_str]){
        this->icon = icon;
        this->command = command;
    }

    
    static void run_command (GtkWidget *widget,gpointer data)
    {
    }

    static char* get_time(){
        //https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
        return "";
    }

    void render(GtkWidget *container){
    }
};