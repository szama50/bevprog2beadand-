#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <iostream>
#include <vector>

class Widget;

class Application
{
protected:
    int window_width;
    int window_height;
    bool ingame;
    bool single_player;
    std::vector<Widget*> menu;
    std::vector<Widget*> game;
public:
    Application(int window_w,int window_h);
    void register_game_widget(Widget*);
    void register_menu_widget(Widget*);
    void event_loop();
    void clear_screen();
    void change_ingame_status();
};

#endif // APPLICATION_HPP
