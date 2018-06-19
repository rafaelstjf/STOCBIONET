# Stochastic simulation algorithms

[![Open Source Love](https://badges.frapsoft.com/os/v2/open-source.svg?v=103)](https://github.com/ellerbrock/open-source-badges/)

Stochastic simulation algorithms for Gene Regulatory Networks for delayed and non-delayed reactions.

## Avaiable methods:

 * Direct method
 * First reaction method
 * [Next reaction method](https://pubs.acs.org/doi/abs/10.1021/jp993732q)
 * [Modified next reaction method](https://aip.scitation.org/doi/abs/10.1063/1.2799998)
 * [Simplified next reaction method](http://repositorio.ufjf.br:8080/jspui/bitstream/ufjf/4828/1/camillodelellisfalcaodasilva.pdf)
 * Next reaction method compact
 
## Methods in development:
 
 * Rejection method (__0%__ )
 * Delayed modified next reaction method (__0%__ )

## Requirements:

 * C++11

## Example of use:

If you are using it in the terminal you can run it without arguments or with the following arguments: Input-file Operation-code Initial-time Maximum-time

The current operations codes are:
```
DM - Direct Method
FRM - First Reaction Method
NRM - Next Reaction Method
NRMC - Next Reaction Method Compact
MNRM - Modified Next Reaction Method
SNRM - Simplified Next Reaction Method
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
#IMPORTANT: Comments not supported
```
:+1: Credits for the input file structure: Camillo de Lellis Falcão da Silva
