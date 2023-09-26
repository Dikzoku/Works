// 完成 PL/0 语言的语法分析器
// 词法分析器会向语法分析器提供词语流。你需要以合适的方式对词语流进行分析，并生成一颗语法树，或者宣告语法错误。
// 如果输入的程序包含语法错误，仅输出一行"Syntax Error"（不含引号）
// 评测程序只会读取你的程序输出到标准输出的内容。你可以向标准错误流打印若干信息以方便调试，美观输出或是出于其他任何原因。

// 如果该节点是(，即左括号，该节点应当输出为 LP
// 如果该节点是)，即右括号，该节点应当输出为 RP
// 如果该节点是,，即逗号，该节点应当输出为 COMMA
// 如果该节点是其他的叶子节点（对应词法分析器中的某一个词语），那么其名称为其本身
// 如果该节点不是一个叶子节点，则遵循下表进行替换输出

// 上下文无关文法中的节点	对应的替换词语
// 程序	PROGRAM
// 分程序	SUBPROG
// 常量说明部分	CONSTANTDECLARE
// 常量定义	CONSTANTDEFINE
// 无符号整数	< 这是一个叶子节点，用其本身替代 >
// 变量说明部分	VARIABLEDECLARE
// 标识符	< 这是一个叶子节点，用其本身替代 >
// 过程说明部分	PROCEDUREDECLARE
// 过程首部	PROCEDUREHEAD
// 语句	SENTENCE
// 赋值语句	ASSIGNMENT
// 复合语句	COMBINED
// 条件	CONDITION
// 表达式	EXPRESSION
// 项	ITEM
// 因子	FACTOR
// 加减运算符	< 这是一个叶子节点，用其本身替代 >
// 乘除运算符	< 这是一个叶子节点，用其本身替代 >
// 关系运算符	< 这是一个叶子节点，用其本身替代 >
// 条件语句	IFSENTENCE
// 过程调用语句	CALLSENTENCE
// 当型循环语句	WHILESENTENCE
// 读语句	READSENTENCE
// 写语句	WRITESENTENCE
// 空语句	EMPTY

// <程序>→<分程序>.
// <分程序>→ [<常量说明部分>][<变量说明部分>][<过程说明部分>]<语句>
// <常量说明部分> → CONST<常量定义>{ ,<常量定义>};
// <常量定义> → <标识符>=<无符号整数>
// <无符号整数> → <数字>{<数字>}
// <变量说明部分> → VAR<标识符>{ ,<标识符>};
// <标识符> → <字母>{<字母>|<数字>}
// <过程说明部分> → <过程首部><分程序>;{<过程说明部分>}
// <过程首部> → PROCEDURE <标识符>;
// <语句> → <赋值语句>|<条件语句>|<当型循环语句>|<过程调用语句>|<读语句>|<写语句>|<复合语句>|<空语句>
// <赋值语句> → <标识符>:=<表达式>
// <复合语句> → BEGIN<语句>{ ;<语句>} END
// <条件> → <表达式><关系运算符><表达式>|ODD<表达式>
// <表达式> → [+|-]<项>{<加减运算符><项>}
// <项> → <因子>{<乘除运算符><因子>}
// <因子> → <标识符>|<无符号整数>|(<表达式>)
// <加减运算符> → +|-
// <乘除运算符> → *|/
// <关系运算符> → =|#|<|<=|>|>=
// <条件语句> → IF<条件>THEN<语句>
// <过程调用语句> → CALL<标识符>
// <当型循环语句> → WHILE<条件>DO<语句>
// <读语句> → READ(<标识符>{ ,<标识符>})
// <写语句> → WRITE(<标识符>{,<标识符>})
// <字母> → A|B|C…X|Y|Z
// <数字> → 0|1|2…7|8|9
// <空语句> → epsilon
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include "LexicalAnalyse.cpp"


class SyntaxAnalyse{
public:
    SyntaxAnalyse();
    ~SyntaxAnalyse();
    void analyse(vector<pl0word> words);
    void printTree();
    void printCode();

