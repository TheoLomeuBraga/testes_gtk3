using namespace std;
#include <gtk/gtk.h>
#include <iostream>
#include "component.h"
#include "../config.h"

class minimizer : public component{
public:
    GtkWidget *window;
    string icon,name;
    GtkWidget *button,*button_box;

    static void minimize(GtkWidget *widget,gpointer data){
        system("xdotool key super+d");
        gtk_window_present(GTK_WINDOW(data));
    }

    minimizer(GtkWidget *window,string icon,string name){
        this->window = window;
        this->icon = icon;
        this->name = name;
    }

    

    void render(GtkWidget *container){
        
        GtkImage *image;

                                                        
        

        GtkSettings *default_settings = gtk_settings_get_default();
        g_object_set(default_settings, "gtk-button-images", TRUE, NULL);
        

        //create button
        button = gtk_button_new_with_label("");
        g_signal_connect(button, "clicked", G_CALLBACK (minimizer::minimize), (gpointer)window);

        //set image
        GdkPixbuf *pb = gdk_pixbuf_new_from_file(this->icon.c_str(),NULL);
        GdkPixbuf *pxbscaled = gdk_pixbuf_scale_simple(pb,icon_res,icon_res,GDK_INTERP_BILINEAR);
        image = (GtkImage*)gtk_image_new_from_pixbuf(pxbscaled);
        gtk_image_set_from_pixbuf(GTK_IMAGE(image), pxbscaled);
        gtk_button_set_image (GTK_BUTTON(button),(GtkWidget *)image); 





 
        //add text
        gtk_widget_set_tooltip_text(button, (const char*)this->name.c_str());
        
        //put on the list
        gtk_box_pack_start(GTK_BOX(container), button, TRUE, TRUE, 0);
        
    }
};