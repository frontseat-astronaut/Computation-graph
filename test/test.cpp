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
    for(auto x: a->get_shape())
        std::cout<<x<<" ";
    std::cout<<'\n';
    for(auto x: b->get_shape())
        std::cout<<x<<" ";
    std::cout<<'\n';
    Node c = add(a, b);
    c->print();
}