    void printNameTable();
private:
    vector<pl0word> words;
    vector<pl0word>::iterator it;
    treeNode *root;
    int procedure_depth; //过程嵌套层数
    
    void _printTree(treeNode *t);
    void analyseProgram(treeNode *t); //程序
    void analyseSubprog(treeNode *t); //分程序
    void analyseConstDeclare(treeNode *t); //常量说明部分
    void analyseConstDefine(treeNode *t); //常量定义
    void analyseUnsignedInteger(treeNode *t); //无符号整数
    void analyseVariableDeclare(treeNode *t);  //变量说明部分
    void analyseIdentifier(treeNode *t); //标识符
    void analyseProcedureDeclare(treeNode *t); //过程说明部分
    void analyseProcedureHead(treeNode *t); //过程首部
    void analyseSentence(treeNode *t); //语句
    void analyseAssignment(treeNode *t); //赋值语句 
    void analyseCombined(treeNode *t); //复合语句
    void analyseCondition(treeNode *t); //条件
    void analyseExpression(treeNode *t); //表达式
    void analyseItem(treeNode *t); //项
    void analyseFactor(treeNode *t); //因子
    void analyseAddSubOperator(treeNode *t); //加减运算符
    void analyseMulDivOperator(treeNode *t); //乘除运算符
    void analyseRelationOperator(treeNode *t); //关系运算符
    void analyseIfSentence(treeNode *t); //条件语句
    void analyseCallSentence(treeNode *t); //过程调用语句
    void analyseWhileSentence(treeNode *t); //当型循环语句 
    void analyseReadSentence(treeNode *t); //读语句
    void analyseWriteSentence(treeNode *t); //写语句
    void analyseEmpty(treeNode *t); //空语句

//------------------目标代码生成------------------start
    int OPR_cnt = 14;
    string OPR_Table[20] = {"RETURN","ODD","READ","WRITE", "+", "-", "*", "/","=", "#", "<", "<=", ">", ">="};
    vector<NameTable> table;
    vector<TargetCode> code;
    void addTable(string name, string kind, int parameter1, int parameter2);
    void addCode(string f, int l, int a);

    int getIndexbyName(int level, string name);
    int getIndexbyOPR(string opr);
//-----------------------------------------------end
};
void SyntaxAnalyse::printNameTable(){
    cout << "NameTable:" << endl;
    cout << "name\tkind\tparameter1\tparameter2" << endl;
    for(int i = 0; i < table.size(); i++){
        cout << table[i].name << "\t" << table[i].kind << "\t" << table[i].parameter1 << "\t" << table[i].parameter2 << endl;
    }
}

//------------------目标代码生成------------------start
void SyntaxAnalyse::printCode()
{
    for(int i = 0; i < code.size(); i++)
    {
        cout<< code[i].f << " " << code[i].l << " " << code[i].a << endl;
    }
}
void SyntaxAnalyse::addTable(string name, string kind, int parameter1, int parameter2)
{
    NameTable t;
    t.name = name;
    t.kind = kind;
    t.parameter1 = parameter1;
    t.parameter2 = parameter2;
    table.push_back(t);
}
void SyntaxAnalyse::addCode(string f, int l, int a)
{
    TargetCode t;
    t.f = f;
    t.l = l;
    t.a = a;
    code.push_back(t);
}
int SyntaxAnalyse::getIndexbyName(int level,string name)
{
    for(int i = table.size() - 1; i >= 0; i--)
    {
        if(table[i].name == name ){
            if(table[i].kind == "CONSTANT") return i;
            if(table[i].kind == "VARIABLE" && table[i].parameter1 <= level) return i;
        }
    }
    return -1;
}
int SyntaxAnalyse::getIndexbyOPR(string opr)
{
    for(int i = 0; i < OPR_cnt; i++)
    {
        if(OPR_Table[i] == opr) return i;
    }
    return -1;
}

//-----------------------------------------------end
SyntaxAnalyse::SyntaxAnalyse()
{
    root = NULL;
    procedure_depth = 0;
}

