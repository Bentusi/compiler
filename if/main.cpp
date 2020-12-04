
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
    expr* l = new lt(a, b);
    env*  e = new env();
    // e->set("p", new num(2));
    // e->set("q", new num(3));
    
    expr* p = new var("p");
    expr* q = new var("q");

    expr* m = new assign("x", a);
    expr* n = new assign("x", b);
    expr* k = new IF(l, m, n);
    vm->run(k, e);

    return 0;
}
