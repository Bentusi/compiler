#include "expression.hpp"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    mathine* vm = new mathine();

    expr* a = new add(new num(1), new num(2));
    expr* b = new mul(new num(2), new num(3));
    expr* j = new mul(a, b);
    expr* k = new mul(b, j);
    vm->run(k);

    expr* l = new lt(j, k);
    vm->run(l);

    return 0;
}
