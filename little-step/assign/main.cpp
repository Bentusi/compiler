
#include <iostream>
#include "assign.hpp"
#include "env.hpp"
#include "vm.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    mathine* vm = new mathine();

    // expr* a = new add(new num(1), new num(2));
    // expr* b = new mul(new num(2), new num(3));
    // expr* j = new mul(a, b);
    // expr* k = new mul(b, j);
    // vm->run(k);

    // expr* l = new lt(a, k);
    // vm->run(l);
    env*  e = new env();
    // e->set("p", new num(2));
    // e->set("q", new num(3));
    
    expr* p = new var("p");
    expr* q = new var("q");
    expr* k = new mul(p, q);

    expr* m = new assign("x", k);
    vm->run(m, e);

    return 0;
}
