# Usage guide
Please refer to [README](https://github.com/frontseat-astronaut/Computation-graph/blob/master/README.md) for instructions on how to run the library. 

## Contents
- [Header file and namespace](#Header-file-and-namespace)
- [Nodes, Variables and Constants](#Nodes,-Variables-and-Constants)
- [Operators](#Operators)
    - [Member function operators](##Member-function-operators)
    - [Non-member function operators](#2.-Non/-Member-function-operators) 
    - [Overloaded operators](#3.-overloaded-operators) 
- [Updating Values](#Updating-values)
- [Jacobian](#Jacobian)

## Header file and namespace
To use the library in your `.cpp` file, you only need to include one header file:
```
#include <dio.h>
```
The whole library is under the namespace `dio`, so you need to either have `use namespace dio` at the start, or use the scope operator `dio::` with every function call or class from the library.
In this doc, we'll be using the latter.

## Nodes, Variables and Constants
Computation graph consists of nodes, which are multi-dimensional arrays.
Any node is either a "variable" or a "constant". A constant is a node whose value cannot be changed at run-time, while the value of variable can. 

To create a node, we need to create an instance of the `Node` class. For example:
```
dio::Node a = dio::Variable(std::vector<double>{1.0, 2.0})
```
creates a variable of shape `(2,)` and having the value `[1.0, 2.0]`. 

To print the value of a node to STDOUT, use
```
a.print_val();
```

There are multiple ways to create a `Variable`. 
Here are the function prototypes for the same:

- To create a variable with a given shape, initialization (check [include/initalizers.h](https://github.com/frontseat-astronaut/Computation-graph/blob/master/include/initializers.h) to check the initializers available) and the list arguments to initializer (like mean and variable for normal initializer):
    ```
    dio::Node dio::Variable(std::vector<int>shape, std::string initializer, 
                            std::vector<double>init_args=std::vector<double>{});
    ```
    Value of `initializer` should be either one of the following:

    + `'normal'` or `'gaussian'`: Initializes all elements of the array independently with a normal distribution of given mean `init_args[0]` and variance `init_args[1]`.
    + `'zeros'`: Initializes all elements of the array with `0.0`.

- To create a variable, which is initialized as having the same shape and value as a grid-like multi-dimensional `std::vector` with elements of type `double` or a single element `double` value:

    ```
    dio::Node dio::Variable({vector or double variable});
    ```
    For example:
    ```
    dio::Node a = dio::Variable(5.0)
    ```

`Constant` objects only be created by the second way given above:
```
dio::Node = dio::Constant(std::vector<std::vector<double>>{{1.0, 2.0}, {3.0, 4.0}});
```
which creates a constant array `[[1, 2], [3, 4]]` of shape `(2, 2)`.

Note that the following will throw an error, because the vector is not a grid:
```
dio::Node a = dio::Variable(std::vector<std::vector<double>>{{1.0, 2.0}, {3.0}});
```

## Operators
Operators are the edges in our computation graph, which can be viewed as functions that act on multiple `Node` objects and produce a new `Node` (of type variable, not constant). 

For example:
```
dio::Node a = dio::Constant(std::vector<double>{1.0, 2.0});
dio::Node b = dio::Variable(std::vector<double>{3.0, 4.0});
dio::Node c = a + b;
c.print_val();
```
outputs `[4.0, 6.0]`. Here, `+` is an operator, namely the element-wise addition operator.

There are three kinds of operators currently in the library:
1. Operators which are member methods of the `Node` class
2. Operators which are non-member functions, taking `Node` objects as arguments
3. Operators which are overloaded C++ operators (like `+` above)

Let's take a look into each of them:

### 1. Member function operators
Currently we only have one member function operator, which is the `index` operator. 

This operator acts on a single `Node` object and is used to index its array. 
For example, 
```
dio::Node a = dio::Variable(std::vector<double>{1.0, 2.0});
dio::Node a_0 = a.index(0);
a_0.print_val();
```
outputs `[1.0]`. 

The indexing rules here are very similar to that with lists in Python.
You can index across multiple axes and use multiple indices for a particular axis.

This can best be explained using examples:
```
dio::Node a = dio::Variable(std::vector<std::vector<double>>{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}});
a.print_val();
```
should output the value of `a`: `[[1.0, 2.0, 3.0], [4.0, 5.0, 6.0]]`.

Let's try the `index` operator:
```
a.index(1, 2).print_val()
```
should output `[6.0]`. 
Here we pick the second index from the first axis and third index from the second axis.

Moreover,
```
a.index(0, std::vector<int>{0, 2}).print_val();
```
should output `[1.0, 3.0]`. 
Here, we pick the first index from the first axis and the first and third indices from the second axis.

Also, you needn't specify indices for all axes:
```
a.index(0).print_val();
```
should output `[4.0, 5.0, 6.0]`, and:
```
a.index(-1, 1).print_val();
```
should output `[2.0, 5.0]`, whose shape is `(2)`. 
Here, `-1` means taking all indices in the particular axis. **Note**: This is unlike in Python, where it means taking the last element.

Note that if we modify the above in the following manner:
```
a.index(-1, std::vector<int>{1}).print_val();
```
This should output `[[2.0], [5.0]]` whose shape is `(2, 1)`. 
In general, if you specify an integer index along an axis (except `-1`), that axis is removed from the result. Using `vector` index keeps that axis, even if we only pick one index from that axis.

We can also change the ordering of the indices along an axis:
```
a.index(0, std::vector<int>{2, 1, 0}).print_val();
```
should output `[3.0, 2.0, 1.0]`.

Note that `index` is an operator, so every time it is called, it creates and returns a new `Node` object as the result.

### 2. Non-member function operators
These are functions that take multiple `Node` objects as arguments and return a single `Node` object as result.
Let's take a look at the currently available operators:
- `concat`: This operator is used to concatenate two `Node` objects along a single axis (by default, it's `axis=0`). 
The function prototype looks like the following:
    ```
    dio::Node dio::concat(dio::Node a, dio::Node b, int axis=0);
    ```
    Let's see an example:
    ```
    dio::Node d = dio::Variable(std::vector<std::vector<double>>{{1, 2}, {3, 4}}); 
    d.print_val();
    printf("\n");

    dio::Node e = dio::Variable(std::vector<std::vector<double>>{{5, 6}});
    e.print_val();
    printf("\n");
    
    dio::Node e_ = dio::Variable(std::vector<std::vector<double>>{{5}, {6}});
    e_.print_val();
    printf("\n");
    ```
    should output 3 arrays: `[[1.0, 2.0], [3.0, 4.0]]`, `[[5.0, 6.0]]` and `[[5.0], [6.0]]`.
    
    Let's try the `concat` operator:
    ```
    dio::concat(d, e).print_val();
    ```
    This should output `[[1.0, 2.0], [3.0, 4.0], [5.0, 6.0]]`.

    Alternatively:
    ```
    dio::concat(d, e_, 1).print_val();
    ```
    should output `[[1.0, 2.0, 5.0], [3.0, 4.0, 6.0]]`. 

- `reshape`: This operator acts on a single `Node` object and produces a new `Node` object with the same elements, but in a different shape.

    The function prototype looks like the following:
    ```
    dio::Node dio::reshape(dio::Node a, std::vector<int>new_shape);
    ```

    For example, consider the array:
    ```
    dio::Node a = dio::Variable(std::vector<std::vector<double>>{{1.0, 2.0}, {3.0, 4.0}});
    a.print_val();
    ```
    which outputs `[[1.0, 2.0], [3.0, 4.0]]`.
    Using the `reshape` operator:
    ```
    dio::reshape(a, std::vector<int>{4}).print_val();
    ```
    outputs `[1.0, 2.0, 3.0, 4.0]`.

    **Note:** that there is also an in-place reshape member function available in the `Node` class, which does not create a new `Node` object, but instead changes the shape of the existing object. 
    For example:
    ```
    a.reshape(std::vector<int>{4});
    a.print_val();
    ```
    which changes shape of `a` from `(2, 2)` to `(4)`.

- `matmul`: This operator takes in two 2-dimensional `Node` objects and returns their matrix multiplication.
    For example,
    ```
    dio::Node a = dio::Variable(std::vector<std::vector<double>>{{100, 1}, {10, 1000}});
    a.print_val();
    printf("\n");

    dio::Node b = dio::Variable(std::vector<std::vector<double>>{{1}, {3}});
    b.print_val();
    printf("\n");
    ```
    outputs two arrays `[[100.0, 1.0], [10.0, 1000.0]]` and `[[1.0], [3.0]]`.

    Using `matmul`:
    ```
    dio::matmul(a, b).print_val();
    ```
    outputs their matrix multiplication `[[103.0], [3010.0]]`.

- `reduce_sum`: This operator is used to reduce a `Node` object along multiple given axes, by taking sum of elements. The function prototype is:
    ```
    dio::Node dio::reduce_sum(dio::Node a, std::vector<int>axes);
    ```

    Let's take an example:
    ```
    std::vector<std::vector<std::vector<double>>>arg{{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}}, {{6.0, 7.0, 8.0}, {9.0, 10.0, 11.0}}};
    a = dio::Variable(arg);
    a.print_val();
    ```
    which outputs
    ```
    [
        [
            [1.000000, 2.000000, 3.000000],
            [4.000000, 5.000000, 6.000000]
        ],
        [
            [6.000000, 7.000000, 8.000000],
            [9.000000, 10.000000, 11.000000]
        ]
    ]
    ```
    of shape `(2, 2, 3)`.

    Now, let's try:
    ```
    dio::Node c = dio::reduce_sum(a, std::vector<int>{0});
    c.print_val();
    ```    
    This will output `[[7.000000, 9.000000, 11.000000], [13.000000, 15.000000, 17.000000]]` of shape `(2, 3)`, by reducing along and eliminating the first axis.

    Let's try some other axis:
    ```
    c = dio::reduce_sum(a, std::vector<int>{2});
    c.print_val();
    ```
    This will output `[[6.000000, 15.000000], [21.000000, 30.000000]]` of shape `(2, 2)`, by reducing along and eliminating the third axis.

    Trying multiple axes:
    ```
    c = dio::reduce_sum(a, std::vector<int>{0, 1, 2});
    c.print_val();
    ```
    This will output `[72.0]`, of shape `(1)`. This is just the sum of all elements of the array.

You can check rest of the operators in [include/op_api.h](https://github.com/frontseat-astronaut/Computation-graph/blob/master/include/op_api.h), which are mostly just element-wise operators like `exp`, `relu` and `sigmoid`.

### 3. Overloaded operators
These consist of the element-wise arithmetic operators addition `+`, subtraction `-`, division `/`, multipication `*` and power `^`. Their precedence is as follows:
```
`*` and `/` > `+` and `-` > `^`
```
These operators can be used with two `Node` objects like:
```
dio::Node a = dio::Variable(std::vector<double>{1.0, 2.0});
dio::Node b = dio::Constant(std::vector<double>{3.0, 4.0});
(a ^ b).print_val();
```
which outputs `[1.0, 16.0]`.

Moreover, these can also be used with a `Node` object and a `double` variable:
```
dio::Node a = dio::Variable(std::vector<double>{1.0, 2.0});
(a+2).print_val();
```
which outputs `[3.0, 4.0]`.

## Updating values
You might have noticed that there are two kinds of ways to create `Node` objects:

- By explicitly calling the `Variable` or `Constant` functions.
- By using an operator on existing `Node` objects, that creates a new `Node` object (of type variable).

Variables that are created using the second method are called "**latent**" variables, which means that their value depends entirely on the values of other nodes.
The variables created by the first method can be called "**observed**" variables.

To change the value of an observed variable during run-time, call the `update_val()` method of the `Node` class:
```
dio::Node a = dio::Variable(5.0);
printf("Old value: ");
a.print_val();
printf("\n");

a.update_val(a - 5);
printf("New value: ");
a.print_val();
```
Output should be:
```
Old value: [5.0]
New value: [0.0]
```
Note that update_val takes a `Node` object as argument.

Also, calling `update_val()` with contants and latent variables will lead to an error.

The value of latent variables is dependent solely on the value of its operator arguments. 
At the time of creation of a latent variable, its value is calculated using the current values of the argument `Node` objects. 
**But this value is not updated when the argument values change**.
This can lead to stale values of latent variables and re-computation of value is necessary.

For example:
```
dio::Node a = dio::Variable(5.0);
dio::Node b = dio::Variable(6.0);
dio::Node c = a + b;
c.print_value();
```
outputs `[11.0]`.

But after changing the value of `a`:
```
a.update_val(a-2.0);
c.print_val();
```
The value of c is not changed.

To re-compute the value of a latent variable, you should call the member function `compute_val()`:
```
c.compute_val();
c.print_val();
```
This should output `[9.0]` now.

Notice the perks of having a directed graph structure: 
```
dio::Node a = dio::Variable(5.0);
dio::Node b = dio::Variable(6.0);
dio::Node c = a + b;
dio::Node d = 2*c;
c.print_value();
d.print_value();
```
This should output `[11.0]` and `[22.0]`.

Now if we update the value of `a`:
```
a.update_value(dio::Constant(1.0)); // changes value of a to [1.0]

c.print_val();
d.print_val();
```
As expected, the values of `c` and `d` should remain the same.

Now, let's compute value of `d`:
```
d.compute_val();

c.print_val();
d.print_val();
```
The output should be `[7.0]` and `[14.0]`.
Note that even we called `compute_val` only on `d`, the value of `c` was updated as well.
This is because `compute_val` is called recursively on all the nodes that `d` is directly or indirectly dependent on (`c` being one of them), and the base case of recursion are constants or observed variables.

A pseudocode for `compute_val` is:
```
compute_val(var):
    if var is constant:
        pass
    else:
        if islatent(var):
            for arg in argument_list:
                compute_val(arg)
            value := operator(argument_values)
        else:
            pass
```

## Jacobian
Jacobian of a latent `Node` variable `a` with respect to another `Node` object `b` is a constant `Node` object of shape `(a.shape, b.shape)`, with pair-wise first order partial derivatives as elements. 
One can see it as a sort of generalization of the [Jacobian matrix](https://en.wikipedia.org/wiki/Jacobian_matrix_and_determinant) for a vector valued function to multi-dimensional tensors.

Let's take an example:
```
dio::Node a = dio::Variable(std::vector<double>{1.0, 2.0});
dio::Node b = dio::Variable(std::vector<double>{3.0, 4.0});
dio::Node c = a + b;
```
`c` is a `Node` of shape `(2)`.

To get the Jacobian of `c` with respect to `a`:
```
dio::Node Jca = c.grad(a);
Jca.print_val();
```
This should give the output `[[1.000000, 0.000000], [0.000000, 1.000000]]` of shape `(2, 2)`.

To understand what it means, see the below description for each element of `Jca`:
```
Jca =
[
    [(del c0 / del a0), (del c0 / del a1)],
    [(del c1 / del a0), (del c1 / del a1)]
],
where c = [c0, c1], a = [a0, a1] and b = [b0, b1]

c0 = a0 + b0, which implies
    (del c0 / del a0) = 1
    (del c0 / del a1) = 0

c1 = a1 + b1, which implies
    (del c0 / del a0) = 0
    (del c1 / del a1) = 1
```
Each element is a partial derivative of some element of `c` with some other element of `a`. In fact for this case, it's exactly the Jacobian matrix.

Let's take a more complex example:
```
Node a = Variable(std::vector<std::vector<double>>{{100, 1}, {10, 1000}});
Node b = Variable(std::vector<std::vector<double>>{{1}, {3}});

Node c = matmul(a, b);

Node Jcb= c.grad(b);
Jcb.print_val();
printf("\n");
```
The output should be as follows:
```
[
 [
  [
   [100.000000],
   [1.000000]
  ]
 ],
 [
  [
   [10.000000],
   [1000.000000]
  ]
 ]
]
```
which is a `Node` of shape `(2, 1, 2, 1)` and defined as follows:
```
Jdb = 
[
 [
  [
   [(del c00 / del b00)],
   [(del c00 / del b10)]
  ]
 ],
 [
  [
   [(del c10 / del b00)],
   [(del c10 / del b10)]
  ]
 ]
], 
where c = [[c00], [c10]], a = [[a00, a01], [a10, a11]] and b = [[b00], [b10]]

c00 = a00*b00 + a01*b10, which implies
    (del c00/ del b00) = a00
    (del c00/ del b10) = a01

c10 = a10*b00 + a11*b10, which implies
    (del c10/ del b00) = a10
    (del c10/ del b10) = a11
```

It is recommended that you play around with differently shaped arguments and different operators to see how the Jacobian looks. 

Note that the `grad` function returns a **constant** `Node` object. 


