#include <gtk/gtk.h>

int avaliable_space_in_grid = 0;
GtkWidget *grid = NULL;

class component{
    public:
    virtual void render(GtkWidget *window){}
};