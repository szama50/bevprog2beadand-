#include "application.hpp"
#include "choosetext.hpp"
#include "setnumber.hpp"
#include "button.hpp"
#include "screen.hpp"

#include <cstdlib>
#include <ctime>

//A program a gomokun alapuló amőbát valósítja meg, azaz csak olyan területre lehet tenni, aminek környezetében már van 'O' vagy 'X'.

class App : public Application
{
private:
    Button* b1;
    Setnumber* s;
    Choosetext* c;
    Button* b2;
    Screen* sc;
public:
    App(int widthheight, int game_frame_) : Application(widthheight,game_frame_)
    {
        //Menu
        b1 = new Button(0.5*(widthheight-200),0.1*widthheight,200,100,5,255,255,255,this,"Play",false);
        s = new Setnumber(0.5*(widthheight-200),0.35*widthheight,200,100,5,255,255,255,15,30,20,this);
        c = new Choosetext(0.5*(widthheight-200),0.6*widthheight,200,300,5,255,255,255,{"Single Player","Multiplayer"},3,this);
        //Menu
        //Game_over_screen
        sc = new Screen(0.5*(widthheight-300),100,300,150,10,255,255,255,this);
        b2 = new Button(0.5*(widthheight-200),300,200,100,5,255,255,255,this,"Back to menu",true);
        //Game_over_screen
    }
};

int main()
{
    srand(time(NULL));
    App* a = new App(800,20);
    a->event_loop();
    return 0;
}
