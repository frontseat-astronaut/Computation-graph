#include<string>
#include<vector>

#include<operations.h>
#include<base.h>
using namespace std;

class variable: public base
{
    protected:
        double value = 0;
        bool is_valid = 0;

    public:
        variable(string key):base(key) {}

        double get_value()
        {
            return value;
        }

        void set_value(int value)
        {
            variable::value = value;
            is_valid = 1;
        }

        void set_invalid()
        {
            is_valid = 0;
        }
};

class dependent_variable: public variable
{
    protected:
        vector<variable*>opargv;
        operation *op;
    
    public:
        dependent_variable(vector<variable*>opargv, operation *op, string key)
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