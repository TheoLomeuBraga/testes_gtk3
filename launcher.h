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
    void render(GtkWidget *container){
        
        GtkImage *image;

                                                        
        

        GtkSettings *default_settings = gtk_settings_get_default();
        g_object_set(default_settings, "gtk-button-images", TRUE, NULL);

        button = gtk_button_new_with_label("");
        g_signal_connect (button, "clicked", G_CALLBACK (launcher::run_command), (gpointer)this->command);

        image = (GtkImage *)gtk_image_new_from_file(this->icon); 
        gtk_button_set_image (GTK_BUTTON(button),(GtkWidget *)image); 
        
        gtk_box_pack_start(GTK_BOX(container), button, TRUE, TRUE, 0);
        gtk_widget_set_tooltip_text(button, this->name);




        next_avaliable_slot_in_grid++;
    }
};