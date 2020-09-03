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

    vector<node*>args;
    args.push_back(&a);
    args.push_back(&b);

    dep_variable c(args, &add_op, "c");

    args.pop_back();
    args.pop_back();
    args.push_back(&c);
    args.push_back(&b);
    dep_variable d(args, &add_op, "d");

    cout<<c.get_value()<<'\n';
    cout<<d.get_value()<<'\n';
}