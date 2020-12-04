
#include "expression.hpp"
#include <string>
#include <iostream>

using namespace std;

class assign : public expr
{
private:
    string m_name;
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
}

assign::~assign()
{
}

expr* assign::reduce(env* e)
{
    return e->get(m_name);
}

bool  assign::reduceable()
{
    return true;
}

void  assign::to_s()
{
    cout << "(" << m_name;
    cout << ")";
}
