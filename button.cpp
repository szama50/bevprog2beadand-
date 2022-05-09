#include "button.hpp"

using namespace genv;

Button::Button(int pos_x, int pos_y, int size_x, int size_y, int frame_size_, int r, int g, int b, Application* p, std::string t)
    :Widget(pos_x,pos_y,size_x,size_y,frame_size_,r,g,b,p), title(t)
{
    parent->register_menu_widget(this);
}

void Button::place()
{
    gout << move_to(position_x,position_y);
    gout << color(color_red,color_green,color_blue);
    gout << box(size_x_px,size_y_px);
    gout << move_to(position_x+frame_size,position_y+frame_size);
    if (active)
        gout << color(0.3*color_red,0.3*color_green,0.3*color_blue);
    else
        gout << color(0,0,0);
    gout << box(size_x_px-2*frame_size,size_y_px-2*frame_size);
    gout << color(color_red,color_green,color_blue);
    gout << move_to(position_x+0.5*(size_x_px-gout.twidth(title)),position_y+0.5*(size_y_px-gout.cascent()-gout.cdescent()));
    gout << text(title);
}

void Button::event_handler(genv::event ev)
{
    if (ev.type == ev_mouse && ev.button == btn_left && active)
    {
        parent->change_ingame_status();
    }
}