SyntaxAnalyse::~SyntaxAnalyse()
{
    if(root != NULL) delete root;
}

void SyntaxAnalyse::printTree()
{
    _printTree(root);
}
void SyntaxAnalyse::_printTree(treeNode *t)
{
    if(t == NULL)
        return;
    if (t->child.size() == 0)
    {
        cout << t->element;
        return;
    }
    cout << t->element;
    cout << "(";
    for (int i = 0; i < t->child.size(); i++)
    {
        _printTree(t->child[i]);
        if(i != t->child.size()-1) cout<<",";
    }
    cout << ")";
}

void SyntaxAnalyse::analyse(vector<pl0word> _words)
{
    for(int i = 0; i < _words.size(); i++)
    {
        words.push_back(_words[i]);
    }
    it = words.begin();
    root = new treeNode("PROGRAM");
    analyseProgram(root);
}


//程序
void SyntaxAnalyse::analyseProgram(treeNode *t){
    if(words.size() == 0)
        throw "Syntax Error";
    treeNode *tSubprog = new treeNode("SUBPROG");
	analyseSubprog(tSubprog);
	if (it->name == ".")
	{
		t->child.push_back(tSubprog);
        t->child.push_back(new treeNode("."));
	}
	else
		throw "Syntax Error";
    
    if(it != words.end() - 1) //还有未分析的单词
        throw "Syntax Error";
}

//分程序
void SyntaxAnalyse::analyseSubprog(treeNode *t){
//-------------------------------------start
    addCode("JMP", 0, 0);
    int tmpidx = code.size() - 1;
    bool flag = false;
//-------------------------------------end
    if (it->name == "CONST")
    {
        treeNode *tConstDeclare = new treeNode("CONSTANTDECLARE");
        analyseConstDeclare(tConstDeclare);
        t->child.push_back(tConstDeclare);
    }
    if (it->name == "VAR")
    {
        treeNode *tVariableDeclare = new treeNode("VARIABLEDECLARE");
        analyseVariableDeclare(tVariableDeclare);
        t->child.push_back(tVariableDeclare);
    }
    if (it->name == "PROCEDURE")
    {
        flag = true;
        treeNode *tProcedureDeclare = new treeNode("PROCEDUREDECLARE");
        analyseProcedureDeclare(tProcedureDeclare);
        t->child.push_back(tProcedureDeclare);
    }
//--------------------------------------start
    if(!flag)
        code.erase(code.end()-1);
    else
        code[tmpidx].a = code.size();
    int varCount = 0;
    for(int i = 0; i < table.size(); i++)
    {
        if(table[i].kind == "VARIABLE" && table[i].parameter1 == procedure_depth)
            varCount++;
    }
    addCode("INT", 0, varCount+3);
//-----------------------------------------------end
    treeNode *tSentence = new treeNode("SENTENCE");
    analyseSentence(tSentence);
    t->child.push_back(tSentence);
//-------------------------------------start
    addCode("OPR", 0, 0);
//-------------------------------------end
}

//常量说明部分
void SyntaxAnalyse::analyseConstDeclare(treeNode *t){
    if (it->name == "CONST")
    {
        it++;
        treeNode *tConstDefine = new treeNode("CONSTANTDEFINE");
        analyseConstDefine(tConstDefine);
        t->child.push_back(new treeNode("CONST"));
        t->child.push_back(tConstDefine);
        while (it->name == ",")
        {
            it++;
            tConstDefine = new treeNode("CONSTANTDEFINE");
            analyseConstDefine(tConstDefine);
            t->child.push_back(new treeNode("COMMA"));
            t->child.push_back(tConstDefine);
        }
        if (it->name == ";")
        {
            it++;
            t->child.push_back(new treeNode(";"));
        }
        else
            throw "Syntax Error";
    }
    else
        throw "Syntax Error";
}
 
