#include "function.h"
#include "object.h"
#include "init.h"
#include "menu.h"
#include "game.h"

int main(int argc, char* argv[])
{
    if (Init() == false) return 0;
    Game_Running();
    return 0;
}
