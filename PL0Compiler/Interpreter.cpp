#include <stack>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "struct.hpp"
using namespace std;
class Interpreter
{
    public:
        Interpreter();
        ~Interpreter();
        void interpret(); //主要函数，完成对目标代码的解释
        void readCode(string filename); //读取目标代码
    private:
        vector<TargetCode> code; //目标代码
        const static int ret_addr = 0, dynamic_link = 1, static_link = 2;
        //栈中返回地址，动态链，静态链的相对位置
        TargetCode ir; //当前指令
        int ip = 0, sp = 0, bp = 0; //指令指针，栈顶指针，基址指针
        int stack[100000] = { 0 }; //栈
        int sp_stack[1000]; //栈顶指针栈，用于存放每个过程的栈顶指针
        int sp_top = 0; //栈顶指针栈的栈顶指针
};
Interpreter::Interpreter()
{
    ip = 0, sp = 0, bp = 0;
    sp_top = 0;
}
Interpreter::~Interpreter()
{
}
void Interpreter::readCode(string filename)
{
    ifstream fin;
    fin.open(filename);
    TargetCode temp;
    while(fin>>temp.f>>temp.l>>temp.a)
    {
        code.push_back(temp);
    }
    fin.close();
}
// LIT: l 域无效，将 a 放到栈顶
// LOD: 将于当前层层差为 l 的层，变量相对位置为 a 的变量复制到栈顶
// STO: 将栈顶内容复制到于当前层层差为 l 的层，变量相对位置为 a 的变量
// CAL: 调用过程。l 标明层差，a 表明目标程序地址
// INT: l 域无效，在栈顶分配 a 个空间
// JMP: l 域无效，无条件跳转到地址 a 执行
// JPC: l 域无效，若栈顶对应的布尔值为假（即 0）则跳转到地址 a 处执行，否则顺序执行
// OPR: l 域无效，对栈顶和栈次顶执行运算，结果存放在次顶，a=0 时为调用返回
void Interpreter::interpret()
{

    while (ip<code.size())
    {
        ir = code[ip++];
        if(ir.f == "LIT"){
            stack[sp++] = ir.a;
        }else if(ir.f == "LOD"){
            if (ir.l == 0)
                stack[sp++] = stack[bp + ir.a];
            else
            {
                int outer_bp = stack[bp + static_link];
                while (--ir.l)
                    outer_bp = stack[outer_bp + static_link];
                stack[sp++] = stack[outer_bp + ir.a];
            }
        }else if(ir.f == "STO"){
            if (ir.l == 0)
                stack[bp + ir.a] = stack[sp - 1];
            else
            {
                int outer_bp = stack[bp + static_link];
                while (--ir.l)
                    outer_bp = stack[outer_bp + static_link];
                stack[outer_bp + ir.a] = stack[sp - 1];
            }
        }else if(ir.f == "CAL"){
            stack[sp + ret_addr] = ip;
            stack[sp + dynamic_link] = bp;
            if(ir.l == 0)
                stack[sp + static_link] = bp;
            else
            {
                int outer_bp = stack[bp + static_link];
                while (--ir.l)
                    outer_bp = stack[outer_bp + static_link];
                stack[sp + static_link] = outer_bp;
            }
            ip = ir.a;
            bp = sp;
        }else if(ir.f == "INT"){
            sp_stack[sp_top++] = sp;
            sp += ir.a;
        }else if(ir.f == "JMP"){
            ip = ir.a;
        }else if (ir.f == "JPC"){
            if (stack[sp - 1] == 0)
                ip = ir.a;
            sp--;
        }else if(ir.f == "OPR"){
            //{"RETURN","ODD","READ","WRITE", "+", "-", "*", "/",
            //"=", "#", "<", "<=", ">", ">="};
            switch (ir.a)
            {
                case 0: //OPR_RET
                {
                    ip = stack[bp + ret_addr];
                    bp = stack[bp + dynamic_link];
                    sp = sp_stack[--sp_top];
                    if (sp_top <= 0)
                    {
                        return;
                    }
                    break;
                }
                case 1: //OPR_ODD
                {
                    stack[sp - 1] = stack[sp - 1] % 2;
                    break;
                }
                case 2: //OPR_READ
                {
                    scanf("%d", &stack[sp++]);
                    break;
                }
                case 3: //OPR_WRITE
                {
                    printf("%d\n", stack[sp - 1]);
                    sp--;
                    break;
                }
                case 4: //OPR_+
                {
                    stack[sp - 2] = stack[sp - 1] + stack[sp - 2];
                    sp--;
                    break;
                }
                case 5: //OPR_-
                {
                    stack[sp - 2] = stack[sp - 2] - stack[sp - 1];
                    sp--;
                    break;
                }
                case 6: //OPR_*
                {
                    stack[sp - 2] = stack[sp - 1] * stack[sp - 2];
                    sp--;
                    break;
                }
                case 7: //OPR_/
                {
                    stack[sp - 2] = stack[sp - 2] / stack[sp - 1];
                    sp--;
                    break;
                }
                case 8: //OPR_=
                {
                    stack[sp - 2] = (stack[sp - 2] == stack[sp - 1]) ;
                    sp--;
                    break;
                }
                case 9: //OPR_#
                {
                    stack[sp - 2] = (stack[sp - 2] != stack[sp - 1]) ;
                    sp--;
                    break;
                }
                case 10: //OPR_<
                {
                    stack[sp - 2] = (stack[sp - 2]<stack[sp - 1]);
                    sp--;
                    break;
                }
                case 11: //OPR_<=
                {
                    stack[sp - 2] = (stack[sp - 2] <= stack[sp - 1]);
                    sp--;
                    break;
                }
                case 12: //OPR_>
                {
                    stack[sp - 2] = (stack[sp - 2]>stack[sp - 1]);
                    sp--;
                    break;
                }
                case 13: //OPR_>=
                {
                    stack[sp - 2] = (stack[sp - 2] >= stack[sp - 1]);
                    sp--;
                    break;
                }
                default:{
                   return;
                }
            }
        }
    }
}