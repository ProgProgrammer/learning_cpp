#pragma once

class MoverInterface
{
public:
    virtual void Calculate(const int & timeStamp) = 0;
    virtual int GetX() const = 0;
    virtual int GetY() const = 0;
};