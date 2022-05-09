#include "choosetext.hpp"
#include "graphics.hpp"

#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace genv;

Choosetext::Choosetext(int pos_x, int pos_y, int size_x, int size_y, int frame_size_, int r, int g, int b, vector<string>_text,int novi,
                       Application* p)
    : Widget(pos_x,pos_y,size_x,size_y,frame_size_,r,g,b,p),highlighted(-1),number_of_visible_items(novi)
{
    for (size_t i = 0; i < _text.size(); i++)
    {
        if (i==1)
        {
            text_.push_back(_text[0]);
        }
        text_.push_back(_text[i]);
    }
    from = 1;
    parent->register_menu_widget(this);
}

canvas triangle(int size_x,int size_y,int r,int g, int b, bool up)
{
    canvas t;
    t.open(size_x,size_y);
    t.transparent(true);
    t << color(r,g,b);
    int y = 1;
    int to = size_y-1;
    if (up)
    {
        y = size_y-1;
        to = 1;
    }
    for (int i = 0; i < size_x; i++)
        t << move_to(i,y) << line_to(0.5*size_x,to);
    return t;
}

void Choosetext::place()
{
    if (!active)
    {
        highlighted = -1;
    }

    //Chosen item
    int size_of_triangle = 0.5*(gout.cascent()+gout.cdescent()); //y size of text
    canvas triangle_ = triangle(size_of_triangle,size_of_triangle,color_red,color_green,color_blue,active);

    gout << color(color_red,color_green,color_blue);
    gout << move_to(position_x,position_y);
    gout << box(size_x_px,size_y_px/number_of_visible_items);
    gout << color(0,0,0);
    gout << move_to(position_x+frame_size,position_y+frame_size);
    gout << box(size_x_px-2*frame_size,(size_y_px/number_of_visible_items)-2*frame_size);
    gout << color(color_red,color_green,color_blue);

    gout << move_to(position_x+0.5*(size_x_px-gout.twidth(text_[0])),position_y+((size_y_px/number_of_visible_items-gout.cascent()-gout.cdescent())/2));
    gout << text(text_[0]);
    gout << stamp(triangle_,position_x+size_x_px-2*frame_size-size_of_triangle, position_y+0.5*(size_y_px/number_of_visible_items-size_of_triangle));
    //Chosen item

    int until = from;
    if (active)
    {
        until = from+number_of_visible_items-1;
    }
    int i = 1;
        for (int j = from; j < until; j++)
        {
            gout << color(color_red,color_green,color_blue);
            gout << move_to(position_x,position_y+i*size_y_px/number_of_visible_items);
            gout << box(size_x_px,size_y_px/number_of_visible_items);
            if (highlighted == int(i))
                gout << color(0.3*color_red,0.3*color_green,0.3*color_blue);
            else
                gout << color(0,0,0);
            gout << move_to(position_x+frame_size,position_y+frame_size+i*size_y_px/number_of_visible_items);
            gout << box(size_x_px-2*frame_size,(size_y_px/number_of_visible_items)-2*frame_size);
            gout << color(color_red,color_green,color_blue);
            gout << move_to(position_x+(size_x_px-gout.twidth(text_[j]))/2,position_y+
                            ((size_y_px/number_of_visible_items-gout.cascent()-gout.cdescent())/2)+i*(size_y_px/number_of_visible_items));
            gout << text(text_[j]);
            i++;
        }
}

void Choosetext::event_handler(event ev)
{
    if (active && ev.type == ev_mouse && ev.pos_x>=position_x && ev.pos_x<=position_x+size_x_px)
    {
        int i = 1;
        for (int j = from; j < from+number_of_visible_items-1; j++)
        {
            if (ev.pos_y>=int(position_y+i*(size_y_px/number_of_visible_items)) && ev.pos_y<=int(position_y+(i+1)*(size_y_px/number_of_visible_items)))
            {
                if (ev.button == btn_left)
                {
                    text_[0]=text_[j];
                    if (i!=0)
                        active = false;
                }
                else
                {
                    highlighted = i;
                    break;
                }
            }
            i++;
        }
    }
    else if (active && ev.type == ev_mouse)
    {
        if (ev.button == btn_wheeldown && from!=int(text_.size()-number_of_visible_items)+1)
        {
            from++;
        }
        if (ev.button == btn_wheelup && from!=1)
        {
            from--;
        }
    }
}

void Choosetext::setactivity(event ev)
{
    if (ev.type == ev_mouse && ev.button ==btn_left)
    {
        if (!active)
            active = (ev.pos_x>=position_x && ev.pos_x<=position_x+size_x_px && ev.pos_y>=position_y &&
                    ev.pos_y<=position_y+size_y_px/number_of_visible_items);
        else
            active = (ev.pos_x>=position_x && ev.pos_x<=position_x+size_x_px && ev.pos_y>=position_y &&
                    ev.pos_y<=position_y+size_y_px);
    }
}

string Choosetext::string_getter()
{
    return text_[0];
}












