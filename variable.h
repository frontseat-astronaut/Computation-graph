#include<string>
#include<operation.h>
using namespace std;

class variable
{
    protected:
        string key;
        double value = 0;
        bool is_valid = 0;

    public:
        variable(string key):key{key} {}

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
        int opargc;
        variable **opargv;
        operation op;
    
    public:
        dependent_variable(int opargc, variable **opargv, operation op, string key)
        :opargc{opargc}, opargv{opargv}, op{op}, variable(key) {}

        double get_value()
        {
            if(is_valid) return value;

            double tmpargval[opargc] = {};
            for(int i=0; i<opargc; ++i)
                tmpargval[i] = opargv[i]->get_value();

            value = op.run(tmpargval);
            is_valid = 1;
            return value;
        }
};