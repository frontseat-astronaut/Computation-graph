# Framework guide
`include/` folder contains header files, while `src/` contains corresponding cpp files for the headers.
I'd suggest to first go over headers, and then to cpp for implementations.

As with any project, there's a partial order of dependencies between files here. One valid ordering is:
1. `array`
2. `variable`
3. `number_op`
4. `array_op`
5. `var_api`
6. `op_api`
7. `dio` (the main library header file!)

And finally... 

8. `test.cpp`