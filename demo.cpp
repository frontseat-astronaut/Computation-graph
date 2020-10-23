#include<vector>
#include<stdio.h>
#include<iostream>
#include<random>

#include<dio.h>

using namespace dio;

void line()
{
    printf("\n");
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
    Node z = (0.5-x)^2; 

    for(int epoch=0; epoch<12; ++epoch)
    {
        printf("Epoch %d: z:", epoch);
        z.compute_val(); // re-computes value of z with new x
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
    // create random dataset
    int x_dim = 10;
    int num_samples = 1000;
    
    printf("dimension of x: %d, number of samples: %d\n\n", x_dim, num_samples);

    std::vector<std::vector<double>> data_x(num_samples, std::vector<double>(x_dim));
    std::vector<double> data_y(num_samples); 
    std::vector<double> true_params(x_dim);

    for(int i=0; i<x_dim; ++i) true_params[i] = gen_random_normal(0, 10);

    // x_i: random vector of length (#x_dim)
    // y_i =  dot(true_params_i, x_i) + random error
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
    Node x = Variable(data_x); // shape: (#num_samples, x_dim)
    Node y = Variable(data_y); // shape: (#num_samples)

    Node theta = Variable(std::vector<int>{x_dim, 1}, "normal");
    Node z = matmul(x, theta).reshape(std::vector<int>{num_samples}); // shape: (#num_samples)
    Node Loss = (0.5/num_samples)*(reduce_sum((z - y)^2, std::vector<int>{0})); // MSE

    // training (full batch gradient descent)
    double lr = 0.05;
    for(int epoch=0; epoch<30; epoch++)
    {
        Loss.compute_val();

        printf("Epoch %d Loss: ", epoch);
        Loss.print_val();
        printf("\n");

        theta.update_val(theta - lr*(Loss.grad(theta).index(0)));
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

void TwoLayerNeuralNetwork()
{
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
        }
        data_y[i] = rand()%2;
    }

    // build model
    // data 
    Node x = Variable(data_x); // shape: (#num_samples, x_dim)
    Node y = Variable(data_y); // shape: (#num_samples)

    // weights
    int m_hidden = 4;
    Node W_1 = Variable(std::vector<int>{x_dim, m_hidden}, "normal");
    Node W_2 = Variable(std::vector<int>{m_hidden, 1}, "normal");

    // latent variables
    Node z_1 = matmul(x, W_1); // shape: (#num_samples, m_hidden)
    Node a_1 = relu(z_1);
    Node z_2 = matmul(a_1, W_2); // shape: (#num_samples, 1)
    Node logits = sigmoid(z_2).reshape(std::vector<int>{num_samples});  // shape: (#num_samples)

    Node Loss_term = y*log(logits) + (1-y)*log(1-logits);
    Node Loss = (-1.0/num_samples)*(reduce_sum(Loss_term, std::vector<int>{0})); // Binary Cross-entropy

    // training (full batch gradient descent)
    double lr = 1;
    for(int epoch=0; epoch<1000; epoch++)
    {
        Loss.compute_val();

        if(epoch%10 == 0)
        {
            printf("Epoch %d Loss: ", epoch);
            Loss.print_val();
            printf("\n");
        }

        W_1.update_val(W_1- lr*(Loss.grad(W_1).index(0)));
        W_2.update_val(W_2 - lr*(Loss.grad(W_2).index(0)));
    }
}

int main()
{
    // OneVariableOptimization();
    // line();

    // LinearRegression();
    // line();

    TwoLayerNeuralNetwork();
    line();
}