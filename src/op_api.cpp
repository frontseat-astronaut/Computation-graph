#include <op_api.h>

namespace dio 
{
    std::map<std::string, std::shared_ptr<operation>>op;

    Number add(Number a, Number b)
    {
        if(op.find("add") == op.end())
            op["add"] = std::shared_ptr<operation>(new _add);

        Number c = Number(new variable_number(std::vector<Number>{a, b}, op["add"]));
        return c;
    }

    Number multiply(Number a, Number b)
    {
        if(op.find("multiply") == op.end())
            op["multiply"] = std::shared_ptr<operation>(new _multiply);

        Number c = Number(new variable_number(std::vector<Number>{a, b}, op["multiply"]));
        return c;
    }

    Number divide(Number a, Number b)
    {
        if(op.find("divide") == op.end())
            op["divide"] = std::shared_ptr<operation>(new _divide);

        Number c = Number(new variable_number(std::vector<Number>{a, b}, op["divide"]));
        return c;
    }

    Number reciprocal(Number a)
    {
        return divide(Number(new constant_number(1)), a);
    }

    Number minus(Number a)
    {
        if(op.find("minus") == op.end())
            op["minus"] = std::shared_ptr<operation>(new _minus);

        Number c = Number(new variable_number(std::vector<Number>{a}, op["minus"]));
        return c;
    }

    Number powr(Number a, Number b)
    {
        if(op.find("powr") == op.end())
            op["powr"] = std::shared_ptr<operation>(new _power);

        Number c = Number(new variable_number(std::vector<Number>{a, b}, op["powr"]));
        return c;
    }

    Number exp(Number a)
    {
        return powr(Number(new constant_number(std::exp(1))), a); 
    }

}