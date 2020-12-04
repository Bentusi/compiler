#ifndef __STATEMENG_HPP__
#define __STATEMENG_HPP__

#include "expression.hpp"
#include <string>
#include <iostream>
#include "env.hpp"
using namespace std;

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


/**********************************************************/
/**/
/**********************************************************/
class assign : public expr
{
private:
    string m_name;
    expr*  m_expr;
    /* data */
public:
    assign(string name, expr* exp);
    ~assign();

    expr* reduce(env* e);
    bool  reduceable();
    void  to_s();
};

assign::assign(string name, expr* exp)
{
    m_name = name;
    m_expr = exp;
}

assign::~assign()
{
}

expr* assign::reduce(env* e)
{
    if (m_expr->reduceable())
    {
        return new assign(m_name, m_expr->reduce(e));
    }
    else
    {
        e->set(m_name, m_expr);
        return new donothing();
    }
}

bool  assign::reduceable()
{
    return true;
}

void  assign::to_s()
{
    cout << "(" << m_name << " = ";
    m_expr->to_s();
    cout << ")";
}

#endif