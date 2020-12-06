#ifndef __STATEMENG_HPP__
#define __STATEMENG_HPP__

#include "variable.hpp"

class donothing : public expr
{
private:
    /* data */
public:
    donothing(/* args */);
    ~donothing();

    expr* reduce(env *);
    bool  reduceable();
    void  to_s();
};

donothing::donothing(/* args */)
{
}

donothing::~donothing()
{
}

expr* donothing::reduce(env *)
{
    return this;
}

bool  donothing::reduceable()
{
    return false;
}

void  donothing::to_s()
{
    cout << "DoNothing";
}

#endif