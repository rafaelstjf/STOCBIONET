# Stochastic simulation algorithms

[![Open Source Love](https://badges.frapsoft.com/os/v2/open-source.svg?v=103)](https://github.com/ellerbrock/open-source-badges/) [![GPL Licence](https://badges.frapsoft.com/os/gpl/gpl.svg?v=103)](https://opensource.org/licenses/GPL-3.0/) 


Stochastic simulation algorithms for Gene Regulatory Networks for delayed and non-delayed reactions.

## Avaiable methods:

 * Direct method
 * Sorting direct method
 * First reaction method
 * Next reaction method
 * Modified next reaction method
 * Simplified next reaction method
 * Rejection method
 
## Methods in development:
 
 * Optimized direct method (__99.9%__)
 * Rejection method using Hash Tables (__99.9%__)
 * Next reaction method compact (__0.0%__)

## Requirements:

 * C++11
 * CMake 3.1 or newer (only if you want to build it using CMake)

## Building
* Linux
    ```sh
    mkdir build
    cd build
    cmake ..
    make
    ```
* Windows (using MinGW)
    ```cmd
    mkdir build
    cd build
    cmake .. -G "MinGW Makefiles"
    mingw32-make
    ```
## Example of use:

If you are using it in the terminal you can run it without arguments or with the following arguments: Input-file Operation-code Initial-time Maximum-time

The current operation's codes are:
```
  DM - Direct Method
 ODM - Optimized Direct Method
 SDM - Sorting Direct Method
 FRM - First Reaction Method
 NRM - Next Reaction Method
NRMC - Next Reaction Method Compact
MNRM - Modified Next Reaction Method
SNRM - Simplified Next Reaction Method
  RM - Rejection Method
```

## Example of input file:

```sh
#reaction rate constants
k1=1;
k2=2;
k3=0.0042;
k4=10;
k5=1;
#delays
t1=1;
t2=10;
t3=40;
v1=10;
#specie quantities
A=1;
B=1;
C=1;
D=1;
E=1;
F=1;
G=1;
#reactions
transcription,k1:A + B -> C;
transcription,k2:B + C -> D;
transcription,k3:D + E -> E + F;
transcription,k4:F -> D + G;
transcription,k5:E + G -> A;
```
__IMPORTANT:__ Comments are not supported in the input file

:+1: Credits for the input file structure: Camillo de Lellis Falcão da Silva
