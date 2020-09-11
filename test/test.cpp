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
    Number a = IndependentVariable();
    assign(a, 2);
    Number b = Constant(6);
    printf("a: %lf\n", value(a)); 
    printf("b: %lf\n", value(b)); 

    // Number c = add(multiply(a, b), minus(reciprocal(a))); // c = a*b - 1/a
    Number c = exp(a); // c = e^a
    // Number c = DependentVariable("c"); // should throw NotAssignedError when value(c) is called
    printf("c: %lf\n", value(c)); 
    printf("del c / del a: %lf\n", gradient(c, a)); 

    line();

    Number zero = Constant(0);
    Number nan = reciprocal(zero);
    printf("nan: %lf\n", value(nan)); // should give inf
    printf("nan + a: %lf\n", value(add(nan, a))); 

    line();

    Array w = IndependentArray(std::vector<int>{2, 2, 2});
}