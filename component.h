#include <gtk/gtk.h>

int next_avaliable_slot_in_grid = 0;
GtkWidget *grid = NULL;

class component{
    public:
    virtual void render(GtkWidget *window){}
};