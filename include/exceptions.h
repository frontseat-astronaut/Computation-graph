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

    class NotFlattened: public std::exception
    {
        const char * what () const throw ()
        {
            return "Expected a single dimensional double array";
        }
    };

    class NoGradForConstant: public std::exception
    {
        const char * what () const throw ()
        {
            return "Constant node has no gradient";
        }
    };

    class WrongArgCount: public std::exception
    {
        const char * what () const throw ()
        {
            // char ret[50];
            // sprintf(ret, "Expected number of arguments: %d instead of %d", correct_cnt, wrong_cnt);
            // return ret;
            return "Wrong number of arguments";
        }
    };

    class Expected2DMatrix: public std::exception
    {
        const char * what () const throw ()
        {
            return "Expected a 2D Matrix";
        }
    };
    
    class IncompatibleMatrices: public std::exception
    {
        const char * what () const throw ()
        {
            return "Shapes not compatible for matmul";
        }
    };
    
    class InvalidDimensionCount: public std::exception
    {
        const char * what () const throw ()
        {
            return "Got more dimensions in slice than the shape of object";
        }
    };
    
    class InvalidIndex: public std::exception
    {
        const char * what () const throw ()
        {
            return "ith index should be an int less than th
        }
    }
    
}

#endif