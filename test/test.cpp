#include<vector>
#include<stdio.h>
#include<iostream>

#include<dio.h>

using namespace dio;

void line()
{
    for(int i=0; i<50; ++i)
        printf("-");
    printf("\n");
}

int main()
{
    Node a = Variable(std::vector<int>{2, 2}, "normal");
    print_val(a);

    Node b = Variable(std::vector<std::vector<double>>{{1, 2}, {3, 4}});
    print_val(b);

    Node c = add(b, exp(b));
    c->compute_value();
    print_val(c);

    Node gradca = grad(c, b);
    print_val(gradca);
}