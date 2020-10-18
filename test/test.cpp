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
    Node w = 1/x;
    w.compute_val();
    w.print_val();
    Node gradw = w.grad(x);
    gradw.compute_val();
    gradw.print_val();

    // matmul
    Node a = Variable(std::vector<std::vector<double>>{{100, 1}, {10, 1000}});
    a.print_val();

    Node b = Variable(std::vector<std::vector<double>>{{1, 2}, {3, 4}});
    b.print_val();

    Node c = matmul(a, b);
    c.compute_val();
    c.print_val();

    Node gradcb = c.grad(b);
    gradcb.print_val();
    Node gradca = c.grad(a);
    gradca.print_val();

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
    Node a01 = index(a, 0, 1);
    a01.compute_val();
    a01.print_val();

    Node a_i = index(a, 1, std::vector<int>{0, 1});
    a_i.compute_val();
    a_i.print_val();

    Node gradf_i = index(gradf, 0, 1);
    gradf_i.compute_val();
    gradf.print_val();
    gradf_i.print_val();

    Node arr = Variable(std::vector<double>{1, 2, 3, 4});
    arr.print_val();
    Node parr = index(arr, std::vector<int>{3, 1, 2, 0});
    parr.compute_val();
    parr.print_val();

    // re-assignment possible now
    z = Variable(std::vector<int>{1, 1}, "normal");
    z.print_val();
}