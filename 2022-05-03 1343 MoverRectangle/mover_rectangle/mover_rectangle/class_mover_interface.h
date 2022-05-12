#pragma once

class MoverInterface
{
public:
    virtual void CalculateXU() = 0;
    virtual void CalculateXD() = 0;
    virtual void CalculateYU() = 0;
    virtual void CalculateYD() = 0;
    virtual int GetX() const = 0;
    virtual int GetY() const = 0;
};