#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "widget.hpp"
#include "graphics.hpp"

#include <string>

class Button : public Widget
{
private:
    std::string title;
public:
    Button(int pos_x, int pos_y, int size_x, int size_y, int frame_size_, int r, int g, int b, Application* p, std::string t);
    void place() override;
    void event_handler(genv::event ev) override;
};

#endif // BUTTON_HPP
