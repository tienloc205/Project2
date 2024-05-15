#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "function.h"
#include "object.h"
#include "init.h"
#include "menu.h"

void Game_Running()
{
    SDL_Rect shooter_rect = {SCREEN_WIDTH/2, SCREEN_HEIGHT - SHOOTER_HEIGHT, SHOOTER_WIDTH, SHOOTER_HEIGHT};
    shooter.Set_Rect(shooter_rect);
    Item hp_plus;
    SDL_Rect hp_plus_rect;
    hp_plus_rect.y = -(500+rand()%SCREEN_HEIGHT);
    hp_plus_rect.x = 500+rand()%SCREEN_WIDTH;
    hp_plus_rect.w = 50;
    hp_plus_rect.h = 50;
    hp_plus.Set_Rect(hp_plus_rect);

    TTF_Font* font = TTF_OpenFont("Roboto-Regular.ttf", 25);
    text.Inf = "Score : 00";

    Mix_PlayMusic(background_sound, -1);

    SDL_Event event;
    while (!quit)
    {
        SDL_GetMouseState(&x_mouse, &y_mouse);
        cout << x_mouse << " " << y_mouse << endl;
        while (SDL_PollEvent(&event)!=0)
        {
            if (event.type == SDL_QUIT) {quit = true;}
            shooter.HandleKey(event, bullet_sound);
            Handle_Menu(event);
            Difficulty(event, ENEMY_NUMS);
        }

        if (state == play or state == retry){
        state = play;
        LoadImage("background.png", renderer, NULL);
        shooter.Move(SCREEN_WIDTH, SCREEN_HEIGHT);
        shooter_rect = shooter.Get_Rect();
        if (SHOOTER_HEALTH>0)LoadImage("plane.png", renderer, &shooter_rect);

        for (int i=0;i<ENEMY_NUMS;i++)
        {
            Enemy* enemy = (enemies + i);
            enemy->Move(SCREEN_WIDTH, SCREEN_HEIGHT, 3);
            SDL_Rect enemy_rect = enemy->Get_Rect();
            LoadImage("enemy.png", renderer, &enemy_rect);
            enemy->Make_Bullet_Move(SCREEN_WIDTH, SCREEN_HEIGHT, shooter_rect);


            if (Check_Collision(shooter_rect, enemy_rect) == true)
            {
                SHOOTER_HEALTH--;
                enemy->Reset();
            }
        }

        vector <Bullet*> ammo_list = shooter.Get_Bullet_List();
        for (unsigned int i=0;i<ammo_list.size();i++)
        {
            Bullet* ammo = ammo_list.at(i);
            if (ammo != NULL)
            {
                if (ammo->Get_Active() == true)
                {
                    ammo->Move(SCREEN_WIDTH, 0, -20);
                    SDL_Rect ammo_rect = ammo->Get_Rect();
                    LoadImage("bul_laser.png", renderer,&ammo_rect);


                    for (int t=0;t<ENEMY_NUMS;t++)
                    {
                        Enemy* enemy = (enemies+t);
                        SDL_Rect enemy_rect = enemy->Get_Rect();
                        if (Check_Collision(ammo_rect, enemy_rect) == true)
                        {
                            enemy->Reset();
                            ammo->Set_Active(false);
                            text.Inf = text.Change_Score();
                        }
                    }
                    if (SHOOTER_HEALTH<=0) ammo->Set_Active(false);
                }
                else
                {
                    if (ammo !=NULL)
                    {
                        ammo_list.erase(ammo_list.begin()+i);
                        shooter.Set_Bullet_List(ammo_list);
                        delete ammo;
                        ammo = NULL;
                    }
                }
            }
        }

        Hp_Bar("hp.png");
        hp_plus.Move(shooter_rect);
        LoadImage("item.png", renderer, &hp_plus_rect);
        hp_plus_rect = hp_plus.Get_Rect();
        SDL_Rect scoring_text_rect;
        scoring_text_rect.x = SCREEN_WIDTH/2 - text.Inf.length()/2;
        scoring_text_rect.y = 0;
        scoring_text_rect.w = 100;
        scoring_text_rect.h = 30;
        LoadText(text.Inf, font, &scoring_text_rect);

        if (SHOOTER_HEALTH <= 0)
        {
            Set_Menu_End_Game(text, font);
        }
        }
        SDL_RenderPresent(renderer);
    }
    delete [] enemies;
    TTF_CloseFont(font);
    Quit();

}
#endif // GAME_H_INCLUDED
