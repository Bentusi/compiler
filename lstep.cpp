#include "lstep.hpp"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    puts("main");
    mathine* mat = new mathine();

    type* a = new add(new num(1), new num(2));
    type* m = new mul(new num(2), new num(3));
    type* j = new mul(a, m);
    type* k = new mul(m, j);
    mat->run(k);
    
    return 0;
}
