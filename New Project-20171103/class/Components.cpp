#pragma once
#include "ECS.cpp"

class PositionComponent : public Component
{
    
private:
    int xPos;
    int yPos;
public:
    int x(){ return xPos; }
    int y(){ return yPos; }
    
    void Initialize() override
    {
        xPos = 0;
        yPos = 0;
    }
    
    void Update() override
    {
        xPos++;
        yPos++;
    }
    
    void SetPos( int x, int y)
    {
        xPos = x;
        yPos = y;
    }
    
};