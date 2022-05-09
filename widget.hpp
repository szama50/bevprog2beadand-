#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "graphics.hpp"
#include "application.hpp"

#include <string>

class Widget
{
protected:
//position
    int position_x;
    int position_y;
//position
//Size
    int size_x_px;
    int size_y_px;
//Size
//Frame
    int frame_size;
//Frame
//Color
    int color_red;
    int color_green;  //RGB
    int color_blue;
//Color
//Activity
    bool active;
//Activity
//Parent
    Application* parent;
//Parent
public:
    Widget(int pos_x, int pos_y, int size_x, int size_y, int frame_size_, int r, int g, int b, Application* p);
    virtual void place() = 0;
    virtual void setactivity(genv::event ev);
    virtual void event_handler(genv::event ev) = 0;
    virtual void position_correction();
    virtual std::string string_getter();
    virtual double int_getter();
};

#endif // WIDGET_HPP