//常量定义
void SyntaxAnalyse::analyseConstDefine(treeNode *t){
//-----------------------------------------------start
    for(int i = 0; i < table.size(); i++)
    {
        if(table[i].name == it->name)
            throw "GenCode Error";
    }
    addTable(it->name, "CONSTANT", 0, 0);
//-----------------------------------------------end
    treeNode *tIdentifier = new treeNode("IDENTIFIER?");
    analyseIdentifier(tIdentifier);
    t->child.push_back(tIdentifier);
    if (it->name == "=")
    {
        it++;
//-----------------------------------------------start
        table[table.size()-1].parameter1 = atoi(it->name.c_str());
//-----------------------------------------------end
        treeNode *tUnsignedInteger = new treeNode("UNSIGNEDINTEGER?");
        analyseUnsignedInteger(tUnsignedInteger);
        t->child.push_back(new treeNode("="));
        t->child.push_back(tUnsignedInteger);
    }
    else
        throw "Syntax Error";
}

//无符号整数
void SyntaxAnalyse::analyseUnsignedInteger(treeNode *t){
    if (it->sym == "NUMBER")
    {
        t->element = it->name;
        it++;
    }
    else
        throw "Syntax Error";
}

//变量说明部分
void SyntaxAnalyse::analyseVariableDeclare(treeNode *t){
    int dx = 3;
    if (it->name == "VAR")
    {
        it++;
//-----------------------------------------------start
        int idx = getIndexbyName(procedure_depth,it->name);
        if(idx != -1 && table[idx].kind == "CONSTANT")
            throw "GenCode Error";
        addTable(it->name, "VARIABLE", procedure_depth, dx++);
//-----------------------------------------------end
        treeNode *tIdentifier = new treeNode("IDENTIFIER?");
        analyseIdentifier(tIdentifier);
        t->child.push_back(new treeNode("VAR"));
        t->child.push_back(tIdentifier);
        while (it->name == ",")
        {
            it++;
//-----------------------------------------------start
            int idx = getIndexbyName(procedure_depth,it->name);
            if(idx != -1 && table[idx].kind == "CONSTANT")
                throw "GenCode Error";
            addTable(it->name, "VARIABLE", procedure_depth, dx++);
//-----------------------------------------------end
            tIdentifier = new treeNode("IDENTIFIER?");
            analyseIdentifier(tIdentifier);
            t->child.push_back(new treeNode("COMMA"));
            t->child.push_back(tIdentifier);
        }
        if (it->name == ";")
        {
            it++;
            t->child.push_back(new treeNode(";"));
        }
        else
            throw "Syntax Error";
    }
    else
        throw "Syntax Error";
}

//标识符
void SyntaxAnalyse::analyseIdentifier(treeNode *t){
    if (it->sym == "IDENTIFIER")
    {
        t->element = it->name;
        it++;
    }
    else
        throw "Syntax Error";
}

//过程说明部分
void SyntaxAnalyse::analyseProcedureDeclare(treeNode *t){
    procedure_depth++;
    treeNode *tProcedureHead = new treeNode("PROCEDUREHEAD");
    analyseProcedureHead(tProcedureHead);
    t->child.push_back(tProcedureHead);
    treeNode *tSubprog = new treeNode("SUBPROG");


    if(procedure_depth > 3) //过程嵌套深度不能超过3
        throw "Syntax Error";
    analyseSubprog(tSubprog);
    procedure_depth--;

    t->child.push_back(tSubprog);
    if(it->name == ";")
    {
        it++;
        t->child.push_back(new treeNode(";"));
    }
    else
        throw "Syntax Error";
    
    if(it->name == "PROCEDURE")
    {
        treeNode *tProcedureDeclare = new treeNode("PROCEDUREDECLARE");
        analyseProcedureDeclare(tProcedureDeclare);
        t->child.push_back(tProcedureDeclare);
    }
}

