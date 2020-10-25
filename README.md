# Computation Graph
Hello there! This is a computation graph library in C++ that supports automatic differentiation.
Currently, it can:
1. Construct directed acyclic computation graphs, where each node is a multi-dimensional array (akin to tensors in Tensorflow and Pytorch) and each directed edge is an operation on these nodes, like an element-wise arithmetic operation or matrix multiplication.
2. Find the Jacobian `Jab` for any node `a` w.r.t. another node `b`, using forward-mode auto-differentiation (reverse mode is currently [being implementated](https://github.com/frontseat-astronaut/Computation-graph/tree/reverse-mode-autodiff)).

Please find the usage guide in [doc/usage](https://github.com/frontseat-astronaut/Computation-graph/tree/master/doc/usage) and the framework overview in [doc/framework](https://github.com/frontseat-astronaut/Computation-graph/tree/master/doc/framework).
There is also a [demo.cpp](https://github.com/frontseat-astronaut/Computation-graph/blob/master/demo.cpp) with examples like implementing a basic neural network using the library.

### Reading
If you are unfamiliar with computation graphs or automatic differentiation, please refer to the following:
- [colah's blog](https://colah.github.io/posts/2015-08-Backprop/) explaining computational graphs and automatic differentiation.
- [Wikipedia](https://en.wikipedia.org/wiki/Automatic_differentiation) on automatic differentiation.
- [doc/theory.md](https://github.com/frontseat-astronaut/Computation-graph/tree/master/doc/theory.md) explaining computation graphs with multi-dimensional arrays.

### How to run
This library is written and tested in my local machine with GNU `g++ (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0`. 
To run this on your local machine:
1. Clone this repository to your local machine.
2. Run the following in a terminal to build the library:
    ```
    make -C /path/to/repo/ build
    ```
     A new directory `build/` should be created in the repository, that stores the `.o` object files. This step needs to be repeated only if you make changes to the library code. Otherwise, once is enough.
3. If you want to run `demo.cpp`, do:
    ```
    make -C /path/to/repo/ demo 
    ./path/to/repo/bin/demo
    ```
    `make demo` is for compilation and `./path/to/repo/bin/demo` is to run the executable in the newly created `bin/` directory. 
4. To run your own `a.cpp` using the library (make sure it has `#include <dio.h>`):
    ```
    g++ -g -I /path/to/repo/include -c -o a.o a.cpp
    g++ -g -I /path/to/repo/include -o a a.o /path/to/repo/build/*
    ./a
    ```
    `./a` is to run the executable. 