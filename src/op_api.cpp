#include <op_api.h>

namespace dio 
{
    std::map<std::string, std::shared_ptr<operation>>op;

    Number add(Number a, Number b, std::string key)
    {
        if(op.find("add") == op.end())
            op["add"] = std::shared_ptr<operation>(new _add);

        if(key == "")
            key = "add_" + a->get_key() + "_" + b->get_key();

        Number c = Number(new dep_variable(std::vector<Number>{a, b}, op["add"], key));
        return c;
    }

    Number multiply(Number a, Number b, std::string key)
    {
        if(op.find("multiply") == op.end())
            op["multiply"] = std::shared_ptr<operation>(new _multiply);

        if(key == "")
            key = "multiply_" + a->get_key() + "_" + b->get_key();

        Number c = Number(new dep_variable(std::vector<Number>{a, b}, op["multiply"], key));
        return c;
    }

    Number divide(Number a, Number b, std::string key)
    {
        if(op.find("divide") == op.end())
            op["divide"] = std::shared_ptr<operation>(new _divide);

        if(key == "")
            key = "divide_" + a->get_key() + "_" + b->get_key();

        Number c = Number(new dep_variable(std::vector<Number>{a, b}, op["divide"], key));
        return c;
    }

    Number reciprocal(Number a, std::string key)
    {
        return divide(Number(new constant(1)), a, key);
    }

    Number minus(Number a, std::string key)
    {
        if(op.find("minus") == op.end())
            op["minus"] = std::shared_ptr<operation>(new _minus);

        if(key == "")
            key = "minus_" + a->get_key();

        Number c = Number(new dep_variable(std::vector<Number>{a}, op["minus"], key));
        return c;
    }

    Number powr(Number a, Number b, std::string key)
    {
        if(op.find("powr") == op.end())
            op["powr"] = std::shared_ptr<operation>(new _power);

        if(key == "")
            key = "power_" + a->get_key() + "_" + b->get_key();

        Number c = Number(new dep_variable(std::vector<Number>{a, b}, op["powr"], key));
        return c;
    }

    Number exp(Number a, std::string key)
    {
        return powr(Number(new constant(std::exp(1), key = "e")), a, key); 
    }
}