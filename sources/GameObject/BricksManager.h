#pragma once
#include "GameEngine\pch.h"

class Brick;

class BricksManager
{
public:
    BricksManager();
    ~BricksManager();
    void Init();
    void Draw();
    void Update();

    void CreateBricks();
    std::vector<std::shared_ptr<Brick>> GetBricks();

    void SetOnBrickBreak(std::function<void()> cb);

private:
    std::vector<std::shared_ptr<Brick>> m_bricks;
    Vector2 m_margin; // margin of brick

    Vector2 m_levelSize; //with X is number if collum, and Y is number of row
    Vector2 m_brickSize;

    std::function<void()> m_onBrickBreakFunction;

};