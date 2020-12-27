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

int main(int argc, char** argv)
{
    int test_case;
    if(argc == 1)
        test_case = -1;
    else
        sscanf(argv[1], "%d", &test_case);
    
    if(test_case == -1 || test_case == 1)
    {
        line();

        // elementwise operations
        Node x = Variable(std::vector<std::vector<double>>{{100, 1}, {10, 1000}});
        Node y = Constant(std::vector<std::vector<double>>{{1, 2}, {3, 4}});
        Node z = x*2+y*3; // notice that precendence(*) > precedence(+)
        z.compute_val();
        z.print_val();
        printf("\n");
        printf("\n");
        Node w = 1/(y^2);
        w.compute_val();
        w.print_val();
        printf("\n");
        printf("\n");
        Node gradw = z.get_jacobian(x);
        gradw.compute_val();
        gradw.print_val();
        printf("\n");
        printf("\n");
    }


    if(test_case == -1 || test_case == 2)
    {
        line();

        // matmul
        Node a = Variable(std::vector<std::vector<double>>{{100, 1}, {10, 1000}});
        a.print_val();
        printf("\n");
        printf("\n");
        printf("\n");

        Node b = Variable(std::vector<std::vector<double>>{{1}, {3}});
        b.print_val();
        printf("\n");
        printf("\n");
        printf("\n");

        Node c = matmul(a, b);
        c.compute_val();
        c.print_val();
        printf("\n");
        printf("\n");
        printf("\n");

        Node gradcb = c.get_jacobian(b);
        gradcb.print_val();
        printf("\n");
        printf("\n");
        printf("\n");
        Node gradca = c.get_jacobian(a);
        gradca.print_val();
        printf("\n");
        printf("\n");
        printf("\n");
    }

    if(test_case == -1 || test_case == 3)
    {
        line();

        // concat
        Node d = Variable(std::vector<std::vector<double>>{{1, 2}, {3, 4}}); 
        d.print_val();
        printf("\n");
        printf("\n");
        Node e = Variable(std::vector<std::vector<double>>{{5, 6}});
        e.print_val();
        printf("\n");
        printf("\n");
        Node e_ = Variable(std::vector<std::vector<double>>{{5}, {6}});
        e_.print_val();
        printf("\n");
        printf("\n");

        Node f = concat(d, e);
        f.compute_val();
        f.print_val();
        printf("\n");
        printf("\n");

        Node f_ = concat(d, e_, 1);
        f_.compute_val();
        f_.print_val();
        printf("\n");
        printf("\n");

        Node gradf = f.get_jacobian(d);
        gradf.print_val();
        printf("\n");
        printf("\n");
    }

    if(test_case == -1 || test_case == 4)
    {
        line();

        // index
        Node a = Variable(std::vector<std::vector<double>>{{100, 1}, {10, 1000}});
        a.print_val();
        printf("\n");
        printf("\n");
        Node a01 = a.index(0, 1);
        a01.compute_val();
        a01.print_val();
        printf("\n");
        printf("\n");

        Node a_i = a.index(1, std::vector<int>{0, 1});
        a_i.compute_val();
        a_i.print_val();
        printf("\n");
        printf("\n");

        Node d = Variable(std::vector<std::vector<double>>{{1, 2}, {3, 4}}); 
        d.print_val();
        printf("\n");
        printf("\n");
        Node e = Variable(std::vector<std::vector<double>>{{5, 6}});
        e.print_val();
        printf("\n");
        printf("\n");
        Node e_ = Variable(std::vector<std::vector<double>>{{5}, {6}});
        e_.print_val();
        printf("\n");
        printf("\n");

        Node f = concat(d, e);
        f.compute_val();
        f.print_val();
        printf("\n");
        printf("\n");

        Node f_ = concat(d, e_, 1);
        f_.compute_val();
        f_.print_val();
        printf("\n");
        printf("\n");

        Node gradf = f.get_jacobian(d);
        gradf.print_val();
        printf("\n");
        printf("\n");

        Node gradf_i = gradf.index(0, 1);
        gradf_i.compute_val();
        gradf.print_val();
        printf("\n");
        printf("\n");
        gradf_i.print_val();
        printf("\n");
        printf("\n");

        Node arr = Variable(std::vector<double>{1, 2, 3, 4});
        arr.print_val();
        printf("\n");
        printf("\n");
        Node parr = arr.index(std::vector<int>{3, 1, 2, 0});
        parr.compute_val();
        parr.print_val();
        printf("\n");
        printf("\n");
    }

    if(test_case == -1 || test_case == 5)
    {
        line();

        // reshape
        Node z = Variable(std::vector<std::vector<double>>{{1, 2}, {3, 4}});
        z = reshape(z, std::vector<int>{4});
        z.compute_val();
        z.print_val();
        printf("\n");
        printf("\n");
        printf("\n");
    }

    if(test_case==-1 || test_case == 6)
    {
        line();

        //reduce sum 
        std::vector<std::vector<std::vector<double>>>arg{{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}}, {{6.0, 7.0, 8.0}, {9.0, 10.0, 11.0}}};
        Node a = Variable(arg);
        a.print_val();
        printf("\n");
        printf("\n");
        printf("\n");
        Node b = reduce_sum(a, std::vector<int>{2});
        b.print_val();
        printf("\n");
        printf("\n");
        printf("\n");
    }

    line();
    
}