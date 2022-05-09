#ifndef CHOOSETEXT_HPP
#define CHOOSETEXT_HPP

#include "widget.hpp"
#include "graphics.hpp"

#include <iostream>
#include <string>
#include <vector>

class Choosetext : public Widget
{
private:
    std::vector<std::string> text_;
    int highlighted;
    int number_of_visible_items; //the amount of string items that appear on screen when 'active'=true
    int from;
public:
    Choosetext(int pos_x, int pos_y, int size_x, int size_y, int frame_size_, int r, int g, int b, std::vector<std::string> _text,int novi,
               Application* p);
    void place() override;
    void event_handler(genv::event ev) override;
    void setactivity(genv::event ev) override;
    std::string string_getter() override;
};

#endif // CHOOSETEXT_HPP
