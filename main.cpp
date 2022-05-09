#include "application.hpp"
#include "choosetext.hpp"
#include "setnumber.hpp"
#include "button.hpp"

class App : public Application
{
private:
    Button* b;
    Setnumber* s;
    Choosetext* c;
public:
    App(int widthheight, int game_frame_) : Application(widthheight,game_frame_)
    {
        b = new Button(0.5*(widthheight-200),0.1*widthheight,200,100,5,255,255,255,this,"Play");
        s = new Setnumber(0.5*(widthheight-200),0.35*widthheight,200,100,5,255,255,255,15,30,20,this);
        c = new Choosetext(0.5*(widthheight-200),0.6*widthheight,200,300,5,255,255,255,{"Single Player","Multiplayer"},3,this);
    }
};

int main()
{
    App* a = new App(920,20);
    a->event_loop();
    return 0;
}
