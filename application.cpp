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
    game_over = false;
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
    for (size_t i = 0; i < game.size(); i++)
        delete game[i];
    vector<Widget*> g_;
    int j = 0;
    int k = 0;
    for (int i = 0; i < pow(size_of_table,2); i++)
    {
        g_.push_back(new Checkbox(j*(window_width_height-2*game_frame)/size_of_table+game_frame,
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
    game = g_;
}

void in_menu(vector<Widget*> menu, event ev, bool& single_player)
{
    for (size_t i = 0; i < menu.size(); i++)
    {
        menu[i]->setactivity(ev);
        menu[i]->place();
        menu[i]->event_handler(ev);
        menu[i]->position_correction();
        if (menu[i]->string_getter()=="Single Player")
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

string diagonal_search(int vertical,int opposite,vector<Widget*> game,int size_of_table)
{
    int x_counter = 0;
    int o_counter = 0;
    int k = 0;
    int c = 2;
    if (vertical == size_of_table && opposite == 1)
        c = 0;
    for (int i = 0; i < size_of_table; i++)
    {
        k = 0;
        while(k<size_of_table-i)
        {
            if (game[i*vertical-c*i*opposite+opposite*(size_of_table-1)+k*(size_of_table+1+opposite*(-2))]->string_getter() == "X")
                x_counter++;
            else
                x_counter = 0;
            if (x_counter == 5)
                return "X";
            if (game[i*vertical-c*i*opposite+opposite*(size_of_table-1)+k*(size_of_table+1+opposite*(-2))]->string_getter() == "O")
                o_counter++;
            else
                o_counter = 0;
            if (o_counter == 5)
                return "O";
            k++;
        }
        x_counter = 0;
        o_counter = 0;
    }
    return " ";
}

string horizontal_vertical_search(bool vertical,vector<Widget*> game, int size_of_table)
{
    int ocounter = 0;
    int xcounter = 0;
    for (int i = 0; i < size_of_table; i++)
    {
        for (int j = 0; j < size_of_table; j++)
        {
            int index = i*size_of_table+j;
            if (vertical)
                index = i+j*size_of_table;
            if (game[index]->string_getter() == "X")
                xcounter++;
            else
                xcounter = 0;
            if (xcounter == 5)
                return "X";
            if (game[index]->string_getter() == "O")
                ocounter++;
            else
                ocounter = 0;
            if (ocounter == 5)
                return "O";
        }
    }
    return " ";
}

bool map_is_full(vector<Widget*> game, int size_of_table)
{
    int counter = 0;
    for (size_t i = 0; i < game.size(); i++)
    {
        if (game[i]->string_getter() != " ")
            counter++;
    }
    return (counter==size_of_table*size_of_table);
}

string gameover(vector<Widget*> game, int size_of_table)
{
    if (horizontal_vertical_search(false,game,size_of_table) == "X" || horizontal_vertical_search(true,game,size_of_table) == "X")
        return "X";
    if (horizontal_vertical_search(false,game,size_of_table) == "O" || horizontal_vertical_search(true,game,size_of_table) == "O")
        return "O";
    if (diagonal_search(1,0,game,size_of_table) == "X" || diagonal_search(size_of_table,0,game,size_of_table) == "X"
            || diagonal_search(1,1,game,size_of_table) == "X" || diagonal_search(size_of_table,1,game,size_of_table) == "X")
        return "X";
    if (diagonal_search(1,0,game,size_of_table) == "O" || diagonal_search(size_of_table,0,game,size_of_table) == "O"
            || diagonal_search(1,1,game,size_of_table) == "O" || diagonal_search(size_of_table,1,game,size_of_table) == "O")
        return "O";
    if (map_is_full(game,size_of_table))
        return "no one, map is full";
    return " ";
}

int find_focus(vector<Widget*> game,event ev)
{
    for (size_t i = 0; i < game.size(); i++)
    {
        game[i]->setactivity(ev);
        if (game[i]->bool_getter())
        {
            return i;
        }
    }
    return -1;
}

void single_player_game(vector<Widget*> game,int size_of_table,int& counter,event ev,bool& xturn)
{
    for (size_t i = 0; i < game.size(); i++)
        game[i]->place();
    int focus = find_focus(game,ev);

    //First move
    if (counter == 1 && ev.button == btn_left && focus!=-1)
    {
        counter++;
        game[focus]->modify_state("X");
        xturn = false;
    }
    //First move

    if (xturn && ev.button == btn_left && allowed_move(size_of_table,focus,game))
    {
        if (game[focus]->string_getter() == " ")
        {
            game[focus]->modify_state("X");
            xturn = false;
        }
    }

    else if (!xturn)
    {
        vector<int> allowed_areas;
        for (size_t i = 0; i < game.size(); i++)
        {
            if (allowed_move(size_of_table,i,game) && game[i]->string_getter() == " ")
                allowed_areas.push_back(i);
        }
        game[allowed_areas[rand() % allowed_areas.size()]]->modify_state("O");
        xturn = true;
    }
}

void multi_player_game(vector<Widget*> game,int size_of_table,int& counter,event ev,bool& xturn)
{
    for (size_t i = 0; i < game.size(); i++)
        game[i]->place();
    int focus = find_focus(game,ev);

    //First move
    if (counter == 1 && ev.button == btn_left && focus!=-1)
    {
        counter++;
        game[focus]->modify_state("X");
        xturn = false;
    }
    //First move

    else if (ev.button == btn_left && allowed_move(size_of_table,focus,game))
    {
        if (game[focus]->string_getter() == " ")
        {
            if (xturn)
                game[focus]->modify_state("X");
            else
                game[focus]->modify_state("O");
            xturn = !xturn;
        }
    }
}

void Application::event_loop()
{
    for (size_t i = 0; i < menu.size(); i++)
        menu[i]->place();
    gout << refresh;
    event ev;

    int size_of_map = 15;
    int counter = 1;
    bool xturn = true;
    while(gin >> ev && ev.keycode != key_escape)
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
            game_over = gameover(game,size_of_map);
            if (game_over != " ")
            {
                counter = 1;
                xturn = true;
                for (size_t i = 0; i < over.size(); i++)
                {
                    over[i]->place();
                    over[i]->setactivity(ev);
                    over[i]->event_handler(ev);
                }
            }
            else
            {
                if (single_player)
                    single_player_game(game,size_of_map,counter,ev,xturn);
                else
                    multi_player_game(game,size_of_map,counter,ev,xturn);
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

void Application::register_over_widget(Widget* widget)
{
    over.push_back(widget);
}

void Application::change_ingame_status()
{
    ingame = !ingame;
}

string Application::game_over_getter()
{
    return game_over;
}








