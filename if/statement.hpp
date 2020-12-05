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
    cout << "IF ";
    m_con->to_s();
    cout << " THEN ";
    m_t->to_s();
    cout << " ELSE ";
    m_f->to_s();
    cout << " END";
}


/**********************************************************/
/**/
/**********************************************************/
class SEQ : public expr
{
private:
    expr* m_f;
    expr* m_s;
public:
    SEQ(expr* f, expr* s);
    ~SEQ();

    expr* reduce(env* e);
    bool  reduceable();
    void  to_s();
};

SEQ::SEQ(expr* f, expr* s)
{
    m_f = f;
    m_s = s;
}

SEQ::~SEQ()
{
}

expr* SEQ::reduce(env* e)
{
    if (m_f->reduceable())
    {
        return new SEQ(m_f->reduce(e), m_s);
    }
    else
    {
        return m_s;
    }
}

bool SEQ::reduceable()
{
    return true;
}

void SEQ::to_s()
{
    cout << "(";
    m_f->to_s();
    cout << "; ";
    m_s->to_s();
    cout << ")";
}

/**********************************************************/
/**/
/**********************************************************/
class WHILE : public expr
{
private:
    expr* m_con;
    expr* m_t;
public:
    WHILE(expr* con, expr* t);
    ~WHILE();

    expr* reduce(env* e);
    bool  reduceable();
    void  to_s();
};

WHILE::WHILE(expr* con, expr* t)
{
    m_con = con;
    m_t = t;
}

WHILE::~WHILE()
{
}

expr* WHILE::reduce(env* e)
{
    return new IF(m_con->reduce(e), new SEQ(m_t, this), new donothing());
}

bool WHILE::reduceable()
{
    return true;
}

void WHILE::to_s()
{
    cout << "WHILE ";
    m_con->to_s();
    cout << " THEN ";
    m_t->to_s();
    cout << " END";
}

#endif