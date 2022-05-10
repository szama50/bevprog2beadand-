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

bool allowed_move(int size_of_table,int focus, vector<Widget*> game)
{
    vector<int> nearbyareas;
    if (focus==-1)
        return false;
    if (focus == 0) //top left corner
        nearbyareas = {focus+1,focus+size_of_table,focus+size_of_table+1};
    else if (focus == size_of_table-1) //top right corner
        nearbyareas = {focus-1,focus+size_of_table,focus+size_of_table-1};
    else if (focus == int(game.size()-size_of_table)) //bottom left corner
        nearbyareas = {focus+1,focus-size_of_table,focus-size_of_table+1};
    else if (focus == int(game.size()-1)) //bottom right corner
        nearbyareas = {focus-1,focus-size_of_table,focus-size_of_table-1};
    else if (focus % size_of_table == size_of_table-1)
        nearbyareas = {focus-1,focus-size_of_table,focus+size_of_table,focus-size_of_table-1,focus+size_of_table-1};
    else if (focus % size_of_table == 0)
        nearbyareas = {focus+1,focus-size_of_table,focus+size_of_table,focus-size_of_table+1,focus+size_of_table+1};
    else if (focus<size_of_table)
        nearbyareas = {focus+1,focus-1,focus+size_of_table,focus+size_of_table-1,focus+size_of_table+1};
    else if (focus>int(game.size()-1-size_of_table))
        nearbyareas = {focus+1,focus-1,focus-size_of_table,focus-size_of_table+1,focus-size_of_table-1};
    else
        nearbyareas = {focus+1,focus-1,focus+size_of_table,focus+size_of_table-1,focus+size_of_table+1,focus-size_of_table,
                      focus-size_of_table-1,focus-size_of_table+1};
    for (size_t i = 0; i < nearbyareas.size(); i++)
    {
        if (game[nearbyareas[i]]->string_getter() != " ")
        {
            return true;
        }
    }
    return false;
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

void multi_player_game(vector<Widget*> game,int size_of_table,event ev)
{
    int focus = -1;
    static int counter = 1;
    for (size_t i = 0; i < game.size(); i++)
    {
        game[i]->setactivity(ev);
        game[i]->place();
        if (game[i]->bool_getter())
            focus = i;
    }
    //First move
    if (counter == 1 && ev.button == btn_left && focus!=-1)
    {
        counter++;
        game[focus]->event_handler(ev);
    }
    //First move
    if (ev.button == btn_left && allowed_move(size_of_table,focus,game))
    {
        game[focus]->event_handler(ev);
    }
}

void Application::event_loop()
{
    for (size_t i = 0; i < menu.size(); i++)
        menu[i]->place();
    gout << refresh;
    event ev;

    int size_of_map = 15;
    while(gin >> ev && ev.button != key_escape)
    {
        if (!ingame)
        {
            this->clear_screen();
            in_menu(menu,ev,single_player);
            if (ingame)
            {
                size_of_map = search_correct_value(menu);
                this->generate_table(size_of_map);
            }
        }
        else
        {
            if (single_player)
            {
                single_player_game(game,ev);
            }
            else
            {
                multi_player_game(game,size_of_map,ev);
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








