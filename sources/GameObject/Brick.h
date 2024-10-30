#pragma once
#include "GameEngine\pch.h"

class Brick
{
public:
    Brick(Vector2 position, Vector2 size);
    ~Brick();
    void Init();
    void Move(int key);
    void Draw();
    void Update();

    Vector2 GetPosition();
    Vector2 GetSize();

    bool IsActive();
    void DecreaseHP(int num = 1);

private:
    Vector2 m_position;
    Vector2 m_size;
    int m_hp;
    bool m_active;
};