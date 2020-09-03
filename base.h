#ifndef __BASE_H_INCLUDED__   
#define __BASE_H_INCLUDED__  

using namespace std;

class base
{
    protected:
        string key;
    
    public:
        base(string key): key{key} {}

        string get_key() { return key; };
};

#endif