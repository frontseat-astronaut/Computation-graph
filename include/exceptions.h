#include<exception>

class NotAssignedError: public std::exception
{
	const char * what () const throw ()
    {
    	return "Dependent variable not assigned";
    }
};