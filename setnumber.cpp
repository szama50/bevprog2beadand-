#include "setnumber.hpp"
#include "graphics.hpp"

#include <iostream>
#include <string>
#include <cmath>

using namespace genv;

Setnumber::Setnumber(int pos_x, int pos_y, int size_x, int size_y, int frame_size_, int r, int g, int b,int interval_a,int interval_b,int s_slider
                     ,Application* p)
    :Widget(pos_x, pos_y, size_x, size_y, frame_size_, r, g, b,p),size_of_slider(s_slider),interval_start(interval_a),interval_end(interval_b)
{
    number = 0.5*(interval_a+interval_b);
    size_of_marker = s_slider - 2*frame_size_;
    position_marker = pos_x+0.5*(size_x-size_of_slider);
    parent->register_menu_widget(this);
}

canvas triangle(int c_size_y,int r, int g, int b, bool to_left)
{
    canvas t;
    t.open(c_size_y,c_size_y);
    t.transparent(true);
    t << color(r,g,b);
    if (to_left)
        for (int i = 0; i < c_size_y; i++)
        {
            t << move_to(c_size_y-1,i);
            t << line_to(0,0.5*c_size_y);
        }
    else
        for (int i = 0; i < c_size_y; i++)
        {
            t << move_to(0,i);
            t << line_to(c_size_y-1,0.5*c_size_y);
        }
    return t;
}

//size_of_slider = height of "slider bar" = height of triangle = base of triangle

void Setnumber::place()
{
    //Box for number
    gout << color(color_red,color_green,color_blue);
    gout << move_to(position_x,position_y);
    gout << box(size_x_px,size_y_px-size_of_slider);
    gout << color(0,0,0);
    gout << move_to(position_x+frame_size,position_y+frame_size);
    gout << box(size_x_px-2*frame_size,size_y_px-2*frame_size-size_of_slider);
    gout << color(color_red,color_green,color_blue);
    gout << move_to(position_x+0.5*(size_x_px-gout.twidth(std::to_string(number))),
                    position_y+0.5*(size_y_px-size_of_slider-gout.cascent()-gout.cdescent()));
    gout << text(std::to_string(number));
    //Box for number

    //Increase & Decrease button
    canvas decrease_button = triangle(size_of_slider,color_red,color_green,color_blue,true);
    gout << stamp(decrease_button,position_x,position_y+size_y_px-size_of_slider);
    canvas increase_button = triangle(size_of_slider,color_red,color_green,color_blue,false);
    gout << stamp(increase_button,position_x+size_x_px-size_of_slider,position_y+size_y_px-size_of_slider);
    //Increase & Decrease button

    //Marker_background
    gout << color(color_red*0.3,color_green*0.3,color_blue*0.3);
    gout << move_to(position_x+size_of_slider,position_y+size_y_px-size_of_slider);
    gout << box(size_x_px-2*size_of_slider,size_of_slider);
    //Marker_background

    //Marker
    //gout << color(color_red,color_green,color_blue);
    gout << color(color_red,color_green,color_blue);
    gout << move_to(position_marker,position_y+size_y_px-size_of_slider+frame_size);
    gout << box(2*size_of_marker,size_of_marker); //size_of_marker = y size of marker, 2* size_of_marker = x size of marker
    //Marker
}

void Setnumber::event_handler(event ev)
{
    static bool leftactive = false;
    static int distance_mouse_marker = 0;
    if (active)
    {
    //Marker
    if (ev.type == ev_mouse)
    {
        if (ev.button == btn_left && ev.pos_x>=position_marker && ev.pos_x<=position_marker+2*size_of_marker
                && ev.pos_y>=position_y+size_y_px-size_of_slider && ev.pos_y<=position_y+size_y_px)
        {
            leftactive = true;
            distance_mouse_marker = ev.pos_x-position_marker;
        }
        if (ev.button == -btn_left)
        {
            leftactive = false;
        }
        if (leftactive)
            //size_of_marker = y size of marker, 2* size_of_marker = x size of marker
        {
            position_marker = ev.pos_x-distance_mouse_marker;
        }
    }

    if (leftactive)
    {
        double scale = double(interval_end-interval_start+1)/double(size_x_px-2*size_of_slider-2*size_of_marker);
        int numbertmp = std::floor(double(interval_start)+double(position_marker-position_x-size_of_slider)*scale);
        if (numbertmp < interval_start)
            number = interval_start;
        else if (numbertmp > interval_end)
            number = interval_end;
        else
            number = numbertmp;
    }
    //Marker

    //Increase & decrease button
    else if (ev.type == ev_mouse && ev.button == btn_left &&
            ev.pos_y>=position_y+size_y_px-size_of_slider && ev.pos_y<=position_y+size_y_px)
    {
        if (ev.pos_x>=position_x+size_x_px-size_of_slider && ev.pos_x<=position_x+size_x_px && number<interval_end)
        {
            number++;
        }
        if (ev.pos_x>=position_x && ev.pos_x<=position_x+size_of_slider && number>interval_start)
        {
            number--;
        }
    }
    if (ev.type == ev_key)
    {
        if (ev.keycode == 97 && number<=interval_end-10) //pg up
            number+=10;
        if (ev.keycode == 91 && number>=interval_start+10) //pg dn
            number-=10;
        if (ev.keycode == 82 && number<interval_end) //up
            number++;
        if (ev.keycode == 81 && number>interval_start) //down
            number--;
    }
    if (!leftactive)
    {
        position_marker=position_x+(size_x_px-2*size_of_marker)/2
                +(number-0.5*(interval_start+interval_end))*(size_x_px-2*size_of_slider-2*size_of_marker)/(interval_end-interval_start);
    }
    //Increase & decrease button
    }
}

void Setnumber::position_correction()
{
    if (position_marker<position_x+size_of_slider) //size_of_slider = height of triangle
    {
        position_marker = position_x+size_of_slider;
    }
    if (position_marker>position_x+size_x_px-size_of_slider-2*size_of_marker)
    {
        position_marker = position_x+size_x_px-size_of_slider-2*size_of_marker;
    }
}

void Setnumber::setactivity(event ev)
{
    if (ev.type == ev_mouse && ev.button == btn_left)
        active = (ev.pos_x>=position_x && ev.pos_x<=position_x+size_x_px && ev.pos_x>=position_y && ev.pos_y<=position_y+size_y_px);
}

double Setnumber::int_getter()
{
    return number;
}








