#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "function.h"
#include "init.h"
#include "object.h"

void Reset_Object()
{
    for(int i=0;i<ENEMY_NUMS;i++)
    {
        Enemy* enemy = (enemies+i);
        for (int t=0;t<enemy->Get_Bullet_List().size();t++)
        {
            Bullet* enemy_ammo = enemy->Get_Bullet_List().at(t);
            enemy_ammo->Set_Active(false);
        }
        enemy->Reset();
    }
    SDL_Rect shooter_rect = {SCREEN_WIDTH/2, SCREEN_HEIGHT - SHOOTER_HEIGHT, SHOOTER_WIDTH, SHOOTER_HEIGHT};
    shooter.Set_Rect(shooter_rect);
    text.Inf = "Score : 00";
}

void Handle_Menu(SDL_Event event)
{
    if (state == start )
    {

        if (isMute)
        {
            LoadImage("start2.jpg", renderer, NULL);
        }
        else
        {
            LoadImage("start1.jpg", renderer, NULL);
        }
        if (345 <= x_mouse && x_mouse <= SCREEN_WIDTH && 655 <= y_mouse && y_mouse <= SCREEN_HEIGHT && event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (isMute)
            {
                isMute = false;
                Mix_ResumeMusic();
            }
            else
            {
                isMute = true;
                Mix_PauseMusic();
            }
        }
        if ((80 <= x_mouse && x_mouse <= 80+240 && 270 <= y_mouse && y_mouse <= 270+50 && event.type == SDL_MOUSEBUTTONDOWN) or state == difficulty)
        {
            state = difficulty;
        }

        if (80 <= x_mouse && x_mouse <= 80+240 && 390 <= y_mouse && y_mouse <= 390+50 && event.type == SDL_MOUSEBUTTONDOWN)
        {
            quit = true;
        }
    }

    if (state == play and event.key.keysym.sym == SDLK_RETURN)
    {
        state = pause;
        SDL_Rect pause_game_rect = {SCREEN_WIDTH/2-200, SCREEN_HEIGHT/2-200, 400, 300};
        LoadImage("pause.png", renderer, &pause_game_rect);
    }

    if (state == pause)
    {
        if (event.key.keysym.sym == SDLK_o)
        {
            state = retry;
        }
        if (event.key.keysym.sym == SDLK_e)
        {
            state = start;
        }
    }

    if(state == play and SHOOTER_HEALTH<=0)
    {
        if (120 <= x_mouse && x_mouse <= 120+75 && 380 <= y_mouse && y_mouse <= 380+75 && event.type == SDL_MOUSEBUTTONDOWN)
        {
            state = start;
            SHOOTER_HEALTH = 5;
            Reset_Object();
        }
        if (205 <= x_mouse && x_mouse <= 205+75 && 380 <= y_mouse && y_mouse <= 380+75 && event.type == SDL_MOUSEBUTTONDOWN)
        {
            state = retry;
            SHOOTER_HEALTH = 5;
            Reset_Object();
            Init_Enemy(enemies);
        }
    }
}

void Difficulty(SDL_Event event, int &enemy_num)
{
    if (state == difficulty){
    SDL_RenderClear(renderer);
    LoadImage("difficulty.png", renderer, NULL);
    switch (event.key.keysym.sym)
    {
    case SDLK_4:
        {
            enemy_num= 4;
            cout << enemy_num;
            state = play;
            Init_Enemy(enemies);
            break;
        }
    case SDLK_6:
        {
            enemy_num = 6;
            cout << enemy_num;
            state = play;
            Init_Enemy(enemies);
            break;
        }
    case SDLK_8:
        {
            enemy_num = 8;
            cout << enemy_num;
            state = play;
            Init_Enemy(enemies);
            break;
        }
    }
    }
}

#endif // MENU_H_INCLUDED
