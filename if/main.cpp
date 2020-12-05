#include <iostream>
#include "statement.hpp"
#include "env.hpp"
#include "vm.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    mathine* vm = new mathine();

    expr* a = new add(new num(1), new num(2));
    expr* b = new mul(new num(2), new num(3));
    env*  e = new env();
    e->set("x", new num(0));

    expr* c = new lt(new var("x"), new num(3));
    expr* q = new add(new var("x"), new num(1));

    vm->run(new WHILE(c, new assign("x", q)), e);

    return 0;
}
