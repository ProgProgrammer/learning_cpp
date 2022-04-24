#pragma once
#include <iostream>

class MoverInterface
{
private:
    int x;
    int y;
    int v;

public:
    virtual void Calculate(const int & timeStamp) = 0;
    virtual int GetX() const = 0;
    virtual int GetY() const = 0;
};

class LineMover : public MoverInterface
{
private:
    int x;
    int y;
    int v;

public:
    LineMover(const int & c_x = 0, const int & c_y = 0, const int & speed = 0);
    virtual void Calculate(const int & timeStamp);
    virtual int GetX() const;
    virtual int GetY() const;
};

class RandomMover : public MoverInterface
{
private:
    int x;
    int y;
    int v;

public:
    RandomMover(const int & c_x = 0, const int & c_y = 0, const int & speed = 0);
    virtual void Calculate(const int & timeStamp);
    virtual int GetX() const;
    virtual int GetY() const;
};