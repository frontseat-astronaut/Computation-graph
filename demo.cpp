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
        x.update_val(x - 0.3*z.get_jacobian(x).index(0)); // DO NOT do: x = x - 0.3*z.get_jacobian(x).index(0), as it creates a new node
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
    Node x = Constant(data_x); // shape: (#num_samples, x_dim)
    Node y = Constant(data_y); // shape: (#num_samples)

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

        theta.update_val(theta - lr*(Loss.get_jacobian(theta).index(0)));
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
            data_y[i] += j*data_x[i][j];
        }
        data_y[i] = (int)( ((1.0/(1+exp(-data_y[i]))) > 0.5)?1:0 );
        // data_y[i] = ((int)rand())%2; // Random labels
    }

    // build model
    // input
    Node x = Constant(data_x); // shape: (#num_samples, x_dim)
    Node y = Constant(data_y); // shape: (#num_samples)

    // Functors
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

    bool do_gradient_check = false;
    int gradient_check_start_epoch = 100;
    for(int epoch=0; epoch<300; epoch++)
    {
        Node a_1 = l1(x);
        Node a_2 = l2(a_1);
        a_2.reshape(std::vector<int>{num_samples});
        Node Loss_term = -(y * log(a_2 + 1e-6) + (1 - y) * log(1 - a_2 + 1e-6));
        // Node Loss_term = (a_2 - y)^2;
        Node Loss = (1.0/num_samples)*(reduce_sum(Loss_term, std::vector<int>{0})); // Binary Cross-entropy
        Loss.compute_val();

        if(epoch%10 == 0)
        {
            double Loss_val = Loss.val_at_index(std::vector<int>{0});
            printf("Epoch %d Loss: %lf\n", epoch, Loss_val);
        }

        // OBSERVATION: Gradient check fails for early epochs, but passes for later ones
        if(epoch == gradient_check_start_epoch) do_gradient_check = true; 
        optimize(Loss, opt, do_gradient_check, 1e-4); // implicitly calls Loss.compute_val() 
    }
}

void error(std::vector<std::string>&demos)
{
    printf("Please specify one of the following demos (option number) as argument:\n");
    for(int i=0; i<demos.size(); ++i)
        printf("%d: %s\n", i, demos[i].c_str());
    exit(1);
}

int main(int argc, char **argv)
{
    int demo_arg;
    std::vector<std::string>demos{
        "one_variable_optimization",
        "linear_regression",
        "two_layer_neural_network"
    };
    if(argc == 1)
        error(demos);
    else
        demo_arg = argv[1][0] - '0';

    if(demo_arg == 0) 
        OneVariableOptimization();

    else if(demo_arg == 1)
        LinearRegression();

    else if(demo_arg == 2)
        TwoLayerNeuralNetwork();
    
    else 
        error(demos);
}