//过程首部
void SyntaxAnalyse::analyseProcedureHead(treeNode *t){
    if (it->name == "PROCEDURE")
    {
        it++;
//-----------------------------------------------start
        addTable(it->name, "PROCEDURE", procedure_depth-1, code.size());
//-----------------------------------------------end
        treeNode *tIdentifier = new treeNode("IDENTIFIER?");
        analyseIdentifier(tIdentifier);
        t->child.push_back(new treeNode("PROCEDURE"));
        t->child.push_back(tIdentifier);
        if (it->name == ";")
        {
            it++;
            t->child.push_back(new treeNode(";"));
        }
        else
            throw "Syntax Error";
    }
    else
        throw "Syntax Error";
}

//语句
void SyntaxAnalyse::analyseSentence(treeNode *t){
    if (it->sym == "IDENTIFIER")
    {
        treeNode *tAssignment = new treeNode("ASSIGNMENT");
        analyseAssignment(tAssignment);
        t->child.push_back(tAssignment);
    }
    else if (it->name == "IF")
    {
        treeNode *tIfSentence = new treeNode("IFSENTENCE");
        analyseIfSentence(tIfSentence);
        t->child.push_back(tIfSentence);
    }
    else if (it->name == "WHILE")
    {
        treeNode *tWhileSentence = new treeNode("WHILESENTENCE");
        analyseWhileSentence(tWhileSentence);
        t->child.push_back(tWhileSentence);
    }
    else if (it->name == "CALL")
    {
        treeNode *tCallSentence = new treeNode("CALLSENTENCE");
        analyseCallSentence(tCallSentence);
        t->child.push_back(tCallSentence);
    }
    else if (it->name == "READ")
    {
        treeNode *tReadSentence = new treeNode("READSENTENCE");
        analyseReadSentence(tReadSentence);
        t->child.push_back(tReadSentence);
    }
    else if (it->name == "WRITE")
    {
        treeNode *tWriteSentence = new treeNode("WRITESENTENCE");
        analyseWriteSentence(tWriteSentence);
        t->child.push_back(tWriteSentence);
    }
    else if (it->name == "BEGIN")
    {
        treeNode *tCombined = new treeNode("COMBINED");
        analyseCombined(tCombined);
        t->child.push_back(tCombined);
    }
    else if (it->name == "END" || it->name == "." || it->name == ";"){
        treeNode *tEmpty = new treeNode("EMPTY");
        analyseEmpty(tEmpty);
        t->child.push_back(tEmpty);
    }else
        throw "Syntax Error";
}

//赋值语句
void SyntaxAnalyse::analyseAssignment(treeNode *t){
    if (it->sym == "IDENTIFIER")
    {
        string idname = it->name;
        t->child.push_back(new treeNode(it->name));
        it++;
        if (it->name == ":=")
        {
            t->child.push_back(new treeNode(":="));
            it++;
            treeNode *tExpression = new treeNode("EXPRESSION");
            analyseExpression(tExpression);
            t->child.push_back(tExpression);
//-----------------------------------
        int index = getIndexbyName(procedure_depth,idname);
        if(index == -1)
            throw "GenCode Error";
        if(table[index].kind != "VARIABLE")
            throw "GenCode Error";
        addCode("STO", abs(table[index].parameter1 - procedure_depth), table[index].parameter2);
//-----------------------------------
        }
        else
            throw "Syntax Error";
    }
    else
        throw "Syntax Error";
}

//复合语句
void SyntaxAnalyse::analyseCombined(treeNode *t){
    if(it->name == "BEGIN"){
        it++;
        t->child.push_back(new treeNode("BEGIN"));
        treeNode *tSentence = new treeNode("SENTENCE");
        analyseSentence(tSentence);
        t->child.push_back(tSentence);
        while(it->name == ";"){
            t->child.push_back(new treeNode(";"));
            it++;
            tSentence = new treeNode("SENTENCE");
            analyseSentence(tSentence);
            t->child.push_back(tSentence);
        }
        if(it->name == "END"){
            it++;
            t->child.push_back(new treeNode("END"));
        }
        else
            throw "Syntax Error";
    }
    else
        throw "Syntax Error";
}

