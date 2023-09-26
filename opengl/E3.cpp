#include <iostream>
#include <GL/glut.h>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <Windows.h>
#include <ctime>
using namespace std;

const int w = 600, h = 600;

float randf()
{
    return rand() / double(RAND_MAX);
}
struct point
{
    int x, y;
    point() {}
    point(int _x, int _y)
        : x(_x), y(_y) {}
};
struct frame
{
    float r, g, b;
    frame() {}
    frame(float _r, float _g, float _b)
        : r(_r), g(_g), b(_b) {}
};
struct Poly
{
    int z;
    frame f;
    vector<point> vertex; //多边形顶点集合
};
vector<Poly> polyset;

frame f_buffer[w + 1][h + 1];
int z_buffer[w + 1][h + 1], cntz;

typedef struct ET
{
    float x;
    float dx;
    float ymax;
    ET *next;
} AET, NET; //活性边表，新边表
AET *headAET;
NET *headNET[h + 5];
void clearET(ET *cur)
{
    while (cur != NULL)
    {
        ET *nxt = cur->next;
        delete cur;
        cur = nxt;
    }
}

void PolyScan(Poly poly)
{

    //确定扫描线最低和最高值
    int ymin = h, ymax = 0;
    for (auto i : poly.vertex)
        ymin = min(ymin, i.y), ymax = max(ymax, i.y);

    //初始化活性边表和新边表
    headAET = new AET;
    headAET->next = NULL;

    for (int i = ymin; i <= ymax; i++)
    {
        headNET[i] = new NET;
        headNET[i]->next = NULL;
    }
    //建立新边表NET
    for (int j = 0; j < poly.vertex.size(); j++)
    {                                                                //遍历多边形顶点(按顺序)
        int pre = (j - 1 + poly.vertex.size()) % poly.vertex.size(); //前一个点在poly.vertex中的下标
        int aft = (j + 1) % poly.vertex.size();                      //后一个点在poly.vertex中的下标
        if (poly.vertex[pre].y > poly.vertex[j].y)
        {
            //与前一个点构成的边是一条新的边
            NET *cur = new NET;
            cur->x = poly.vertex[j].x;
            cur->ymax = poly.vertex[pre].y;
            float DX = poly.vertex[pre].x - poly.vertex[j].x;
            float DY = poly.vertex[pre].y - poly.vertex[j].y;
            cur->dx = DX / DY;
            cur->next = headNET[poly.vertex[j].y]->next;
            headNET[poly.vertex[j].y]->next = cur;
        }
        if (poly.vertex[aft].y > poly.vertex[j].y)
        {
            //与后一个点构成的边是一条新的边
            NET *cur = new NET;
            cur->x = poly.vertex[j].x;
            cur->ymax = poly.vertex[aft].y;
            float DX = poly.vertex[aft].x - poly.vertex[j].x;
            float DY = poly.vertex[aft].y - poly.vertex[j].y;
            cur->dx = DX / DY;
            cur->next = headNET[poly.vertex[j].y]->next;
            headNET[poly.vertex[j].y]->next = cur;
        }
    }
    //通过活性边表AET来进行区域填充
    for (int i = ymin; i <= ymax; i++)
    {
        NET *curNET;
        AET *curAET, *preAET;
        //删除AET中到达ymax的边
        preAET = headAET;
        curAET = headAET->next;
        while (curAET)
        {
            if (curAET->ymax == i)
            {
                preAET->next = curAET->next;
                delete curAET;
                curAET = preAET->next;
            }
            else
            {
                preAET = preAET->next;
                curAET = curAET->next;
            }
        }

        //将NET中在y=i这一扫描线新的边用插入排序加入到AET中
        curNET = headNET[i]->next;
        while (curNET)
        {
            curAET = headAET;
            while (curAET->next != NULL && curNET->x > curAET->next->x)
                curAET = curAET->next;
            if (curAET->next != NULL && curNET->x == curAET->next->x && curNET->dx > curAET->next->dx)
                curAET = curAET->next;
            AET *tmp = new AET;
            tmp->dx = curNET->dx;
            tmp->ymax = curNET->ymax;
            tmp->x = curNET->x;
            tmp->next = curAET->next;
            curAET->next = tmp;

            curNET = curNET->next;
        }
        //以AET中的点两两配对的形式来进行填充
        curAET = headAET->next;
        while (curAET != NULL && curAET->next != NULL)
        {
            for (int x = (int)curAET->x; x < curAET->next->x; x++)
            {
                if (poly.z > z_buffer[x][i])
                {
                    f_buffer[x][i].r = poly.f.r;
                    f_buffer[x][i].g = poly.f.g;
                    f_buffer[x][i].b = poly.f.b;
                    z_buffer[x][i] = poly.z;
                }
            }
            curAET = curAET->next->next;
        }

        //更新AET中边的x
        curAET = headAET->next;
        while (curAET)
        {
            curAET->x += curAET->dx;
            curAET = curAET->next;
        }
    }

    clearET(headAET);
    headAET = NULL;
    for (int i = ymin; i <= ymax; i++)
        clearET(headNET[i]), headNET[i] = NULL;
}

