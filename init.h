#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include "function.h"
#include "object.h"

static Object shooter;
static Enemy* enemies = new Enemy[ENEMY_NUMS];
static TextObject text;
static int x_mouse, y_mouse;
static bool isMute = false;
static bool quit = false;

bool Init();
void Init_Enemy(Enemy* enemies);
void Set_Menu_End_Game(TextObject text, TTF_Font* font);
#endif // INIT_H_INCLUDED
