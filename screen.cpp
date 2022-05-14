#include "screen.hpp"

using namespace genv;

Screen::Screen(int pos_x, int pos_y, int size_x, int size_y, int frame_size_, int r, int g, int b, Application* p) :
    Widget(pos_x,pos_y,size_x,size_y,frame_size_,r,g,b,p)
{
    parent->register_over_widget(this);
}

void Screen::place()
{
    gout << move_to(position_x,position_y);
    gout << color(color_red,color_green,color_blue);
    gout << box(size_x_px,size_y_px);
    gout << move_to(position_x+frame_size,position_y+frame_size);
    gout << color(0,0,0);
    gout << box(size_x_px-2*frame_size,size_y_px-2*frame_size);
    gout << color(color_red,color_green,color_blue);
    std::string text_ = "WINNER: " + parent->game_over_getter();
    gout << move_to(position_x+0.5*(size_x_px-gout.twidth(text_))+5,position_y+0.5*(size_y_px-gout.cascent()-gout.cdescent()));
    gout << text(text_);
}

void Screen::event_handler(event)
{
    return;
}
