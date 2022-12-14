#include "cd.h"

Cd::Cd(const char* s1, const char* s2, int n, double x)
{
    if (performers == nullptr)
        performers = new char[strlen(s1) + 1];

    if (label == nullptr)
        label = new char[strlen(s2) + 1];

    strcpy_s(performers, strlen(s1) + 1, s1);
    strcpy_s(label, strlen(s2) + 1, s2);
    selections = n;
    playtime = x;
}

Cd::Cd(const Cd& d)
{
    if (performers == nullptr)
        performers = new char[strlen(d.performers) + 1];

    if (label == nullptr)
        label = new char[strlen(d.label) + 1];

    strcpy_s(performers, strlen(d.performers) + 1, d.performers);
    strcpy_s(label, strlen(d.label) + 1, d.label);
    selections = d.selections;
    playtime = d.playtime;
}

Cd::Cd()
{
    if (performers == nullptr)
        performers = new char[5];

    if (label == nullptr)
        label = new char[5];

    strcpy_s(performers, 5, "null");
    strcpy_s(label, 5, "null");
    selections = 0;
    playtime = 0;
}

Cd::~Cd()
{
    if (performers != nullptr)
    {
        delete[] performers;
        performers = nullptr;
    }

    if (label != nullptr)
    {
        delete[] label;
        label = nullptr;
    }
}

void Cd::Report() const
{
    std::cout << "performers = " << performers << std::endl;
    std::cout << "label = " << label << std::endl;
    std::cout << "selections = " << selections << std::endl;
    std::cout << "playtime = " << playtime << std::endl << std::endl;
}

Cd& Cd::operator=(const Cd& cd)
{
    if (this == &cd)
        return *this;

    if (performers != nullptr)
        delete [] performers;

    performers = new char[strlen(performers + 1)];
    strcpy_s(performers, strlen(cd.performers) + 1, cd.performers);

    if (label != nullptr)
        delete [] label;

    label = new char[strlen(label + 1)];
    strcpy_s(label, strlen(cd.label) + 1, cd.label);

    selections = cd.selections;
    playtime = cd.playtime;

    return *this;
}

Classic::Classic(const char* m, const char* s1, const char* s2, int n, double x) : Cd(s1, s2, n, x)
{
    if (m_composition == nullptr)
        m_composition = new char[strlen(m) + 1];

    strcpy_s(m_composition, strlen(m) + 1, m);
}

Classic::Classic() : Cd("null", "null", 0, 0)
{
    if (m_composition == nullptr)
        m_composition = new char[5];

    strcpy_s(m_composition, 5, "null");
}

Classic::~Classic()
{
    if (m_composition != nullptr)
    {
        delete[] m_composition;
        m_composition = nullptr;
    }
}

void Classic::Report() const
{
    std::cout << "musical composition = " << m_composition << std::endl;
    Cd::Report();
}

Classic& Classic::operator=(const Classic& cl)
{
    if (this == &cl)
        return *this;

    Cd::operator=(cl);
    
    if (m_composition != nullptr)
        delete[] m_composition;

    m_composition = new char[strlen(cl.m_composition) + 1];

    strcpy_s(m_composition, strlen(cl.m_composition) + 1, cl.m_composition);

    return *this;
}