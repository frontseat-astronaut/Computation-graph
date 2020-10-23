#include<vector>
#include<stdio.h>
#include<iostream>
#include<random>

#include<dio.h>

using namespace dio;

void line()
{
    for(int i=0; i<50; ++i)
        printf("-");
    printf("\n");
}

std::default_random_engine generator;
double gen_random_normal(double mean=0, double var=1)
{
    std::normal_distribution<double> distribution(mean,sqrt(var));
    return distribution(generator);
}

void OneVariableOptimization()
{
    /* Simple example involving optimization of a one variable function */
    Node x = Variable(5.00);
    // Node z = -((0.5-x)^2); // precendence(^) < precedence(-)
    Node z = (0.5-x)^2; 

    for(int epoch=0; epoch<12; ++epoch)
    {
        printf("Epoch %d: z:", epoch);
        z.compute_val(); // re-calculates value of z
        z.print_val();
        printf(" x: ");
        x.print_val();
        printf(" new x: ");
        x.update_val(x - 0.3*z.grad(x).index(0)); // DO NOT do: x = x - 0.3*z.grad(x).index(0), as it creates a new node
        x.print_val();
        printf("\n");
    }
}

void LinearRegression()
{
    /* Linear Regression */
    // dataset
    int x_dim = 10;
    int num_samples = 1000;
    
    printf("dimension of x: %d, number of samples: %d\n\n", x_dim, num_samples);

    std::vector<std::vector<double>> data_x(num_samples, std::vector<double>(x_dim));
    std::vector<double> data_y(num_samples);
    std::vector<double> true_params(x_dim);
    for(int i=0; i<x_dim; ++i) true_params[i] = gen_random_normal(0, 10);

    for(int i=0; i<num_samples; ++i)
    {
        for(int j=0; j<x_dim; ++j)
        {
            data_x[i][j] = gen_random_normal(0, 10);
            data_y[i] += data_x[i][j]*true_params[j];
        }
        data_y[i] += gen_random_normal(); // random noise
    }

    // build model
    Node theta = Variable(std::vector<int>{x_dim, 1}, "normal");
    double lr = 0.05;
    Node xi = Variable(data_x); // shape: (#num_samples, x_dim)
    Node yi = Variable(data_y); // shape: (#num_samples)

    // training
    for(int epoch=0; epoch<30; epoch++)
    {
        Node z = matmul(xi, theta).reshape(std::vector<int>{num_samples}); // shape: (#num_samples)
        Node Loss = (0.5/num_samples)*(reduce_sum((z - yi)^2, std::vector<int>{0}));
        Loss.compute_val();

        printf("Epoch %d Loss: ", epoch);
        Loss.print_val();
        printf("\n");

        Node new_theta = theta - lr*(Loss.grad(theta).index(0));
        new_theta.compute_val();
        theta.update_val(new_theta);
    }

    // predicted parameters
    printf("\n\npredicted params: ");
    theta.reshape(std::vector<int>{x_dim}).print_val();
    printf("\n");
    printf("true params: [");
    for(double thetai: true_params)
        printf("%lf ", thetai);
    printf("]\n");
}

int main()
{
    OneVariableOptimization();
    line();

    LinearRegression();
    line();


}