//条件
void SyntaxAnalyse::analyseCondition(treeNode *t){
    if (it->name == "ODD")
    {
        it++;
        treeNode *tExpression = new treeNode("EXPRESSION");
        analyseExpression(tExpression);
        t->child.push_back(new treeNode("ODD"));
        t->child.push_back(tExpression);
//-----------------------------------
        addCode("OPR", 0, getIndexbyOPR("ODD"));
//-----------------------------------
    }
    else
    {
        treeNode *tExpression1 = new treeNode("EXPRESSION");
        analyseExpression(tExpression1);
        t->child.push_back(tExpression1);
//-----------------------------------
        string opr = it->name;
//-----------------------------------
        treeNode *tRelationOperator = new treeNode("RELATIONOPERATOR?");
        analyseRelationOperator(tRelationOperator);
        t->child.push_back(tRelationOperator);
        treeNode *tExpression2 = new treeNode("EXPRESSION");
        analyseExpression(tExpression2);
        t->child.push_back(tExpression2);
//-----------------------------------
        addCode("OPR", 0, getIndexbyOPR(opr));
//-----------------------------------
    }
}

//表达式
void SyntaxAnalyse::analyseExpression(treeNode *t){
    string opr = it->name;
    if (it->name == "+" || it->name == "-")
    {
        addCode("LIT", 0, 0);
        t->child.push_back(new treeNode(it->name));
        it++;
    }
    treeNode *tItem = new treeNode("ITEM");
    analyseItem(tItem);
    t->child.push_back(tItem);
    //-----------------------------------
    if (opr == "-" || opr == "+"){
        addCode("OPR", 0, getIndexbyOPR(opr));
    }
    //-----------------------------------
    while (it->name == "+" || it->name == "-")
    {
//-----------------------------------
        string opr = it->name;
//-----------------------------------
        treeNode *tAddSubOperator = new treeNode("ADD_SUB_OPERATOR?");
        analyseAddSubOperator(tAddSubOperator);
        t->child.push_back(tAddSubOperator);

        tItem = new treeNode("ITEM");
        analyseItem(tItem);
        t->child.push_back(tItem);
//-----------------------------------
        addCode("OPR", 0, getIndexbyOPR(opr));
//-----------------------------------
    }
}

//项
void SyntaxAnalyse::analyseItem(treeNode *t){
    treeNode *tFactor = new treeNode("FACTOR");
    analyseFactor(tFactor);
    t->child.push_back(tFactor);
    while (it->name == "*" || it->name == "/")
    {
//-----------------------------------
        string opr = it->name;
//-----------------------------------
        treeNode *tMulDivOperator = new treeNode("MUL_DIV_OPERATOR?");
        analyseMulDivOperator(tMulDivOperator);
        t->child.push_back(tMulDivOperator);

        tFactor = new treeNode("FACTOR");
        analyseFactor(tFactor);
        t->child.push_back(tFactor);
//-----------------------------------
        addCode("OPR", 0, getIndexbyOPR(opr));
//-----------------------------------
    }
}

//因子
void SyntaxAnalyse::analyseFactor(treeNode *t){
    if (it->sym == "IDENTIFIER")
    {
//-----------------------------------
        int index = getIndexbyName(procedure_depth,it->name);
        if(index == -1)
            throw "GenCode Error";
        if(table[index].kind == "CONSTANT")
            addCode("LIT", 0, table[index].parameter1);
        else if(table[index].kind == "VARIABLE")
            addCode("LOD", abs(table[index].parameter1 - procedure_depth), table[index].parameter2);
        else
            throw "GenCode Error";
//-----------------------------------
        t->child.push_back(new treeNode(it->name));
        it++;
    }
    else if (it->sym == "NUMBER")
    {
//-----------------------------------
        addCode("LIT", 0, stoi(it->name));
//-----------------------------------
        t->child.push_back(new treeNode(it->name));
        it++;
    }
    else if (it->name == "(")
    {
        it++;
        t->child.push_back(new treeNode("LP"));
        treeNode *tExpression = new treeNode("EXPRESSION");
        analyseExpression(tExpression);
        t->child.push_back(tExpression);
        if (it->name == ")")
        {
            it++;
            t->child.push_back(new treeNode("RP"));
        }
        else
            throw "Syntax Error";
    }
    else
        throw "Syntax Error";
}

