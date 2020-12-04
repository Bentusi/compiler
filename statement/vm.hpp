#ifndef __VM_HPP__
#define __VM_HPP__

#include "expression.hpp"
#include "env.hpp"

/**********************************************************/
/**/
/**********************************************************/
class mathine
{
private:
    expr* m_pc;
    env*  m_env;
public:
    mathine();
    ~mathine();

    void run(expr* pc, env* e);
    void step(expr* pc, env* e);
};

mathine::mathine()
{
}

void mathine::run(expr* pc, env* e)
{
    pc->to_s();
    cout << ",";
    e->print();
    cout << endl;
    while (pc->reduceable())
    {
        pc = pc->reduce(e);
        pc->to_s();
        cout << ",";
        e->print();
        cout << endl;
    }
}

void mathine::step(expr* pc, env* e)
{
    if (pc->reduceable())
    {
        pc = pc->reduce(e);
    }
    pc->to_s();
    cout << ",";
    e->print();
    cout << endl;
}

#endif