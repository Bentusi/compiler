#ifndef __VARIABLE_HPP__
#define __VARIABLE_HPP__

#include "expression.hpp"
#include <string>
#include <iostream>
#include "env.hpp"
using namespace std;


/**********************************************************/
/**/
/**********************************************************/
class var : public expr
{
private:
    string m_name;
public:
    var(string str);
    ~var();
    expr* reduce(env* e);
    bool  reduceable();
    void  to_s();
};

var::var(string str)
{
    m_name = str;
}

var::~var()
{
}

expr* var::reduce(env* e)
{
    return e->get(m_name);
}

bool  var::reduceable()
{
    return true;
}

void  var::to_s()
{
    cout << m_name;
}

#endif