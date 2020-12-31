#include<vector>
#include<stdio.h>
#include<iostream>

#include<dio.h>

using namespace dio;

std::default_random_engine generator;
double gen_random_normal(double mean=0, double var=1)
{
    std::normal_distribution<double> distribution(mean,sqrt(var));
    return distribution(generator);
}
void line()
{
    for(int i=0; i<50; ++i)
        printf("-");
    printf("\n");
}
Node pow2(Node x)
{
    return x^2;
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
        a.compute_val();
        a.print_val();
        printf("\n");
        printf("\n");
        printf("\n");
        Node b = reduce_sum(a, std::vector<int>{2});
        b.compute_val();
        b.print_val();
        printf("\n");
        printf("\n");
        printf("\n");
    }

    if(test_case==-1 || test_case == 7)
    {
        line();

        Node a = Variable(std::vector<double>{1.0, 2.0});
        Node b = a^2;
        b.compute_val();
        b.compute_val();
        b.compute_val();
        b.print_val();
        printf("\n");
    }

    if(test_case==-1 || test_case == 8)
    {
        line();

        /* Single hidden layer Layer Neural Network trained for a binary classification task */
        // create random dataset
        int x_dim = 5;
        int num_samples = 100;
        
        printf("dimension of x: %d, number of samples: %d\n\n", x_dim, num_samples);

        std::vector<std::vector<double>> data_x(num_samples, std::vector<double>(x_dim));
        std::vector<double> data_y(num_samples); 

        // x_i: random vector of length (#x_dim)
        // y_i =  0 or 1
        srand( (unsigned)time(NULL) );
        for(int i=0; i<num_samples; ++i)
        {
            for(int j=0; j<x_dim; ++j)
            {
                data_x[i][j] = gen_random_normal(0, 10);
                data_y[i] += j*data_x[i][j];
            }
            data_y[i] = (int)( ((1.0/(1+exp(-data_y[i]))) > 0.5)?1:0 );
            // data_y[i] = ((int)rand())%2; // Random labels
        }

        // build model
        // data 
        Node x = Constant(data_x); // shape: (#num_samples, x_dim)
        Node y = Constant(data_y); // shape: (#num_samples)

        // Functor
        Linear l1 = Linear(x_dim, 20, "relu", "normal", false);
        auto parameters1 = l1.get_parameters();
        Linear l2 = Linear(20, 1, "sigmoid", "normal", false);
        auto parameters2 = l2.get_parameters();
        auto parameters = parameters1;
        parameters.insert(parameters.end(), parameters2.begin(), parameters2.end());

        // training (full batch gradient descent)
        double lr = 0.01;
        double momentum = 0.1;
        Optimizer opt = SGD(parameters, lr, momentum);

        printf("learning rate: %lf\n", lr);
        printf("momentum: %lf\n", momentum);
        fflush(stdout);

        for(int epoch=0; epoch<300; epoch++)
        {
            Node a_1 = l1(x);
            Node a_2 = l2(a_1);
            a_2.reshape(std::vector<int>{num_samples});
            Node Loss_term = y*log(a_2) + (1-y)*log(1-a_2);
            Node Loss = (-1.0/num_samples)*(reduce_sum(Loss_term, std::vector<int>{0})); // Binary Cross-entropy
            optimize(Loss, opt); // implicitly calls Loss.compute_val() 
            if(epoch%10 == 0)
            {
                printf("Epoch %d Loss: ", epoch);
                Loss.print_val();
                printf("\n");
            }
        }
    }

    line();
    
}