#ifndef __EXPRESSION_HPP__
#define __EXPRESSION_HPP__

#include <string>
#include <iostream>
#include <map>

using namespace std;

class env;
/**********************************************************/
/**/
/**********************************************************/
class expr
{
private:
    /* data */
public:
    expr(/* args */);
    ~expr();

    virtual expr* reduce(env *) = 0;
    virtual bool  reduceable() = 0;
    virtual void  to_s() = 0;
};

expr::expr(/* args */)
{
}

expr::~expr()
{
}

/**********************************************************/
/**/
/**********************************************************/
class boolean : public expr
{
private:
    bool m_value;
    /* data */
public:
    boolean(bool init);
    ~boolean();
    expr* reduce(env *);
    bool  reduceable();
    void  to_s();
    int   value();
};

boolean::boolean(bool init)
{
    m_value = init;
}

boolean::~boolean()
{
}

void boolean::to_s()
{
    cout << (m_value ? "True":"False");
}

expr* boolean::reduce(env* e)
{
    return this;
}

bool boolean::reduceable()
{
    return false;
}

int boolean::value()
{
    return m_value;
}

/**********************************************************/
/**/
/**********************************************************/
class num : public expr
{
private:
    int m_value;
    /* data */
public:
    num(int init);
    ~num();
    expr* reduce(env *);
    bool  reduceable();
    void  to_s();
    int   value();
};

num::num(int init)
{
    m_value = init;
}

num::~num()
{
}

void num::to_s()
{
    cout << m_value;
}

expr* num::reduce(env* e)
{
    return this;
}

bool num::reduceable()
{
    return false;
}

int num::value()
{
    return m_value;
}

/**********************************************************/
/**/
/**********************************************************/
class add : public expr
{
private:
    expr* m_left;
    expr* m_right;
public:
    add(expr* left, expr* right);
    ~add();
    expr* reduce(env *);
    bool  reduceable();
    void  to_s();
};

add::add(expr* left, expr* right)
{
    m_left  = left;
    m_right = right;
}

add::~add()
{
}

void add::to_s()
{
    cout << "(";
    m_left->to_s();
    cout << " + ";
    m_right->to_s();
    cout << ")";
}

expr* add::reduce(env* e)
{
    if (m_left->reduceable())
    {
        return new add(m_left->reduce(e), m_right);
    }
    else if (m_right->reduceable())
    {
        return new add(m_left, m_right->reduce(e));
    }
    else
    {
        return new num(((num*)m_left)->value() + ((num*)m_right)->value());
    }
}

bool add::reduceable()
{
    return true;
}

/**********************************************************/
/**/
/**********************************************************/
class lt : public expr
{
private:
    expr* m_left;
    expr* m_right;
public:
    lt(expr* left, expr* right);
    ~lt();
    expr* reduce(env *);
    bool  reduceable();
    void  to_s();
};

lt::lt(expr* left, expr* right)
{
    m_left  = left;
    m_right = right;
}

lt::~lt()
{
}

void lt::to_s()
{
    cout << "(";
    m_left->to_s();
    cout << " < ";
    m_right->to_s();
    cout << ")";
}

expr* lt::reduce(env* e)
{
    if (m_left->reduceable())
    {
        return new lt(m_left->reduce(e), m_right);
    }
    else if (m_right->reduceable())
    {
        return new lt(m_left, m_right->reduce(e));
    }
    else
    {
        return new boolean(((num*)m_left)->value() < ((num*)m_right)->value());
    }
}

bool lt::reduceable()
{
    return true;
}

/**********************************************************/
/**/
/**********************************************************/
class mul : public expr
{
private:
    expr* m_left;
    expr* m_right;
public:
    mul(expr* left, expr* right);
    ~mul();
    expr* reduce(env*);
    bool  reduceable();
    void  to_s();
};

mul::mul(expr* left, expr* right)
{
    m_left  = left;
    m_right = right;
}

mul::~mul()
{
}

void mul::to_s()
{
    cout << "(";
    m_left->to_s();
    cout << " * ";
    m_right->to_s();
    cout << ")";
}

expr* mul::reduce(env* e)
{
    if (m_left->reduceable())
    {
        return new mul(m_left->reduce(e), m_right);
    }
    else if (m_right->reduceable())
    {
        return new mul(m_left, m_right->reduce(e));
    }
    else
    {
        return new num(((num*)m_left)->value() * ((num*)m_right)->value());
    }
}

bool mul::reduceable()
{
    return true;
}

#endif