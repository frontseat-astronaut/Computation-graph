#include <Functor.h>

namespace dio
{
    // Functor
    void Functor::set_input_shape(std::vector<int>input_shape)
    {
        Functor::input_shape = input_shape;
        Functor::input_shape_set = true;
    }

    void Functor::find_parameters()
    {
        if(!Functor::input_shape_set)
            throw InputShapeNotSet();

        std::vector<int>input_shape = Functor::input_shape;
        for(int dim=0; dim<input_shape.size(); ++dim)
            if(input_shape[dim] == -1)
                input_shape[dim] = 1;

        Node dummy_input = Variable(input_shape, "zeros");
        find_parameters(dummy_input);
    }

    void Functor::find_parameters(Node input)
    {
        std::shared_ptr<node> output = call(input).get();

        std::map<long long, int>node_idx;
        std::vector<std::shared_ptr<node>>node_list;
        output->traverse_graph(node_idx, node_list);

        for(auto nodei: node_list)
            if(!nodei->check_constant() && !nodei->check_latent())
                Functor::parameters.push_back(Node(nodei));

        Functor::found_parameters = true;
    }

    void Functor::assert_input_shape(std::vector<int>input_shape)
    {
        if(!Functor::input_shape_set)
            throw InputShapeNotSet();

        // If a value of input_shape along a certain dimension is -1, it means don't care
        if(input_shape.size() != Functor::input_shape.size())
            throw InvalidInputShape();

        for(int dim=0; dim<input_shape.size(); ++dim)
            if(Functor::input_shape[dim] != -1 && input_shape[dim] != Functor::input_shape[dim])
                throw InvalidInputShape();
    }

    Node Functor::operator()(Node input)
    {
        assert_input_shape(input.get()->get_shape());
        if(Functor::store_parameters && !Functor::found_parameters)
        {
            find_parameters(input);
            if(Functor::find_parameters_every_call)
                Functor::found_parameters = false;
        }
        return call(input);
    }

    std::vector<Node> Functor::get_parameters()
    {
        if(!Functor::found_parameters)
            throw ParametersNotSet();
        return parameters;
    }

    // Linear
    Linear::Linear(int input_dim, int output_dim, std::string activation_function, std::string initializer, bool use_bias):
        input_dim{input_dim}, output_dim{output_dim}, activation_function{activation_function}, use_bias{use_bias}
    {
        Linear::W = Variable(std::vector<int>{input_dim, output_dim}, initializer);
        // TODO: Implement broadcasting
        if(use_bias)
            Linear::b = Variable(std::vector<int>{output_dim}, "zeros");

        Functor::set_input_shape(std::vector<int>{-1, input_dim});
        find_parameters();
    }

    Node Linear::call(Node input)
    {
        Node out = matmul(input, W);
        if(Linear::use_bias)
            out = out + b;
        if(Linear::activation_function == "relu")
            out = relu(out);
        else if(Linear::activation_function == "sigmoid")
            out = sigmoid(out);
        else if(Linear::activation_function != "")
            throw InvalidActivationFunction();
        return out;
    }

}