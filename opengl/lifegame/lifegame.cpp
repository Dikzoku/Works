#include<iostream>
#include <GL/glut.h>
#include <cmath>
#include <ctime>
#include <Windows.h>
using namespace std;
const int w=600,h=600;
const int plen = 5;
const int weight = w/plen,height =h/plen;
const int sleeptime = 100;
int g[weight+5][height+5],tmpg[weight+5][height+5];
int check(int i,int j){
    if(i<0||j<0||i>=weight||j>=height) return 0;
    return g[i][j];
}
int check_roundalive(int i,int j){
    int cnt=0;
    cnt+=check(i-1,j-1);
    cnt+=check(i-1,j);
    cnt+=check(i-1,j+1);
    cnt+=check(i,j-1);
    cnt+=check(i,j+1);
    cnt+=check(i+1,j-1);
    cnt+=check(i+1,j);
    cnt+=check(i+1,j+1);
    return cnt;
}
void calcnext(){
    for(int i=0;i<weight;i++){
        for(int j=0;j<height;j++){
            int cnt=check_roundalive(i,j);
            tmpg[i][j] = g[i][j];
            if(cnt<2 || cnt>3) tmpg[i][j] = 0;
            else if(cnt == 3) tmpg[i][j] = 1;
        }
    }
    for(int i=0;i<weight;i++){
        for(int j=0;j<height;j++){
            g[i][j] = tmpg[i][j];
        }
    }
}
void drawall(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);
    glPointSize(5);
    glBegin(GL_POINTS);
    for(int i=0;i<weight;i++){
        for(int j=0;j<height;j++){
            if(g[i][j]){
                glVertex2f(i*plen, j*plen);
            }
        }
    }
    glEnd();
    glFlush();
}
void initg(){
    srand(time(0));
    for(int i=0;i<weight;i++){
        for(int j=0;j<height;j++){
            g[i][j] = rand() % 2;
        }
    }
}
bool cyclemode;
void myKeyboard(unsigned char key, int x, int y){
    if (key == 'r'){
        initg();
        drawall();
    }
    if (key == 'a'){
        cyclemode^=1;
    }
}
void mymouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        calcnext();
        drawall();
	}//左键确定多边形的顶点
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
    glClearColor(1, 1, 1, 1); 
    //颜色过渡形式
    glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);

    initg();
    drawall();
}
void myDisplay(void) {}
void mytimer(int value){
    if(cyclemode){
        calcnext();
        drawall();
    }
    glutTimerFunc(sleeptime,mytimer,0);
}
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    //设置初始窗口的位置
    glutInitWindowPosition(50, 50);
    //设置初始窗口的大小
    glutInitWindowSize(w, h);
    //根据前面设置建立窗口，参数设置为变体
    glutCreateWindow("Lifegame");
    Init();
    //改变窗体大小时进行图像重绘
    glutReshapeFunc(myReshape);
    //绘图时被调用的函数
    glutDisplayFunc(myDisplay);
    glutMouseFunc(mymouse);
    glutKeyboardFunc(myKeyboard);
    glutTimerFunc(sleeptime, mytimer, 0);
    //进行消息循环，用于显示窗体，窗体关闭后自动退出循环
    glutMainLoop();
	return 0;
}