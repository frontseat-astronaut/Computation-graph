#include "op_api.h"

namespace dio 
{
    std::map<std::string, operation*>op;

    Node Add(Node a, Node b, std::string key)
    {
        if(op.find("add") == op.end())
            op["add"] = new add;

        if(key == "")
            key = "add_" + a->get_key() + "_" + b->get_key();

        Node c = new dep_variable(std::vector<Node>{a, b}, op["add"], key);
        return c;
    }

    Node Multiply(Node a, Node b, std::string key)
    {
        if(op.find("multiply") == op.end())
            op["multiply"] = new multiply;

        if(key == "")
            key = "multiply_" + a->get_key() + "_" + b->get_key();

        Node c = new dep_variable(std::vector<Node>{a, b}, op["multiply"], key);
        return c;
    }

    Node Divide(Node a, Node b, std::string key)
    {
        if(op.find("divide") == op.end())
            op["divide"] = new divide;

        if(key == "")
            key = "divide" + a->get_key() + "_" + b->get_key();

        Node c = new dep_variable(std::vector<Node>{a, b}, op["divide"], key);
        return c;
    }

    Node Reciprocal(Node a, std::string key)
    {
        if(op.find("divide") == op.end())
            op["divide"] = new divide;
        
        if(key == "")
            key = "reciprocal_" + a->get_key();
        
        Node c = new dep_variable(std::vector<Node>{new constant(1, "one_"+key), a}, op["divide"], key);
        return c;
    }
}