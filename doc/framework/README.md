# Framework guide
`include/` folder contains header files, while `src/` contains corresponding cpp files for the headers.
I'd suggest to first go over headers, and then to cpp for implementations.

As with any project, there's a partial order of dependencies between files here. One valid ordering is:
1. `array`: a single node in the computation graph, is a multidimensional array
2. `variable`: inherit array class, two classes: constant and variable
3. `number_op`: operators defined on numbers, not on arrays
4. `array_op`: operators acting on arrays
5. `var_api`: api for variables
6. `op_api`: api for array operators
7. `dio`: the main library header file!

And finally... 

8. `test.cpp`: do stuff here to test framework