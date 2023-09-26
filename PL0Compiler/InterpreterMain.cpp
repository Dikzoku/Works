#include "Interpreter.cpp"

int main(){
    Interpreter interpreter;
    interpreter.readCode("program.code");
    interpreter.interpret();
    return 0;
}