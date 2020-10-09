## Some piece of theory (DEPRECATED)
Let's setup the problem first.
Assume we have 
 - A set `X` of independent variables. The value of any of these variables is not dependent on any other variable.
 - A set `Y` of variables which are non-constant functions of some variables belonging to `X` or `Y`. The values of these variables depend on other variables. 

Let's treat all variables as nodes of a graph and add a directed edge from variable `u` to variable `v` if `v` is a function of `u` (`v` depends on `u`). 
For the gradient tape to work, I'll be assuming that the resultant graph is a **Directed Acyclic Graph**, meaning there is no cyclic dependency. 

Since it is a DAG, we can form an ordering (topological sorting) of the variables where for any two variables `u` and `v`, position of `u` is before the position of `v` if `v` depends on `u`. 
`v` doesn't have to be directly dependent on `u`, that is, `u` doesn't have to appear in the function expression of `v`. Instead, `v` can be dependent on some variable `x`, which is in turn dependent on `u`.
More generally speaking, for `v` to be dependent on `u` (directly or indirectly), there should exist at least one directed path from `u` to `v`. 

**The goal is to be able to find partial differential (gradient) of any variable `v` in `Y` with respect to any variable `u` in `X`.**
It is obvious that if `v` appears before `u` in the vertex ordering, this gradient would be zero.
Else, to find the gradients, we can use what is called the **Chain rule** for multivariable functions:
```
Say v = f(x1, x2, ... xn) is a function of variables x1, x2, ... xn.
For any variable u,
del v / del u = (del v / del x1)*(del x1 / del u) + (del v / del x2)*(del x2 / del u) + ... (del v / del xn)*(del xn / del u)  
```
Since we have the function expression of `f` that contains `xi`'s, we can directly find `(del v / del xi)`. 
Finding `(del xi / del u)` is the same problem as above (`xi` may not directly depend on `u`) except that `v` has now been replaced by `xi`. 

This urges us to look at the above chain rule equation as a **recursive equation**, where we're going from a variable of higher position in the ordering (`v`) to a variable of lower position (`xi`, because `v` depends on `xi`). 
Going backwards like this, we'll eventually always reach an **independent variable** `z`, which is our base case. Then, we can clearly see that: 
```
del z / del u = 1 if z == u else 0
```
That's it! We've solved the problem. 
Now performing recursion for every variable multiple times will be costly, which calls for using **dynamic programming** in the implementation.

Now, given that `xi` occurs in the function representation of `v`, how do we find `(del v / del xi)`?
The idea is to represent `v`'s function expression as a **composition of many differentiable functions**. 
For example, if `v = sin(e^{x}) + x^2`, then we can write `z = add(sin(exp(x)), pow(x, 2))`.
Now, to find gradient with respect to `x`, we can again apply chain rule!
```
dv/dx 
= d(add(sin(exp(x)), pow(x, 2)))/dx
= add(d(sin(exp(x)))/dx, d(pow(x, 2))/dx)
= add(cos(exp(x))*d(exp(x))/dx, 2*(x)*(dx/dx))
= add(cos(exp(x))*exp(x)*(dx/dx), 2*(x)*(1))
= add(cos(exp(x))*exp(x)*(1), 2*(x)*(1))
```

However, it seems a bit redundant to have to apply chain rule again here, as it is the same thing we did earlier when we were finding `del v / del u`. In fact, we can create a new variable for every function call in the composite function representation of any variable.
So for the above example, we can do the following:
```
v1 := pow(x, 2)
v2 := exp(x)
v3 := sin(v2)
v := add(v1, v3)
```
We can now modify our graph by including `v1`, `v2` and `v3`. This would ensure that any variable in the graph is a single elementary function of some other variables, and not a composition of functions.
