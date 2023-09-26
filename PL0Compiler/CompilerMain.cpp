#include "SyntaxAnalyse.cpp"
#include <iostream>
#include <string>
using namespace std;
// >>>>Running Testcase constant_declare_err_4
// [FAIL] Wrong Answer
//>>>>Running Testcase empty
//整个程序为空（ . 也没有），特判一下，为Syntax Error，不特判出现访问越界
int main()
{
    string filename="in.txt";
    
    LexicalAnalyse la;
    SyntaxAnalyse sa;
    if(!la.analyse(filename)){
//        cout<<"Lexical Error"<<endl;
        return -1;
    }else{
        try{
            sa.analyse(la.words);
        }catch(...){
//            cout<<"Syntax Error"<<endl;
            return -1;
        }
        sa.printCode();
    }
    return 0;
}