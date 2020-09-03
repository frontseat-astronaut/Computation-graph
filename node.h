#include<string>

#include<base.h>
using namespace std;

class node: public base
{
    protected:
        double value = 0;

    public:
        node(string key):base(key) {}
        node(double value, string key): value{value}, base(key) {}

        double get_value()
        {
            return value;
        }
};