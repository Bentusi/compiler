#ifndef __ASSIGN_HPP__
#define __ASSIGN_HPP__

#include "statement.hpp"
#include <string>
#include <iostream>

using namespace std;

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
    cout << "(" << m_name << "=";
    m_expr->to_s();
    cout << ")";
}

#endif
