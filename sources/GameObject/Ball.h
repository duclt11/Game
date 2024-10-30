#pragma once
#include "GameEngine\pch.h"

class Paddle;
class Brick;

class Ball
{
public:
    Ball();
    ~Ball();
    void Init();
    void Draw();
    void Update();
    void SetActive(bool active);

    void OnCollision();
    void AttachPaddle(std::shared_ptr<Paddle> paddle);
    void AttachBricks(std::vector<std::shared_ptr<Brick>> bricks);

    void SetOnScoreChangeFunction(std::function<void(int)> cb);

    int GetScore();
    void ChangeScore(int num);
private:
    std::shared_ptr<Paddle> m_paddle;
    std::vector<std::shared_ptr<Brick>> m_bricks;

    Vector2 m_position;
    int m_size;
    int m_ballDamage;
    float m_speed;
    Vector2 m_moveVector;
    bool m_active;
    int m_score;
    int m_scorePerBrick;

    std::function<void(int)> m_onScoreChangeFunction;

};