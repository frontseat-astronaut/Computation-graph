#include<iostream>
#include<vector>

#include "node.h"
#include "operations.h"
#include "variables.h"
#include "op_api.h"
#include "var_api.h"

using namespace dio;

int main()
{
    Node a = IndependentVariable("a");
    assign(a, 2);
    Node b = Constant(6, "b");
    printf("a: %lf\n", value(a)); 
    printf("b: %lf\n", value(b)); 

    Node c = Add(Multiply(a, b), Reciprocal(a));
    printf("c: %lf\n", value(b)); 
    printf("c key (prefix notation!): %s\n", c->get_key().c_str()); 
    printf("del c / del a: %lf\n", gradient(c, "a")); 

}