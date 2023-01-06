using namespace std;
#include <gtk/gtk.h>
#include <iostream>
#include <string>

class launcher{
public:
    string icon,name,command;
    launcher(){}

    launcher(string icon,string name,string command){
        this->icon = icon;
        this->name = name;
        this->command = command;
    }

    
    static void run (GtkWidget *widget,gpointer data)
    {
        launcher* This = ((launcher*)data);
        system((This->command + " &").c_str());
    }
    void render(GtkWidget *window){


        GtkWidget *button,*button_box;

        button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
        gtk_container_add (GTK_CONTAINER (window), button_box);

        button = gtk_button_new_with_label("Hello World");
        g_signal_connect (button, "clicked", G_CALLBACK (this->run), NULL);
        g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
        gtk_container_add (GTK_CONTAINER (button_box), button);
    }
};