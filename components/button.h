using namespace std;
#include <gtk/gtk.h>
#include <iostream>
#include "component.h"
#include "../config.h"



class button : public component{
public:
    string icon,name,command;
    GtkWidget *gtk_button,*button_box;
    

    //button(char icon[NUM_CHARS_STR],char name[NUM_CHARS_STR],char command[NUM_CHARS_STR]){
    //    this->icon = icon;
    //    this->name = name;
    //    this->command = command;
    //}
    button(string icon,string name,string command){
        
        this->icon = icon;
        this->name = name;
        this->command = command + " &";
    }

    
    static void run_command (GtkWidget *widget,gpointer data)
    {
        system((char*)data);
    }
    void render(GtkWidget *container){
        
        GtkImage *image;

                                                        
        

        GtkSettings *default_settings = gtk_settings_get_default();
        g_object_set(default_settings, "gtk-button-images", TRUE, NULL);
        

        //create button
        gtk_button = gtk_button_new_with_label("");
        g_signal_connect (gtk_button, "clicked", G_CALLBACK (button::run_command), (gpointer)(char*)this->command.c_str());

        //set image
        GdkPixbuf *pb = gdk_pixbuf_new_from_file(this->icon.c_str(),NULL);
        GdkPixbuf *pxbscaled = gdk_pixbuf_scale_simple(pb,icon_res,icon_res,GDK_INTERP_BILINEAR);
        image = (GtkImage*)gtk_image_new_from_pixbuf(pxbscaled);
        gtk_image_set_from_pixbuf(GTK_IMAGE(image), pxbscaled);
        gtk_button_set_image (GTK_BUTTON(gtk_button),(GtkWidget *)image); 





 
        //add text
        gtk_widget_set_tooltip_text(gtk_button, (const char*)this->name.c_str());
        
        //put on the list
        gtk_box_pack_start(GTK_BOX(container), gtk_button, TRUE, TRUE, 0);
        
    }
};