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
    App(int width,int height) : Application(width,height)
    {
        b = new Button(0.5*(width-200),0.1*height,200,100,5,255,255,255,this,"Play");
        s = new Setnumber(0.5*(width-200),0.35*height,200,100,5,255,255,255,15,30,20,this);
        c = new Choosetext(0.5*(width-200),0.6*height,200,300,5,255,255,255,{"Single Player","Multiplayer"},3,this);
    }
};

int main()
{
    App* a = new App(800,800);
    a->event_loop();
    return 0;
}
