#include<iostream>
#include <GL/glut.h>
#include <cmath>
#include <ctime>
#include <Windows.h>
#include <list>
#include <vector>
#include <ctime>
using namespace std;
const float w=600,h=600;
const float plen = 20;
const int onestep_time = 100; // ms

const float weight = w/plen,height =h/plen;
struct point{
    int x,y;
    point(){}
    point(int xx,int yy){
        x=xx,y=yy;
    }
};
class snake{
    public:
        snake(int w,int h){
            weight=w,height=h;
            newgame();
        }
        ~snake(){}

        bool move();
        void setdir(int dir);
        void newgame();

        vector<point> body;
        point food;
    private:
        
        void setfood();
        int towards;// 0 1 2 3 w a s d
        int newtowards;
        int dirx[4]={0,-1,0,1},diry[4]={-1,0,1,0};

        int weight,height;
};
void snake::newgame(){
    srand(time(0));
    newtowards = towards = 0;
    body.clear();
    body.push_back(point(weight/2,height/2));
    body.push_back(point(weight/2,height/2+1));
    body.push_back(point(weight/2,height/2+2));
    setfood();
}
void snake::setdir(int dir){
    if((dir + towards) % 2) newtowards = dir;
}
void snake::setfood(){
    int maxn = weight*height - body.size();
    int setp = rand() % maxn;
    for(int x=0;x<weight;x++){
        for(int y=0;y<height;y++){
            bool isbody = 0;
            for(int i=0 ;i<body.size();i++){
                if(x == body[i].x && y == body[i].y){
                    isbody = 1; break;
                }
            }
            if(isbody) continue;
            if(setp == 0){
                food.x=x; food.y=y;
                return;
            }else setp--;
        }
    }
}
bool snake::move(){
    towards = newtowards;
    point tail = body[body.size()-1];
    for(int i=body.size()-1;i>0;i--) body[i]=body[i-1];
    body[0].x =  body[0].x + dirx[towards];
    body[0].y =  body[0].y + diry[towards];
    body[0].x = (body[0].x+weight) % weight;
    body[0].y = (body[0].y+height) % height;

    if(body[0].x == food.x && body[0].y == food.y){
        body.push_back(tail);
        setfood();
    }

    for(int i=1 ;i<body.size();i++){
        if(body[0].x == body[i].x && body[0].y == body[i].y) return 0;
    }
    return 1;
}
snake snk(weight,height);
bool pause;
bool gameend;
void drawall(){
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(plen);
    glBegin(GL_POINTS);
    glColor3f(0, 1, 0);
    glVertex2f(snk.food.x*plen + plen/2, (height - snk.food.y)*plen - plen/2);
    if(!gameend) glColor3f(0, 0, 0);
    else glColor3f(1, 0, 0);
    for(int i=0;i<snk.body.size();i++){
        glVertex2f(snk.body[i].x*plen + plen/2, (height - snk.body[i].y)*plen - plen/2);
    }
    glEnd();
    glFlush();
}
void myKeyboard(unsigned char key, int x, int y){
    if (key == 'w' || key == 'W'){
        snk.setdir(0);
    }
    if (key == 'a' || key == 'A'){
        snk.setdir(1);
    }
    if (key == 's' || key == 'S'){
        snk.setdir(2);
    }
    if (key == 'd' || key == 'D'){
        snk.setdir(3);
    }
    if (key == 'p' || key == 'P'){
        pause^=1;
    }
    if (key == 32){
        pause^=1;
    }
    if (key == 'r' || key == 'R'){
        snk.newgame();
        gameend = 0;
    }
}
void mySpecialKey(int key,int x,int y){
    if (key == GLUT_KEY_UP){
        snk.setdir(0);
    }
    if (key == GLUT_KEY_LEFT){
        snk.setdir(1);
    }
    if (key == GLUT_KEY_DOWN){
        snk.setdir(2);
    }
    if (key == GLUT_KEY_RIGHT){
        snk.setdir(3);
    }
}
void mytimer(int value){
    if(!pause && !gameend ){
        if(snk.move() == 0){
            gameend = 1;
        }
        drawall();
    }
    glutTimerFunc(onestep_time,mytimer,0);
}
void mymouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
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
    glClearColor(1, 1, 1, 1); 
    //颜色过渡形式
    glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);

}
void myDisplay(void) {}
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    //设置初始窗口的位置
    glutInitWindowPosition(50, 50);
    //设置初始窗口的大小
    glutInitWindowSize(w, h);
    //根据前面设置建立窗口，参数设置为变体
    glutCreateWindow("Snake");
    Init();
    //改变窗体大小时进行图像重绘
    glutReshapeFunc(myReshape);
    //绘图时被调用的函数
    glutDisplayFunc(myDisplay);
    glutMouseFunc(mymouse);
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecialKey);
    glutTimerFunc(onestep_time, mytimer, 0);
    //进行消息循环，用于显示窗体，窗体关闭后自动退出循环
    glutMainLoop();
	return 0;
}