#! /bin/bash
g++ -c CompilerMain.cpp -o CompilerMain.o -O2
g++ CompilerMain.o -o Compiler -lm

g++ -c InterpreterMain.cpp -o InterpreterMain.o -O2
g++ InterpreterMain.o -o Interpreter -lm

