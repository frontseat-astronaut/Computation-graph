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
    for(int i=0; i<2; ++i)
    {
        for(int j=0; j<2; ++j)
        {
            printf("%lf ", a->get_value(std::vector<int>{i, j}));
        }
        printf("\n");
    }
    Node b = Variable(std::vector<std::vector<double>>{{1, 2}, {3, 4}});
}