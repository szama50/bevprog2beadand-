#ifndef SETNUMBER_HPP
#define SETNUMBER_HPP

#include "widget.hpp"

class Setnumber : public Widget
{
private:
    int number;
    int size_of_slider;
    int position_marker;
    int size_of_marker;
    int interval_start;
    int interval_end;
public:
    Setnumber(int pos_x, int pos_y, int size_x, int size_y, int frame_size_, int r, int g, int b,int interval_a,int interval_b,int s_slider,
              Application* p);
    void place() override;
    void event_handler(genv::event ev) override;
    void position_correction() override;
    void setactivity(genv::event ev) override;
    double int_getter() override;
};

#endif // SETNUMBER_HPP
