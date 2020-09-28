#ifndef __EXCEPTION_H_INCLUDED__   
#define __EXCEPTION_H_INCLUDED__  

#include<exception>
#include<string>

namespace dio
{
    class NotAssignedError: public std::exception
    {
        const char * what () const throw ()
        {
            return "Dependent variable not assigned";
        }
    };

    class ArrayNotInitialized: public std::exception
    {
        const char * what () const throw ()
        {
            return "Array not initialized";
        }
    };

    class IndexOutofBounds: public std::exception
    {
        const char * what () const throw ()
        {
            return "Index out of bounds";
        }
    };

    class ShapeMismatch: public std::exception
    {
        const char * what () const throw ()
        {
            return "The shapes of arrays don't match";
        }
    };

    class NotAGrid: public std::exception
    {
        const char * what () const throw ()
        {
            return "The array provided is not a grid";
        }
    };

    class ShapeNotSpecified: public std::exception
    {
        const char * what () const throw ()
        {
            return "Shape required for allocation";
        }
    };
}

#endif