# Stochastic simulation algorithms

Stochastic simulation algorithms for Gene Regulatory Networks for delayed and non-delayed reactions.

Avaiable methods:

 *
 
Methods in development:
 
 * Direct method
 * First reaction method
 * Next reaction method
 * Modified next reaction method
 * Rejection method
 * Delayed modified next reaction method

Requirements:

 * [libsbml 5.14](http://sbml.org/Software/libSBML)

Example of use:

```c++
SSA* dm = new DirectMethod();
dm->peform("filename");
```
