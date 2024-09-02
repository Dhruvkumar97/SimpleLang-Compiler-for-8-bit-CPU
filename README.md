Implementing a SimpleLang Compiler for 8 bit CPU

Objective: Create a compiler that translates SimpleLang code into assembly code for the 8-bit CPU.

-> 8 bit CPU Simulator used for this project - https://github.com/lightcode/8bit-computer

Short Discription:
-> The compiler code is written in C programming language. 
-> It has 3 main parts: Lexer, Parser and Code Generator.
-> Lexer is used for tokenisation.
-> Parser is used to generate Abstract Syntax Tree(AST).
-> Code Generator is used to generate assembly code by traversing AST.
-> The assembly code is stored in output.asm file
-> output.asm is the used as input to the assembler provided by the 8bit cpu simulator.

How to execute:
-> Keep output.asm file in "tests" directory of 8bit CPU simulator.
-> Run this following commands: 
   1) ./asm/asm.py tests/output.asm > memory.list
   2) make clean && make run
