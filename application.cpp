#include "graphics.hpp"
#include "application.hpp"
#include "widget.hpp"
#include "checkbox.hpp"

#include <cmath>

using namespace genv;
using namespace std;

Application::Application(int window_wh, int game_frame_): window_width_height(window_wh), game_frame(game_frame_)
{
    gout.open(window_wh,window_wh);
    gout.load_font("LiberationSans-Regular.ttf",19);
    ingame = false;
}

int search_correct_value(vector<Widget*> menu)
{
    for (size_t i = 0; i < menu.size(); i++)
    {
        if (menu[i]->int_getter() == int(menu[i]->int_getter()))
        {
            return menu[i]->int_getter();
        }
    }
    return 15;
}

void Application::generate_table(int size_of_table)
{
    int j = 0;
    int k = 0;
    for (int i = 0; i < pow(size_of_table,2); i++)
    {
        game.push_back(new Checkbox(j*(window_width_height-2*game_frame)/size_of_table+game_frame,
                                    k*(window_width_height-2*game_frame)/size_of_table+game_frame,
                                    (window_width_height-2*game_frame)/size_of_table+1,
                                    (window_width_height-2*game_frame)/size_of_table+1,2,0,0,255,this));
        j++;
        if (j==size_of_table)
        {
            k++;
            j = 0;
        }
    }
}

void in_menu(vector<Widget*> menu, event ev, bool& single_player)
{
    for (size_t i = 0; i < menu.size(); i++)
    {
        menu[i]->setactivity(ev);
        menu[i]->place();
        menu[i]->event_handler(ev);
        menu[i]->position_correction();
        if (menu[i]->string_getter()=="Single player")
            single_player = true;
        if (menu[i]->string_getter()=="Multiplayer")
            single_player = false;
    }
}

void single_player_game(vector<Widget*> game,event ev)
{
    for (size_t i = 0; i < game.size(); i++)
    {
        game[i]->place();
        game[i]->setactivity(ev);
        game[i]->event_handler(ev);
    }
}

void multi_player_game(vector<Widget*> game,event ev)
{
    for (size_t i = 0; i < game.size(); i++)
    {
        game[i]->place();
        game[i]->setactivity(ev);
        game[i]->event_handler(ev);
    }
}

void Application::event_loop()
{
    for (size_t i = 0; i < menu.size(); i++)
        menu[i]->place();
    gout << refresh;
    event ev;

    while(gin >> ev && ev.button != key_escape)
    {
        if (!ingame)
        {
            this->clear_screen();
            gout.load_font("LiberationSans-Regular.ttf",19);
            in_menu(menu,ev,single_player);
            if (ingame)
            {
                this->generate_table(search_correct_value(menu));
            }
        }
        else
        {
            gout.load_font("LiberationSans-Regular.ttf",20);
            if (single_player)
            {
                single_player_game(game,ev);
            }
            else
            {
                multi_player_game(game,ev);
            }
        }
        gout << refresh;
    }
}

void Application::clear_screen()
{
    gout << color(0,0,0);
    gout << move_to(0,0);
    gout << box(window_width_height,window_width_height);
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








