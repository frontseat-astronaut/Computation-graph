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
    a->print();

    Node b = Variable(std::vector<std::vector<double>>{{1, 2}, {3, 4}});
    b->print();

    Node c = add(b, exp(b));
    c->compute_value();
    c->print();

    auto grad_c = c->forward_diff(b);
    for(int i=0; i<4; ++i)
        std::cout<<grad_c[i][i]<<" ";
    std::cout<<'\n';
}