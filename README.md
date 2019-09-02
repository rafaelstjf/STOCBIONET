# STOCBIONET

[![Open Source Love](https://badges.frapsoft.com/os/v2/open-source.svg?v=103)](https://github.com/ellerbrock/open-source-badges/) [![GPL Licence](https://badges.frapsoft.com/os/gpl/gpl.svg?v=103)](https://opensource.org/licenses/GPL-3.0/) 


Stochastic simulation algorithms for Gene Regulatory Networks for delayed and non-delayed reactions.

## Avaiable methods:

 * Direct method __(Gillespie, 1977)__
 * Sorting direct method __(McCollum et al, 2006)__
 * First reaction method __(Gillespie, 1976)__
 * Next reaction method __(Gibson and Bruck, 2000)__
 * Modified next reaction method __(Anderson, 2007)__
 * Simplified next reaction method __(Silva, 2014)__
 * Rejection method __(Bratsun et al, 2005)__
 * Optimized direct method __(Cao et al, 2004)__
 * Rejection method using a circular list

 
## Methods in development:
 
 * Rejection method using Hash Tables (__90%__) and heap (__99.9%__)
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
RM-OL - Rejection Method using an ordered list
 RM-H - Rejection Method using a circular list
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

### __REFERENCES__

ANDERSON, David F. A modified next reaction method for simulating chemical systems with time dependent propensities and delays. The Journal of chemical physics, v. 127, n. 21, p. 214107, 2007.

BRATSUN, Dmitri et al. Delay-induced stochastic oscillations in gene regulation. Proceedings of the National Academy of Sciences, v. 102, n. 41, p. 14593-14598, 2005.

CAO, Yang; LI, Hong; PETZOLD, Linda. Efficient formulation of the stochastic simulation algorithm for chemically reacting systems. The journal of chemical physics, v. 121, n. 9, p. 4059-4067, 2004.

GIBSON, Michael A.; BRUCK, Jehoshua. Efficient exact stochastic simulation of chemical systems with many species and many channels. The journal of physical chemistry A, v. 104, n. 9, p. 1876-1889, 2000.

GILLESPIE, Daniel T. A general method for numerically simulating the stochastic time evolution of coupled chemical reactions. Journal of computational physics, v. 22, n. 4, p. 403-434, 1976.

GILLESPIE, Daniel T. Exact stochastic simulation of coupled chemical reactions. The journal of physical chemistry, v. 81, n. 25, p. 2340-2361, 1977.

MCCOLLUM, James M. et al. The sorting direct method for stochastic simulation of biochemical systems with varying reaction execution behavior. Computational biology and chemistry, v. 30, n. 1, p. 39-49, 2006.

SILVA, Camillo de Lellis Falcão da et al. Novos algoritmos de simulação estocástica com atraso para redes gênicas. 2014.

:+1: Credits for the input file structure: Camillo de Lellis Falcão da Silva
