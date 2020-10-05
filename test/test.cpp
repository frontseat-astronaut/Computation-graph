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
    Node a = Variable(std::vector<std::vector<double>>{{100, 1}, {10, 1000}});
    print_val(a);

    Node b = Variable(std::vector<std::vector<double>>{{1, 2}, {3, 4}});
    print_val(b);

    Node c = matmul(a, b);
    compute_val(c);
    print_val(c);

    Node gradcb = grad(c, b);
    print_val(gradcb);
    Node gradca = grad(c, a);
    print_val(gradca);
}