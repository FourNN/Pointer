#include <iostream>
#include "UniquePtr.hpp"

struct man
{
    int a;
    int b;
    int c;
    man():a(0),b(0),c(0){}
    man(int a, int b, int c):a(a),b(b),c(c){}
};

int main(int argc, char* argv[])
{
    auto m=makeUnique<man>(10,100,1000);
    std::cout <<m->a<<" "<<m->b<<" "<<m->c<<'\n';
    return 0;
}
