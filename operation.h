#include<string>
#include<vector>
using namespace std;

class operation: public base
{
    protected:
        string op;

    public:
        operation(string key): base(key) {}
        
        string get_op_name() { return op;};

        virtual double run(vector<double>opargv) = 0;
};

class add: class operation
{
    public:
        add(string key): operation(key) {}

        double run(vector<double>opargv)
        {
            if(opargv.size() != 2)
                throw 'add op: 2 arguments expected';
            
            double result = openargv[0] + openargv[1];
            return result;
        }
}