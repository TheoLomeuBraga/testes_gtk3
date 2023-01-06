using namespace std;
#include <gtk/gtk.h>
#include <iostream>
#include "component.h"

class launcher : public component{
public:
    char* icon,*name,*command;
    GtkWidget *button,*button_box;
    launcher(){}

    launcher(char* icon,char* name,char* command){
        this->icon = icon;
        this->name = name;
        this->command = command;
    }

    
    static void run_command (GtkWidget *widget,gpointer data)
    {
        system((char*)data);
    }
    void render(GtkWidget *grid){


        

        

        
        
        

        button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
        button = gtk_button_new_with_label(this->name);
        g_signal_connect (button, "clicked", G_CALLBACK (launcher::run_command), (gpointer)this->command);
        gtk_container_add (GTK_CONTAINER (button_box), button);
        next_avaliable_slot_in_grid++;

        gtk_container_add (GTK_CONTAINER (grid), button_box);
        gtk_grid_attach(GTK_GRID (grid), button, 0, 0, 1, 1);
        next_avaliable_slot_in_grid++;
    }
};