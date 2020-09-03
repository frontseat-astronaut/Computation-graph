#include<iostream>
#include<vector>

#include "node.h"
#include "base.h"
#include "operations.h"
#include "variables.h"
using namespace std;

int main()
{
    ind_variable a("a");
    a.set_value(1);
    constant b(10, "b");

    add add_op("");
    multiply mult_op("");

    vector<node*>args;
    args.push_back(&a);
    args.push_back(&b);

    dep_variable c(args, &add_op, "c"); // c = a + b

    args.pop_back();
    args.pop_back();
    args.push_back(&c);
    args.push_back(&a);
    dep_variable d(args, &mult_op, "d"); // d = c*a = a^2 + b*a

    cout<<c.get_value()<<'\n';
    cout<<d.get_value()<<'\n';
    cout<<c.get_gradient(a.get_key())<<'\n';
    cout<<d.get_gradient(a.get_key())<<'\n';
}