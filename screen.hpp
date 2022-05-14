#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "widget.hpp"

#include <string>

class Screen : public Widget
{
private:
    std::string text_;
public:
    Screen(int pos_x, int pos_y, int size_x, int size_y, int frame_size_, int r, int g, int b, Application* p);
    void event_handler(genv::event ev) override;
    virtual void place() override;
};

#endif // SCREEN_HPP
