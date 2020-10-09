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
    // matmul
    Node a = Variable(std::vector<std::vector<double>>{{100, 1}, {10, 1000}});
    print_val(a);

    Node b = Variable(std::vector<std::vector<double>>{{1, 2}, {3, 4}});
    print_val(b);

    Node c = matmul(a, b);
    compute_val(c);
    print_val(c);

    Node gradcb = grad(c, b);
    print_val(gradcb);
    Node gradca = grad(c, a);
    print_val(gradca);

    line();

    // concat
    Node d = Variable(std::vector<std::vector<double>>{{1, 2}, {3, 4}}); 
    print_val(d);
    Node e = Variable(std::vector<std::vector<double>>{{5, 6}});
    print_val(e);
    Node e_ = Variable(std::vector<std::vector<double>>{{5}, {6}});
    print_val(e_);

    Node f = concat(d, e);
    compute_val(f);
    print_val(f);

    Node f_ = concat(d, e_, 1);
    compute_val(f_);
    print_val(f_);

    Node gradf = grad(f, d);
    print_val(gradf);

    line();

    // index
    print_val(a);
    Node a01 = index(a, 0, 1);
    compute_val(a01);
    print_val(a01);

    Node a_i = index(a, 1, std::vector<int>{0, 1});
    compute_val(a_i);
    print_val(a_i);

    Node gradf_i = index(gradf, 0, std::vector<int>{1});
    compute_val(gradf_i);
    print_val(gradf);
    print_val(gradf_i);
}