// 把关键字、算符、界符称为语言固有的单词，标识符、常量称为用户自定义的单词。为此设置两个全程量：NAME,SYM 。
//  SYM：存放每个单词的类别。
//  NAME：存放单词值。
//  要完成的任务：
// 1.	滤掉单词间的空格。
// 2.	识别关键字，用查关键字表的方法识别。当单词是关键字时，将对应的类别放在SYM中。如IF的类别为IFSYM，THEN的类别为THENSYM。
// 3.	识别标识符，标识符的类别为IDENT，IDENT放在SYM中，标识符本身的值放在NAME中。
// 4.	拼数，将数的类别NUMBER放在SYM中，数本身的值放在NAME中。
// 5.	拼由两个字符组成的运算符，如：>=、<=等等，识别后将类别存放在SYM中。
// 6.	打印源程序，边读入字符边打印。
// 注意：由于一个单词是由一个或多个字符组成的，所以需实现一个读字符过程。

// 在 PL/0 语言中，标识符不会超过 10 字符长。如果超过了 10 个字符，你应该认为这是一个词法错误。
// 如果程序包含词法错误，你的程序应当仅输出一行"Lexical Error"，不含引号。
// 输出时，除 Lexical Error 外，输出字母应当均为大写。

//关键词
// CONST,VAR,PROCEDURE,BEGIN,END,ODD,IF,THEN,CALL,WHILE,DO,READ,WRITE

//分隔符
// ; , . ( )

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "struct.hpp"

class LexicalAnalyse{
public:
    vector<pl0word> words;

    LexicalAnalyse(){};
    ~LexicalAnalyse(){};
    
    void print();
    bool analyse(string filename);

private:
    //PL0关键字
    int keylen = 13;
    string keyword[13] = { "CONST","VAR","PROCEDURE","BEGIN",
    "END","ODD","IF","THEN","CALL","WHILE","DO","READ","WRITE" };
    string keysym[13] = { "CONSTSYM","VARSYM","PROCSYM","BEGINSYM",
    "ENDSYM","ODDSYM","IFSYM","THENSYM","CALLSYM","WHILESYM","DOSYM",
    "READSYM","WRITESYM" };
    //PL0运算符
    int oplen = 11;
    string op[11] =  {"=",":=", "+", "-", "*", "/", "#", "<", "<=", ">", ">="};
    string opsym[11] =  {"EQL", "BECOMES", "PLUS", "MINUS", "TIMES", "SLASH",
     "NEQ", "LSS", "LEQ", "GTR", "GEQ"};
    //PL0分隔符
    int dellen = 5;
    string delimiter[5] = { ";", ",", ".", "(", ")" };
    string delsym[5] = {"SEMICOLON", "COMMA", "PERIOD", "LPAREN", "RPAREN" };
    //标识符 IDENTIFIER
    //数 NUMBER

    bool isLetter(char ch); //判断是否为字母
    bool isDigit(char ch);  //判断是否为数字
    bool isDelimiter(char ch); //判断是否为分隔符
    bool isOperator(char ch); //判断是否为运算符
    stringstream readfile(string filename); //读取文件
};


stringstream LexicalAnalyse::readfile(string filename){
    ifstream fin;
    stringstream buffer;
    if(filename == "stdin"){
        //从标准输入所有字符后赋给buffer
        char ch;
        while(cin.get(ch)){
            //转换成大写字母
            if(ch >= 'a' && ch <= 'z'){
                ch -= 32;
            }
            buffer << ch;
        }
    }else{
        fin.open(filename);
        //转换成大写字母
        char ch;
        while(fin.get(ch)){
            if(ch >= 'a' && ch <= 'z'){
                ch -= 32;
            }
            buffer << ch;
        }
        fin.close();
    }
    return buffer;
}
bool LexicalAnalyse::isLetter(char ch){
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool LexicalAnalyse::isDigit(char ch){
    if (ch >= '0' && ch <= '9')
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool LexicalAnalyse::isDelimiter(char ch){
    for (int i = 0; i < dellen; i++)
    {
        if (ch == delimiter[i][0])
        {
            return true;
        }
    }
    return false;
}
bool LexicalAnalyse::isOperator(char ch){
    for (int i = 0; i < oplen; i++)
    {
        if (ch == op[i][0])
        {
            return true;
        }
    }
    return false;
}
bool LexicalAnalyse::analyse(string filename){
    
    int i;
    char ch;
    stringstream buffer = readfile(filename);
    while (!buffer.eof())
    {
        pl0word wd;
        buffer.get(ch);
        if(buffer.eof()){
            break;
        }
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')
        {
            continue;
        }
        else if (isLetter(ch))
        {
            while (!buffer.eof() && (isLetter(ch) || isDigit(ch)))
            {
                wd.name += ch;
                buffer.get(ch);
            }
            if( !(isLetter(ch) || isDigit(ch)) ) buffer.putback(ch);
            if(wd.name.length() > 10){
                return false;
            }
            for (i = 0; i < keylen; i++)
            {
                if (wd.name == keyword[i])
                {
                    break;
                }
            }
            if (i < keylen)
                wd.sym = keysym[i];
            else
                wd.sym = "IDENTIFIER";
        }
        else if (isDigit(ch))
        {
            while (!buffer.eof() && isDigit(ch))
            {
                wd.name += ch;
                buffer.get(ch);
            }
            // 数字后面不能跟字母
            if(isLetter(ch)){
                return false;
            }
            if(!isDigit(ch)) buffer.putback(ch);
            //去除前导0
            while(wd.name[0] == '0'&& wd.name.length() > 1){
                wd.name.erase(0,1);
            }
            wd.sym = "NUMBER";
        }
        else if (isOperator(ch))
        {
            wd.name = ch;
            buffer.get(ch);
            if (ch == '=')
            {
                wd.name += ch;
            }
            else
            {
                buffer.putback(ch);
            }
            for (i = 0; i < oplen; i++)
            {
                if (wd.name == op[i])
                {
                    wd.sym = opsym[i];
                    break;
                }
            }
            if (i == oplen)
                return false;
        }
        else if (isDelimiter(ch))
        {
            wd.name = ch;
            for (i = 0; i < dellen; i++)
            {
                if (wd.name == delimiter[i])
                {
                    wd.sym = delsym[i];
                    break;
                }
            }
        }
        else
            return false;
        words.push_back(wd);
    }
    return true;
}
void LexicalAnalyse::print(){
    for(int i = 0; i < words.size(); i++){
        if(words[i].sym == "NUMBER"||words[i].sym == "IDENTIFIER")
            cout << words[i].sym << " " << words[i].name << endl;
        else
            cout << words[i].name << endl;
    }
}

//测试点5,14有前导零
//测试点17存在运算符为双字符，但是不在op中，此时应输出Lexical Error
//测试点7存在数字后面跟字母，此时应输出Lexical Error