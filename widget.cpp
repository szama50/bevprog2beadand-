#include "widget.hpp"

Widget::Widget(int pos_x, int pos_y, int size_x, int size_y,int frame_size_, int r, int g, int b, Application* p)
    :position_x(pos_x), position_y(pos_y),size_x_px(size_x),size_y_px(size_y),frame_size(frame_size_),color_red(r),color_green(g),color_blue(b),
    parent(p)
{active = false;}

void Widget::setactivity(genv::event ev)
{
    active = ((ev.pos_x>=position_x) && (ev.pos_x<=position_x+size_x_px) && (ev.pos_y>=position_y) && (ev.pos_y<=position_y+size_y_px));
}

bool Widget::bool_getter()
{
    return active;
}

void Widget::position_correction()
{
    return;
}

std::string Widget::string_getter()
{
    return "";
}

double Widget::int_getter()
{
    return 0.1;
}

void Widget::modify_state(std::string)
{
    return;
}
