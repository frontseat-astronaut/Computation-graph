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
    Number a = Variable(2);
    Number b = Constant(6);
    printf("a: %lf\n", value(a)); 
    printf("b: %lf\n", value(b)); 

    Number c = add(multiply(a, b), minus(reciprocal(a))); // c = a*b - 1/a
    // Number c = exp(a); // c = e^a
    printf("c: %lf\n", value(c)); 
    printf("del c / del a: %lf\n", gradient(c, a)); 

    line();

    Number zero = Constant(0);
    Number nan = reciprocal(zero);
    printf("nan: %lf\n", value(nan)); // should give inf
    printf("nan + a: %lf\n", value(add(nan, a))); 

    line();

    constant d(std::vector<std::vector<double>>{{2, 3}, {1, 4}});
    printf("%lf\n", d.get_value(std::vector<int>{1, 1}));

    variable t(std::vector<int>{3, 2}, "normal"); 
    for(int i=0; i<3; ++i)
    {
        for(int j=0; j<2; ++j)
            printf("%lf ", t.get_value(std::vector<int>{i, j}));
        printf("\n");
    }
}