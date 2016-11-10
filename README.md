# TemplatedProcessor
This is a POC for my ASR course in the ENS Lyon.
This code was created for an homework with my friend AlgueRythme. He was working on the assembler part.

The processor is on  bits, the ISA was developped by the 2016-2017 L3 Informatic promotion of the ENS Lyon with Eddy Caron and Nicolas Louvet.

The goal of this POC is to work code generation of c++. 
An instruction is a function which is going to modify the memory (a vector of 16 bits words) and the registers (an fixed size array of 16 bits words).
The idea is to generate every instruction with the c++ template code generation : every instruction is associated with an opcode, so there are 2^16 instructions to generate.

FOR MY TEACHERS (1er rendu)
Le code fonctionne bien pour tout ce que j'ai pu tester, donc la multiplication et des tests mémoires.
J'ai voulu refaire le code c++ pour m'exercer à manipuler la méta programmation.