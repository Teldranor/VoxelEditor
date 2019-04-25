#include "App.h"

int main( int argc, char * argv[] )
{
    App* app = App::getApp();
    app->init();

    app->loop();

    return 0;
}
