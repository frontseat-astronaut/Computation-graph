#include<iostream>
#include<vector>

#include "node.h"
#include "operations.h"
#include "variables.h"
#include "op_api.h"
#include "var_api.h"

using namespace std;

int main()
{
    Node a = IndependentVariable("a");
    Assign(a, 2);
    Node b = Constant(6, "b");
    printf("a: %lf\n", a->get_value()); 
    printf("b: %lf\n", b->get_value()); 

    Node c = Add(Multiply(a, b), Reciprocal(a));
    printf("c: %lf\n", c->get_value()); 
    printf("c key (prefix notation!): %s\n", c->get_key().c_str()); 
    printf("del c / del a: %lf\n", c->get_gradient("a")); 

}