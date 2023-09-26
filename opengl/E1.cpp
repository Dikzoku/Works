#include<iostream>
#include <GL/glut.h>
#include <cmath>
using namespace std;
const int w=600,h=600;
int mx0,my0,mx1,my1;
unsigned char option='1';
bool clearoption=0;

void DDALine(int x0,int y0,int x1,int y1){
    glBegin(GL_POINTS);
    glColor3f(255,255,255);
    float k=1.0*(y1-y0)/(x1-x0);
    if(abs(k)<=1){//abs(k)<=1
        if(x0>x1){
            swap(x0,x1);
            swap(y0,y1);
        }
        float y=y0;
        for(int x=x0;x<=x1;x++){
            glVertex2i(x,int(y+0.5));
            y=y+k;
        }
    }else{//abs(k)>1
        if(y0>y1){
            swap(x0,x1);
            swap(y0,y1);
        }
        float x=x0;
        k=1/k;
        for(int y=y0;y<=y1;y++){
            glVertex2i(int(x+0.5),y);
            x=x+k;
        }
    }
    glEnd();
}
void IntegerBresenhamline(int x0,int y0,int x1,int y1){
    glBegin(GL_POINTS);
    glColor3f(0,255,0);
    float k=1.0*(y1-y0)/(x1-x0);
    if(abs(k)<=1){
        if(x0>x1){
            swap(x0,x1);
            swap(y0,y1);
        }
        int x,y,dx,dy,e;
        dx=x1-x0,dy=y1-y0;
        x=x0,y=y0;
        if(k>=0){//abs(k)<=1且k>=0
            e=-dx;
            for(int i=0;i<=dx;i++){
                glVertex2i(x,y);
                x++,e=e+2*dy;
                if(e>=0){
                    y++,e=e-2*dx;
                }
            }
        }else{//abs(k)<=1且k<0
            e=dx;
            for(int i=0;i<=dx;i++){
                glVertex2i(x,y);
                x++,e=e+2*dy;
                if(e<=0){
                    y--,e=e+2*dx;
                }
            }
        }
    }else{
        if(y0>y1){
            swap(x0,x1);
            swap(y0,y1);
        }
        int x,y,dx,dy,e;
        dx=x1-x0,dy=y1-y0;
        x=x0,y=y0;
        if(k>=0){//abs(k)>1且k>=0
            e=-dy;
            for(int i=0;i<=dy;i++){
                glVertex2i(x,y);
                y++,e=e+2*dx;
                if(e>=0){
                    x++,e=e-2*dy;
                }
            }
        }else{//abs(k)>1且k<0
            e=dy;
            for(int i=0;i<=dy;i++){
                glVertex2i(x,y);
                y++,e=e+2*dx;
                if(e<=0){
                    x--,e=e+2*dy;
                }
            }
        }
    }
    glEnd();
}

void CirclePoints(int cx,int cy,int x,int y){
    glBegin(GL_POINTS);
    glColor3f(255,0,0);
    glVertex2i(cx+x,cy+y); glVertex2i(cx+y,cy+x);
    glVertex2i(cx-x,cy+y); glVertex2i(cx+y,cy-x);
    glVertex2i(cx+x,cy-y); glVertex2i(cx-y,cy+x);
    glVertex2i(cx-x,cy-y); glVertex2i(cx-y,cy-x);
    glEnd();
}
void MidPointCircle(int cx,int cy,int r){
    int x,y;
    int d;//float d;
    x=0,y=r,d=5-4*r;//d=1.25-r;
    CirclePoints(cx,cy,x,y);
    while(x<=y){
        if(d<0){
            d+=8*x+12;
        }else{
            d+=8*(x-y)+20;
            y--;
        }
        x++;
        CirclePoints(cx,cy,x,y);
    }
}
void myReshape(int w, int h) {
    //glViewport负责把视景体截取的图像按照怎样的高和宽显示到屏幕上
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);  
    //将当前矩阵指定为投影矩阵
    glMatrixMode(GL_PROJECTION);
    //把矩阵设为单位矩阵
    glLoadIdentity();  
    //让中心坐标（0，0）变成窗口的左下角
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}
void Init(){ 
    //设置颜色 
    glClearColor(0.0, 0.0, 0.0, 0.0); 
    //颜色过渡形式
    glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}
void myMouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON&&state == GLUT_DOWN) {
		mx0=x,my0=h-y;//按下左键确定线段及圆的直径起点
	}
    if (button == GLUT_LEFT_BUTTON&&state == GLUT_UP) {
		mx1=x,my1=h-y;//松开左键确定线段及圆的直径终点
	}
    if (button == GLUT_RIGHT_BUTTON&&state == GLUT_DOWN){
        clearoption^=1;//单击右键来切换是否只保留最后一次画图操作
    }
}
void myDisplay(void) {
    if(clearoption) glClear(GL_COLOR_BUFFER_BIT);
    if(option=='1') DDALine(mx0,my0,mx1,my1);//按下键盘数字1运行DDA画线算法
    if(option=='2') IntegerBresenhamline(mx0,my0,mx1,my1);//按下键盘数字2运行Bresenham画线算法
    if(option=='3'){//按下键盘数字3运行中点画圆算法
        int r= sqrt((mx0-mx1)*(mx0-mx1)+(my0-my1)*(my0-my1))/2;
        MidPointCircle((mx0+mx1)/2,(my0+my1)/2,r);
    }
    glFlush();//强制刷新缓冲，保证绘图命令将被执行
}
void myKeyboard(unsigned char key, int x, int y){
    option=key;
}
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    //设置初始窗口的位置
    glutInitWindowPosition(50, 50);
    //设置初始窗口的大小
    glutInitWindowSize(w, h);
    //根据前面设置建立窗口，参数设置为变体
    glutCreateWindow("Experiment1");
    Init();
    //改变窗体大小时进行图像重绘
    glutReshapeFunc(myReshape);
    //绘图时被调用的函数
    glutDisplayFunc(myDisplay);
    glutMouseFunc(myMouse);
    glutKeyboardFunc(myKeyboard);
    
    //进行消息循环，用于显示窗体，窗体关闭后自动退出循环
    glutMainLoop();
	return 0;
}