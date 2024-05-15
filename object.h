#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include "function.h"


struct Bullet;

class Object
{
protected:
    SDL_Rect rect;
    int dx = 0;
    int dy = 0;
    bool active;
    std::vector <Bullet*> bullet_list;
public:
    void Set_Rect(SDL_Rect rect_) {rect = rect_;}
    SDL_Rect Get_Rect() {return rect;}

    void Set_Active(bool active_) {active = active_;}
    bool Get_Active() {return active;}

    void HandleKey(SDL_Event event, Mix_Chunk* bul_sound);
    void Move(const int& x_des, const int y_des);

    void Set_Bullet_List(std::vector <Bullet*> bullet_list_) {bullet_list = bullet_list_;}
    vector <Bullet*> Get_Bullet_List() {return bullet_list;}

};

struct Bullet : public Object
{
    void Move(const int& x_des, const int& y_des, int y);
    void Enemy_Move(const int& x_des, const int& y_des, int y);
};

struct Enemy : public Object
{
    ~Enemy();
    void Move(const int& x_des, const int& y_des, int y);
    void Init_Bullet(Bullet* enemy_bullet);
    void Make_Bullet_Move(const int& x_des, const int& y_des, SDL_Rect player);
    void Reset();
};

struct TextObject : public Object
{
    string Inf;
    int Score;
    int High_Score;

    int Check_Digit();
    string Change_Score();
};

struct Item : public Object
{
    void Move(SDL_Rect player)
    {
        rect.y +=10;
        if (Check_Collision(rect,player) == true)
        {
            rect.y = -rand()%SCREEN_HEIGHT;
            rect.x = rand()%SCREEN_WIDTH;
            if (SHOOTER_HEALTH<5)SHOOTER_HEALTH++;
        }
        if (rect.y > SCREEN_HEIGHT)
        {
            SDL_Delay(1000);
            rect.y = -rand()%SCREEN_HEIGHT;
            rect.x = rand()%SCREEN_WIDTH;
        }
    }
};
#endif // OBJECT_H_INCLUDED
