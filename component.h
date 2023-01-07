#pragma once

#include <gtk/gtk.h>
#define NUM_CHARS_str 200

class component{
    public:
    virtual void render(GtkWidget *window){}
};