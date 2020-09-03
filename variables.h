#include<string>
#include<vector>

#include<operations.h>
#include<base.h>
#include<node.h>
using namespace std;

class constant: public node 
{
    public:
        constant(double value, string key): node(value, key) {}
};

class variable: public node 
{
    protected:
        bool is_valid = 0;

    public:
        variable(string key): node(key) {}


        void set_invalid()
        {
            is_valid = 0;
        }
};

class ind_variable: public variable 
{
    public:
        ind_variable(string key): variable(key) {}

        void set_value(double value)
        {
            ind_variable::value = value;
        }
};

class dep_variable: public variable
{
    protected:
        vector<variable*>opargv;
        operation *op;
    
    public:
        dep_variable(vector<variable*>opargv, operation *op, string key)
        :opargv{opargv}, op{op}, variable(key) {}

        double get_value()
        {
            if(is_valid) return value;

            vector<double>tmpargval(opargv.size());
            for(int i=0; i<opargv.size(); ++i)
                tmpargval[i] = opargv[i]->get_value();

            value = op->run(tmpargval);
            is_valid = 1;
            return value;
        }
};