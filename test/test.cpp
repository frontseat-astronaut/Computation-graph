#include<vector>
#include<stdio.h>

#include<dio.h>

using namespace dio;

int main()
{
    Node a = IndependentVariable("a");
    assign(a, 2);
    Node b = Constant(6, "b");
    printf("a: %lf\n", value(a)); 
    printf("b: %lf\n", value(b)); 

    // Node c = add(multiply(a, b), minus(reciprocal(a))); // c = a*b - 1/a
    // Node c = exp(a); // c = e^a
    Node c = DependentVariable("c"); // should throw NotAssignedError when value(c) is called
    printf("c: %lf\n", value(c)); 
    printf("c key (prefix notation!): %s\n", key(c).c_str()); 
    printf("del c / del a: %lf\n", gradient(c, a)); 

}