#include<iostream>
#include <GL/glut.h>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
#include<Windows.h>
using namespace std;

const int w=500,h=500;

struct point{
	int x, y;
	point(){}
	point(int _x, int _y)
		:x(_x), y(_y) {}
};
vector<point> vertex;//多边形顶点集合

typedef struct ET{
	float x;
	float dx;
	float ymax;
	ET* next;
}AET,NET;//活性边表，新边表
AET* headAET;
NET* headNET[h+5];
void drawpixelf(float x,float y){
    glColor3f(1, 0, 0);
	glPointSize(1);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
    glEnd();
//    glFlush();
}
void drawbigpixelf(float x,float y){
    glColor3f(1, 0, 0);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
    glEnd();
    glFlush();
}
bool newgl;
void clearET(ET* cur){
    while(cur!=NULL){
        ET* nxt=cur->next;
        delete cur;
        cur=nxt;
    }
}
void clear(){
    newgl=0;
    vertex.clear();
    clearET(headAET);
    headAET=NULL;
    for(int i=0;i<=h;i++) clearET(headNET[i]),headNET[i]=NULL;
}
void PolyScan(){
    //确定扫描线最低和最高值
    int ymin=h,ymax=0;
    for(auto i:vertex) ymin=min(ymin,i.y),ymax=max(ymax,i.y);
    //初始化活性边表和新边表
    headAET=new AET;
    headAET->next=NULL;
    headNET[h+5];
    for(int i=ymin;i<=ymax;i++){
        headNET[i] = new NET;
        headNET[i]->next = NULL;
    }
    //建立新边表NET
    for(int j=0;j<vertex.size();j++){//遍历多边形顶点(按顺序)
        int pre=(j-1+vertex.size())%vertex.size();//前一个点在vertex中的下标
        int aft=(j+1)%vertex.size();//后一个点在vertex中的下标
        if (vertex[pre].y > vertex[j].y){
            //与前一个点构成的边是一条新的边
            NET* cur=new NET;
            cur->x = vertex[j].x;
            cur->ymax = vertex[pre].y;
            float DX = vertex[pre].x-vertex[j].x;
            float DY = vertex[pre].y-vertex[j].y;
            cur->dx = DX/DY;
            cur->next = headNET[vertex[j].y]->next;
            headNET[vertex[j].y]->next = cur;
        }
        if (vertex[aft].y > vertex[j].y){
            //与后一个点构成的边是一条新的边
            NET* cur = new NET;
            cur->x = vertex[j].x;
            cur->ymax = vertex[aft].y;
            float DX = vertex[aft].x-vertex[j].x;
            float DY = vertex[aft].y-vertex[j].y;
            cur->dx = DX/DY;
            cur->next = headNET[vertex[j].y]->next;
            headNET[vertex[j].y]->next = cur;
        }
    }
    //通过活性边表AET来进行区域填充
    for(int i=ymin;i<=ymax;i++){
        NET *curNET;
        AET *curAET,*preAET;
        //删除AET中到达ymax的边
        preAET=headAET;
        curAET=headAET->next;
        while (curAET){
			if (curAET->ymax == i){
				preAET->next = curAET->next;
				delete curAET;
				curAET = preAET->next;
			}else{
				preAET = preAET->next;
				curAET = curAET->next;
			}
		}

        //将NET中在y=i这一扫描线新的边用插入排序加入到AET中
        curNET=headNET[i]->next;
		while(curNET){
            curAET= headAET;
			while (curAET->next != NULL && curNET->x > curAET->next->x)
				curAET = curAET->next;
            if(curAET->next != NULL && curNET->x == curAET->next->x
              &&curNET->dx > curAET->next->dx)
                curAET = curAET->next;
            AET *tmp=new AET;
            tmp->dx=curNET->dx;
            tmp->ymax=curNET->ymax;
            tmp->x=curNET->x;
            tmp->next=curAET->next;
            curAET->next=tmp;

			curNET = curNET->next;
		}
        //以AET中的点两两配对的形式来进行填充
        curAET=headAET->next;
		while (curAET!= NULL && curAET->next != NULL){
			for (float j = curAET->x; j < curAET->next->x; j++){
                drawpixelf(j,i);
			}
			curAET=curAET->next->next;
		}


        //更新AET中边的x
        curAET=headAET->next;
        while(curAET){
            curAET->x+=curAET->dx;
            curAET=curAET->next;
        }

        glFlush();
    }
}

void mymouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        if(!newgl){
            glClear(GL_COLOR_BUFFER_BIT);
            newgl=1;
        }
		drawbigpixelf(x, h - y);
		point p(x, h - y);
		vertex.push_back(p);
	}//左键确定多边形的顶点

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
        PolyScan();
        glFlush();
        clear();
	}//右键填充

	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN){
		glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
        clear();
	}//中键清空
}

void display(){}

void Init(){ 
    //设置颜色 
    glClearColor(0.0, 0.0, 0.0, 0.0); 
    //颜色过渡形式
    glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    //设置初始窗口的位置
    glutInitWindowPosition(100, 100);
    //设置初始窗口的大小
    glutInitWindowSize(w, h);
    //根据前面设置建立窗口，参数设置为变体
    glutCreateWindow("Experiment2");
    Init();
    //绘图时被调用的函数
    glutDisplayFunc(display);
    glutMouseFunc(mymouse);
    
    //进行消息循环，用于显示窗体，窗体关闭后自动退出循环
    glutMainLoop();
	return 0;
}