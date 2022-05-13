#include "checkbox.hpp"

#include <string>
#include <cmath>

using namespace genv;

Checkbox::Checkbox(int pos_x, int pos_y, int size_x, int size_y, int frame_size_, int r, int g, int b, Application* p)
    :Widget(pos_x,pos_y,size_x,size_y,frame_size_,r,g,b,p)
{
    state = " ";
}

canvas circle(int size, int r, int g, int b)
{
    canvas c;
    c.open(size,size);
    c.transparent(true);
    c << color(r,g,b);
    for (int i = -size/2; i < size/2; i++)
    {
        for (int j = -size/2; j < size/2; j++)
        {
            if (pow(i,2)+pow(j,2)<=pow(size/2,2) && pow(i,2)+pow(j,2)>=pow(size/2-2,2))
            {
                c << move_to(i+size/2,j+size/2);
                c << dot;
            }
        }
    }
    return c;
}

canvas xmark(int size, int r, int g, int b)
{
    canvas x;
    x.open(size,size);
    x.transparent(true);
    x << color(r,g,b);
    x << move_to(1,0) << line_to(size-1,size-1);
    x << move_to(1,size-1) << line_to(size-1,1);
    return x;
}

void Checkbox::place()
{
    gout << color(color_red,color_green,color_blue);
    gout << move_to(position_x,position_y);
    gout << box(size_x_px,size_y_px);
    gout << color(255,255,255);
    gout << move_to(position_x+frame_size,position_y+frame_size);
    gout << box(size_x_px-2*frame_size,size_y_px-2*frame_size);
    gout << stamp(c,position_x+2*frame_size,position_y+2*frame_size);
}

void Checkbox::event_handler(event ev)
{
    static long long int serial_number = 1;
    if (state == " " && active && ev.type==ev_mouse && ev.button==btn_left)
    {
        if (serial_number % 2 == 1)
        {
            c = xmark(size_x_px-4*frame_size,color_red,color_green,color_blue);
            state = 'X';
        }
        else
        {
            c = circle(size_x_px-4*frame_size,color_red,color_green,color_blue);
            state = 'O';
        }
        serial_number++;
    }
}

std::string Checkbox::string_getter()
{
    return state;
}




