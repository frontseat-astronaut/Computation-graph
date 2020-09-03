#include<string>
#include<operation.h>
using namespace std;

class variable
{
    private:
        string key;
        double value = 0;
        long long update_time = -1;

    public:
        variable(string key):key{key} {}

        double get_value()
        {
            return value;
        }

        void set_value(int value, long long update_time)
        {
            variable::value = value;
            variable::update_time = update_time;
        }
};

class dependent_variable: public variable
{
    private:
        int opargc;
        variable **opargs;
        operation op;
    
    public:
        dependent_variable(int opargc, variable **opargs, operation op, string key)
        :opargc{opargc}, opargs{opargs}, op{op}, variable(key) {}

        double get_value(long long timestamp)
        {

};