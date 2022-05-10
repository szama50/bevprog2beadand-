#ifndef CHECKBOX_HPP
#define CHECKBOX_HPP

#include "widget.hpp"

class Checkbox : public Widget
{
private:
    std::string state;
    genv::canvas c;
public:
    Checkbox(int pos_x, int pos_y, int size_x, int size_y, int frame_size_, int r, int g, int b, Application* p);
    void place() override;
    void event_handler(genv::event ev) override;
    std::string string_getter() override;
};

#endif // CHECKBOX_HPP
