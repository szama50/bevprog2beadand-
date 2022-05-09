#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <iostream>
#include <vector>

class Widget;

class Application
{
protected:
    int window_width_height;
    bool ingame;
    bool single_player;
    std::vector<Widget*> menu;
    std::vector<Widget*> game;
    int game_frame;
public:
    Application(int window_wh, int game_frame_);
    void register_game_widget(Widget*);
    void register_menu_widget(Widget*);
    void event_loop();
    void clear_screen();
    void change_ingame_status();
    void generate_table(int);
};

#endif // APPLICATION_HPP
