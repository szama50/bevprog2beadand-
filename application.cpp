#include "graphics.hpp"
#include "application.hpp"
#include "widget.hpp"

using namespace genv;

Application::Application(int window_w,int window_h): window_width(window_w), window_height(window_h)
{
    gout.open(window_w,window_h);
    gout.load_font("LiberationSans-Regular.ttf",19);
    ingame = false;
}

void Application::event_loop()
{
    for (size_t i = 0; i < menu.size(); i++)
        menu[i]->place();
    gout << refresh;
    event ev;

    while(gin >> ev)
    {
        clear_screen();
        if (!ingame)
        {
            gout.load_font("LiberationSans-Regular.ttf",19);
            for (size_t i = 0; i < menu.size(); i++)
            {
                menu[i]->setactivity(ev);
                menu[i]->place();
                menu[i]->event_handler(ev);
                menu[i]->position_correction();
                if (menu[i]->string_getter()=="Single player")
                {
                    single_player = true;
                }
                if (menu[i]->string_getter()=="Multiplayer")
                {
                    single_player = false;
                }
            }
        }
        else
        {
            if (single_player)
            {
                //for debug
                std::cout << "Single player" << std::endl;
                return;
            }
            else
            {
                //for debug
                std::cout << "Multiplayer" << std::endl;
                return;
            }
        }
        gout << refresh;
    }
}

void Application::clear_screen()
{
    gout << color(0,0,0);
    gout << move_to(0,0);
    gout << box(window_width,window_height);
}

void Application::register_game_widget(Widget* widget)
{
    game.push_back(widget);
}

void Application::register_menu_widget(Widget * widget)
{
    menu.push_back(widget);
}

void Application::change_ingame_status()
{
    ingame = !ingame;
}








