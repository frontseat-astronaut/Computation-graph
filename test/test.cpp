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
    // elementwise operations
    Node x = Variable(std::vector<std::vector<double>>{{100, 1}, {10, 1000}});
    Node y = Constant(std::vector<std::vector<double>>{{1, 2}, {3, 4}});
    Node z = x*2+y*3; // notice that precendence(*) > precedence(+)
    z.compute_val();
    z.print_val();
    Node w = 1/(y^2);
    w.compute_val();
    w.print_val();
    Node gradw = w.grad(x);
    gradw.compute_val();
    gradw.print_val();

    line();

    // matmul
    Node a = Variable(std::vector<std::vector<double>>{{100, 1}, {10, 1000}});
    a.print_val();
    printf("\n");

    Node b = Variable(std::vector<std::vector<double>>{{1}, {3}});
    b.print_val();
    printf("\n");

    Node c = matmul(a, b);
    c.compute_val();
    c.print_val();
    printf("\n");

    Node gradcb = c.grad(b);
    gradcb.print_val();
    printf("\n");
    Node gradca = c.grad(a);
    gradca.print_val();
    printf("\n");

    line();

    // concat
    Node d = Variable(std::vector<std::vector<double>>{{1, 2}, {3, 4}}); 
    d.print_val();
    Node e = Variable(std::vector<std::vector<double>>{{5, 6}});
    e.print_val();
    Node e_ = Variable(std::vector<std::vector<double>>{{5}, {6}});
    e_.print_val();

    Node f = concat(d, e);
    f.compute_val();
    f.print_val();

    Node f_ = concat(d, e_, 1);
    f_.compute_val();
    f_.print_val();

    Node gradf = f.grad(d);
    gradf.print_val();

    line();

    // index
    a.print_val();
    Node a01 = a.index(0, 1);
    a01.compute_val();
    a01.print_val();

    Node a_i = a.index(1, std::vector<int>{0, 1});
    a_i.compute_val();
    a_i.print_val();

    Node gradf_i = gradf.index(0, 1);
    gradf_i.compute_val();
    gradf.print_val();
    gradf_i.print_val();

    Node arr = Variable(std::vector<double>{1, 2, 3, 4});
    arr.print_val();
    Node parr = arr.index(std::vector<int>{3, 1, 2, 0});
    parr.compute_val();
    parr.print_val();

    line();

    // reshape
    z = Variable(std::vector<std::vector<double>>{{1, 2}, {3, 4}});
    z = reshape(z, std::vector<int>{4});
    z.compute_val();
    z.print_val();
    printf("\n");

    line();

    //reduce sum 
    std::vector<std::vector<std::vector<double>>>arg{{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}}, {{6.0, 7.0, 8.0}, {9.0, 10.0, 11.0}}};
    a = Variable(arg);
    a.print_val();
    printf("\n");
    b = reduce_sum(a, std::vector<int>{2});
    b.print_val();
    printf("\n");

    line();
    
}