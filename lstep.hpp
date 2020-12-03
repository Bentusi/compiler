#include <stdio.h>

/**********************************************************/
/**/
/**********************************************************/
class type
{
private:
    /* data */
public:
    type(/* args */);
    ~type();

    virtual type* reduce() = 0;
    virtual bool  reduceable() = 0;
    virtual void  string() = 0;
};

type::type(/* args */)
{
}

type::~type()
{
}

/**********************************************************/
/**/
/**********************************************************/
class num : public type
{
private:
    int m_value;
    /* data */
public:
    num(int init);
    ~num();
    type* reduce();
    bool  reduceable();
    void  string();
    int   value();
};

num::num(int init)
{
    m_value = init;
}

num::~num()
{
}

void num::string()
{
    printf("(%d)", m_value);
}

type* num::reduce()
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
class add : public type
{
private:
    type* m_left;
    type* m_right;
public:
    add(type* left, type* right);
    ~add();
    type* reduce();
    bool  reduceable();
    void  string();
};

add::add(type* left, type* right)
{
    m_left  = left;
    m_right = right;
}

add::~add()
{
}

void add::string()
{
    printf("(");
    m_left->string();
    printf(" + ");
    m_right->string();
    printf(")");
}

type* add::reduce()
{
    if (m_left->reduceable())
    {
        return new add(m_left->reduce(), m_right);
    }
    else if (m_right->reduceable())
    {
        return new add(m_left, m_right->reduce());
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
class mul : public type
{
private:
    type* m_left;
    type* m_right;
public:
    mul(type* left, type* right);
    ~mul();
    type* reduce();
    bool  reduceable();
    void  string();
};

mul::mul(type* left, type* right)
{
    m_left  = left;
    m_right = right;
}

mul::~mul()
{
}

void mul::string()
{
    printf("(");
    m_left->string();
    printf(" * ");
    m_right->string();
    printf(")");
}

type* mul::reduce()
{
    if (m_left->reduceable())
    {
        return new mul(m_left->reduce(), m_right);
    }
    else if (m_right->reduceable())
    {
        return new mul(m_left, m_right->reduce());
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

/**********************************************************/
/**/
/**********************************************************/
class mathine
{
private:
    type* m_pc;
public:
    mathine();
    ~mathine();

    void run(type* pc);
    void step(type* pc);
};

mathine::mathine()
{
}

void mathine::run(type* pc)
{
    pc->string();
    printf("\n");
    while (pc->reduceable())
    {
        pc = pc->reduce();
        pc->string();
        printf("\n");
    }
}

void mathine::step(type* pc)
{
    if (pc->reduceable())
    {
        pc = pc->reduce();
    }
    pc->string();
    printf("\n");
}
