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
    cout << "do-nothing";
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


/**********************************************************/
/**/
/**********************************************************/
class IF : public expr
{
private:
    expr* m_con;
    expr* m_t;
    expr* m_f;
public:
    IF(expr* con, expr* t, expr* f);
    ~IF();

    expr* reduce(env* e);
    bool  reduceable();
    void  to_s();
};

IF::IF(expr* con, expr* t, expr* f)
{
    m_con = con;
    m_t = t;
    m_f = f;
}

IF::~IF()
{
}

expr* IF::reduce(env* e)
{
    if (m_con->reduceable())
    {
        return new IF(m_con->reduce(e), m_t, m_f);
    }
    else
    {
        if (((boolean*)m_con)->value())
        {
            return m_t;
        }
        else
        {
            return m_f;
        }
    }
}

bool IF::reduceable()
{
    return true;
}

void IF::to_s()
{
    cout << "IF (";
    m_con->to_s();
    cout << ") THEN ";
    m_t->to_s();
    cout << " ELSE ";
    m_f->to_s();
    cout << " END";
}

#endif