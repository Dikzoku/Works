#include <string>
#include <vector>
using namespace std;

struct pl0word{
    string name;
    string sym;
    int line;
    int col;
    pl0word(){
        name = "";
        sym = "";
        line = 0;
        col = 0;
    }
    pl0word(const pl0word& wd){
        name = wd.name;
        sym = wd.sym;
        line = wd.line;
        col = wd.col;
    }
    //重载赋值运算符
    pl0word& operator=(const pl0word& wd){
        name = wd.name;
        sym = wd.sym;
        line = wd.line;
        col = wd.col;
        return *this;
    }
};

struct treeNode
{
	string element;
    vector<treeNode*> child;

	treeNode(string _element) 
	{
		element = _element;
	}
    ~treeNode()
    {
        for (int i = 0; i < child.size(); i++)
        {
            if(child[i] != NULL) delete child[i];
        }
    }
};

// 生成的目标代码是一种假想栈式计算机的汇编语言，其格式如下：

// f l a
// 其中 f 为功能码，l 代表层次差，a 代表位移量。

// 这种假想栈式计算机有一个无限大的栈，以及四个寄存器 IR,IP,SP,BP。

// IR，指令寄存器，存放正在执行的指令。

// IP，指令地址寄存器，存放下一条指令的地址。

// SP，栈顶寄存器，指向运行栈的顶端。

// BP，基址寄存器，指向当前过程调用所分配的空间在栈中的起始地址。
struct TargetCode{
    string f;
    int l;
    int a;
};

// NAME	KIND	PARAMETER1	PARAMETER2
// a	CONSTANT	VAL:35	--
// b	CONSTANT	VAL:49	--
// c	VARIABLE	LEVEL: LEV	ADR: DX
// d	VARIABLE	LEVEL: LEV	ADR: DX+1
// e	VARIABLE	LEVEL: LEV	ADR: DX+2
// p	PROCEDURE	LEVEL: LEV	ADR: <UNKNOWN>
// g	VARIABLE	LEVEL: LEV+1	ADR: DX
// 其中，LEVEL 给出的是层次，DX 是每一层局部量的相对地址。
// 对于过程名的地址，需要等待目标代码生成后再填写。
// 考虑到需要存储调用信息、返回信息等维护函数运行的数据，在本实验中，DX 取 3.
struct NameTable{
    string name;
    string kind;
    int parameter1; // VAL/LEVEL
    int parameter2; // ADR
};