//加减运算符
void SyntaxAnalyse::analyseAddSubOperator(treeNode *t){
    if (it->name == "+" || it->name == "-")
    {
        t->element = it->name;
        it++;
    }
    else
        throw "Syntax Error";
}
//乘除运算符
void SyntaxAnalyse::analyseMulDivOperator(treeNode *t){
    if (it->name == "*" || it->name == "/")
    {
        t->element = it->name;
        it++;
    }
    else
        throw "Syntax Error";
}
//关系运算符
void SyntaxAnalyse::analyseRelationOperator(treeNode *t){
    if (it->name == "=" || it->name == "#" || it->name == "<" || it->name == "<=" || it->name == ">" || it->name == ">=")
    {
        t->element = it->name;
        it++;
    }
    else
        throw "Syntax Error";
}

//-------------------------------------------------------
//条件语句
void SyntaxAnalyse::analyseIfSentence(treeNode *t){
    if (it->name == "IF")
    {
        it++;
        treeNode *tCondition = new treeNode("CONDITION");
        analyseCondition(tCondition);
        t->child.push_back(new treeNode("IF"));
        t->child.push_back(tCondition);
//-----------------------------------
        addCode("JPC", 0, 0);
        int index = code.size() - 1;
//-----------------------------------
        if (it->name == "THEN")
        {
            it++;
            treeNode *tSentence = new treeNode("SENTENCE");
            analyseSentence(tSentence);
            t->child.push_back(new treeNode("THEN"));
            t->child.push_back(tSentence);
//-----------------------------------start
            code[index].a = code.size();
//-----------------------------------end
        }
        else
            throw "Syntax Error";
    }
    else
        throw "Syntax Error";
}

//过程调用语句
void SyntaxAnalyse::analyseCallSentence(treeNode *t){
    if (it->name == "CALL")
    {
        it++;
//-----------------------------------start
        int tmpidx = -1;
        for(int i = table.size() - 1; i >= 0; i--)
        {
            if(table[i].name == it->name && table[i].parameter1 <= procedure_depth &&table[i].kind=="PROCEDURE") 
            {
                tmpidx = i;
                break;
            }
        }
        if(tmpidx == -1)
            throw "GenCode Error";
        int tmpaddr = table[tmpidx].parameter2;
        addCode("CAL", abs(table[tmpidx].parameter1 - procedure_depth), tmpaddr);
//-----------------------------------end
        treeNode *tIdentifier= new treeNode("IDENTIFIER?");
        analyseIdentifier(tIdentifier);
        t->child.push_back(new treeNode("CALL"));
        t->child.push_back(tIdentifier);
    }
    else
        throw "Syntax Error";
}

//当型循环语句
void SyntaxAnalyse::analyseWhileSentence(treeNode *t){
    if (it->name == "WHILE")
    {
        it++;
//-----------------------------------start
        int tmpaddr1 = code.size();
//-----------------------------------end
        treeNode *tCondition = new treeNode("CONDITION");
        analyseCondition(tCondition);
        t->child.push_back(new treeNode("WHILE"));
        t->child.push_back(tCondition);
//-----------------------------------start
        addCode("JPC", 0, 0);
        int tmpaddr2 = code.size() - 1;
//-----------------------------------end        
        if (it->name == "DO")
        {
            it++;
            treeNode *tSentence = new treeNode("SENTENCE");
            analyseSentence(tSentence);
            t->child.push_back(new treeNode("DO"));
            t->child.push_back(tSentence);
//-----------------------------------start
            addCode("JMP", 0, tmpaddr1);
            code[tmpaddr2].a = code.size();
//-----------------------------------end
        }
        else
            throw "Syntax Error";
    }
    else
        throw "Syntax Error";
}

