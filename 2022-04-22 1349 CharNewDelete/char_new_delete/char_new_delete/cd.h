#pragma once
#include <iostream>

class Cd
{
private:
    char* performers = nullptr;
    char* label = nullptr;
    int selections;
    double playtime;

public:
    Cd(const char* s1, const char* s2, int n, double x);
    Cd(const Cd& d);
    Cd();
    virtual ~Cd();
    virtual void Report() const;
    Cd& operator=(const Cd& cd);
};

class Classic : public Cd
{
private:
    char* m_composition = nullptr;

public:
    Classic(const char* m, const char* s1, const char* s2, int n, double x);
    Classic();
    ~Classic();
    virtual void Report() const;
    Classic& operator=(const Classic& cl);
};