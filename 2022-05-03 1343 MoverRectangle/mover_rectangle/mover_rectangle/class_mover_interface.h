#pragma once

class MoverInterface
{
public:
    virtual void CalculateX(const int & timeStamp) = 0;
    virtual void CalculateY(const int & timeStamp) = 0;
    virtual int GetX() const = 0;
    virtual int GetY() const = 0;
};