//读语句
void SyntaxAnalyse::analyseReadSentence(treeNode *t){
    if (it->name == "READ")
    {
        it++;
        t->child.push_back(new treeNode("READ"));
        if (it->name == "(")
        {
            it++;
//-----------------------------------start
            addCode("OPR", 0, getIndexbyOPR("READ"));
            int tmpidx = getIndexbyName(procedure_depth,it->name);
            if(tmpidx == -1)
                throw "GenCode Error";
            if(table[tmpidx].kind == "CONSTANT")
                throw "GenCode Error";
            addCode("STO", abs(table[tmpidx].parameter1 - procedure_depth), table[tmpidx].parameter2);
//-----------------------------------end
            t->child.push_back(new treeNode("LP"));
            treeNode *tIdentifier = new treeNode("IDENTIFIER?");
            analyseIdentifier(tIdentifier);
            t->child.push_back(tIdentifier);
            while (it->name == ",")
            {
                it++;
//-----------------------------------start
                addCode("OPR", 0, getIndexbyOPR("READ"));
                int tmpidx = getIndexbyName(procedure_depth,it->name);
                if(tmpidx == -1)
                    throw "GenCode Error";
                if(table[tmpidx].kind == "CONSTANT")
                    throw "GenCode Error";
                addCode("STO", abs(table[tmpidx].parameter1 - procedure_depth), table[tmpidx].parameter2);
//-----------------------------------end
                tIdentifier = new treeNode("IDENTIFIER?");
                analyseIdentifier(tIdentifier);
                t->child.push_back(new treeNode("COMMA"));
                t->child.push_back(tIdentifier);
            }

            if (it->name == ")")
            {
                it++;
                t->child.push_back(new treeNode("RP"));
            }
            else
                throw "Syntax Error";
        }
        else
            throw "Syntax Error";
    }
    else
        throw "Syntax Error";
}

//写语句
void SyntaxAnalyse::analyseWriteSentence(treeNode *t){
    if (it->name == "WRITE")
    {
        it++;
        t->child.push_back(new treeNode("WRITE"));
        if (it->name == "(")
        {
            it++;
//-----------------------------------start
            int tmpidx = getIndexbyName(procedure_depth,it->name);
            if(tmpidx == -1)
                throw "GenCode Error";
            if(table[tmpidx].kind == "CONSTANT")
                addCode("LIT", 0, table[tmpidx].parameter1);
            else
                addCode("LOD", abs(table[tmpidx].parameter1 - procedure_depth), table[tmpidx].parameter2);
            addCode("OPR", 0, getIndexbyOPR("WRITE"));
//-----------------------------------end
            t->child.push_back(new treeNode("LP"));

            treeNode *tIdentifier = new treeNode("IDENTIFIER?");
            analyseIdentifier(tIdentifier);
            t->child.push_back(tIdentifier);

            while (it->name == ",")
            {
                it++;
//-----------------------------------start
                tmpidx = getIndexbyName(procedure_depth,it->name);
                if(tmpidx == -1)
                    throw "GenCode Error";
                if(table[tmpidx].kind == "CONSTANT")
                    addCode("LIT", 0, table[tmpidx].parameter1);
                else
                    addCode("LOD", abs(table[tmpidx].parameter1 - procedure_depth), table[tmpidx].parameter2);
                addCode("OPR", 0, getIndexbyOPR("WRITE")); 
//-----------------------------------end
                tIdentifier = new treeNode("IDENTIFIER?");
                analyseIdentifier(tIdentifier);
                t->child.push_back(new treeNode("COMMA"));
                t->child.push_back(tIdentifier);
            }
            if (it->name == ")")
            {
                it++;
                t->child.push_back(new treeNode("RP"));
            }
            else
                throw "Syntax Error";
        }
        else
            throw "Syntax Error";
    }
    else
        throw "Syntax Error";
}

//空语句
void SyntaxAnalyse::analyseEmpty(treeNode *t){
    t->element = "EMPTY";
}
