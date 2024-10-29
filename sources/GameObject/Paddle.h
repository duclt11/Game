#pragma once
#include "GameEngine\pch.h"

class Paddle
{
public:
    Paddle();
    ~Paddle();
    void Init();
    void Move(int key);
    void Draw();
    void Update();

    Vector2 GetPosition();
    Vector2 GetSize();

    void DecreaseHP(int num = 1);
private:
    Vector2 m_position;
    Vector2 m_size;
    float m_speed;
    int m_hp;

};