void exec_z_buffer()
{
    //初始化f_buffer为背景色，z_buffer为无穷小
    for (int i = 0; i <= w; i++)
    {
        for (int j = 0; j <= h; j++)
        {
            f_buffer[i][j].r = 0;
            f_buffer[i][j].g = 0;
            f_buffer[i][j].b = 0;
            z_buffer[i][j] = -1e9;
        }
    }
    //扫描转换每个多边形，并更新f_buffer和z_buffer
    for (auto p : polyset)
    {
        PolyScan(p);
    }
    //转换完毕，根据f_buffer输出屏幕像素点
    for (int i = 0; i <= w; i++)
    {
        for (int j = 0; j <= h; j++)
        {
            frame frm = f_buffer[i][j];
            glBegin(GL_POINTS);
            glColor3f(frm.r, frm.g, frm.b);
            glVertex2f(i, j);
            glEnd();
        }
    }
}

void creatnewpoly()
{
    polyset.push_back(Poly());
    int last = polyset.size() - 1;
    polyset[last].z = ++cntz;
    polyset[last].f.r = randf();
    polyset[last].f.g = randf();
    polyset[last].f.b = randf();
}
void mymouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        point p(x, h - y);
        int last = polyset.size() - 1;
        polyset[last].vertex.push_back(p);
    } //左键确定多边形的顶点

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        exec_z_buffer();
        glFlush();
        creatnewpoly();
    } //右键填充

    if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        polyset.clear();
        cntz = 0;
        creatnewpoly();
        glFlush();
    } //中键清空
}
void myKeyboard(unsigned char key, int x, int y)
{
    if (key == 9)
    {
        for (int i = 0; i < polyset.size(); i++)
        {
            polyset[i].z = -polyset[i].z;
        }

        glClear(GL_COLOR_BUFFER_BIT);
        exec_z_buffer();
        glFlush();
        creatnewpoly();
    }
}
void display() {}

void Init()
{
    //设置颜色
    glClearColor(0.0, 0.0, 0.0, 0.0);
    //颜色过渡形式
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);

    cntz = 0;
    creatnewpoly();
    srand((int)time(0));
}
int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    //设置初始窗口的位置
    glutInitWindowPosition(100, 100);
    //设置初始窗口的大小
    glutInitWindowSize(w, h);
    //根据前面设置建立窗口，参数设置为变体

    glutCreateWindow("Experiment3");
    Init();
    //绘图时被调用的函数
    glutDisplayFunc(display);
    glutMouseFunc(mymouse);
    glutKeyboardFunc(myKeyboard);
    //进行消息循环，用于显示窗体，窗体关闭后自动退出循环
    glutMainLoop();
    return 0;
}