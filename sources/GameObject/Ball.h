#pragma once
#include "GameEngine\pch.h"

class Paddle;

class Ball
{
public:
    Ball();
    ~Ball();
    void Init();
    void Draw();
    void Update();
    void SetActive(bool active);
    void Dead();
    void OnCollision();
    void AttachPaddle(std::shared_ptr<Paddle> paddle);
private:
    std::shared_ptr<Paddle> m_paddle;

    Vector2 m_position;
    int m_size;
    float m_speed;
    Vector2 m_moveVector;
    bool m_active;
};