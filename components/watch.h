using namespace std;
#include <gtk/gtk.h>
#include <pthread.h>
#include <chrono>
#include <thread>

#include <iostream>
#include "component.h"


#include <iomanip>
#include <ctime>
#include "../config.h"


string oclock;
pthread_t pt;
class watch : public component{
public:
    string icon,command;
    
    GtkWidget *button,*button_box;
    

    //watch(char icon[NUM_CHARS_STR],char command[NUM_CHARS_STR]){
    //    this->icon = icon;
    //    this->command = command;
    //}

    watch(string icon,string command){
        this->icon = icon;
        this->command = command;
    }
    
    static void run_command (GtkWidget *widget,gpointer data)
    {
        system((char*)data);
    }

    static string get_time(){

            auto t = std::time(nullptr);
            auto tm = *std::localtime(&t);
            stringstream ss("");

            ss << put_time(&tm, "%H : %M") ;
            oclock = ss.str();
            

            
        return oclock;
    }

    static void* get_time_threat(void *args){
        while(true){
            this_thread::sleep_for(std::chrono::milliseconds((int)(seconds_to_update_applets * 1000)));
            gtk_widget_set_tooltip_text((GtkWidget*)args, watch::get_time().c_str());
        }
        return NULL;
    }

    

    void render(GtkWidget *container){
        GtkImage *image;

                                                        
        

        GtkSettings *default_settings = gtk_settings_get_default();
        g_object_set(default_settings, "gtk-button-images", TRUE, NULL);

        //create button
        button = gtk_button_new_with_label("");
        g_signal_connect (button, "clicked", G_CALLBACK (launcher::run_command), (gpointer)command.c_str());

        //set image
        GdkPixbuf *pb = gdk_pixbuf_new_from_file(icon.c_str(),NULL);
        GdkPixbuf *pxbscaled = gdk_pixbuf_scale_simple(pb,icon_res,icon_res,GDK_INTERP_BILINEAR);
        image = (GtkImage*)gtk_image_new_from_pixbuf(pxbscaled);
        gtk_image_set_from_pixbuf(GTK_IMAGE(image), pxbscaled);
        gtk_button_set_image (GTK_BUTTON(button),(GtkWidget *)image); 
 
        //add text
        watch::get_time();
        gtk_widget_set_tooltip_text(button, oclock.c_str());

        //thread
        /* create the threads */

        
        pthread_create (&pt, NULL, watch::get_time_threat, button);
        
        //put on the list
        gtk_box_pack_start(GTK_BOX(container), button, TRUE, TRUE, 0);
    }
};