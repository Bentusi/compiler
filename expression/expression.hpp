#include <stdio.h>

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

    virtual expr* reduce() = 0;
    virtual bool  reduceable() = 0;
    virtual void  string() = 0;
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
    expr* reduce();
    bool  reduceable();
    void  string();
    int   value();
};

boolean::boolean(bool init)
{
    m_value = init;
}

boolean::~boolean()
{
}

void boolean::string()
{
    printf("(%s)", m_value ? "True":"False");
}

expr* boolean::reduce()
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
    expr* reduce();
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

expr* num::reduce()
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
    expr* reduce();
    bool  reduceable();
    void  string();
};

add::add(expr* left, expr* right)
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

expr* add::reduce()
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
class lt : public expr
{
private:
    expr* m_left;
    expr* m_right;
public:
    lt(expr* left, expr* right);
    ~lt();
    expr* reduce();
    bool  reduceable();
    void  string();
};

lt::lt(expr* left, expr* right)
{
    m_left  = left;
    m_right = right;
}

lt::~lt()
{
}

void lt::string()
{
    printf("(");
    m_left->string();
    printf(" < ");
    m_right->string();
    printf(")");
}

expr* lt::reduce()
{
    if (m_left->reduceable())
    {
        return new lt(m_left->reduce(), m_right);
    }
    else if (m_right->reduceable())
    {
        return new lt(m_left, m_right->reduce());
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
    expr* reduce();
    bool  reduceable();
    void  string();
};

mul::mul(expr* left, expr* right)
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

expr* mul::reduce()
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
    expr* m_pc;
public:
    mathine();
    ~mathine();

    void run(expr* pc);
    void step(expr* pc);
};

mathine::mathine()
{
}

void mathine::run(expr* pc)
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

void mathine::step(expr* pc)
{
    if (pc->reduceable())
    {
        pc = pc->reduce();
    }
    pc->string();
    printf("\n");
}
