#include<iostream>
#include <GL/glut.h>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
#include<list>
#include<Windows.h>
#include<cmath>
#include<string.h>
using namespace std;

const int w=1000,h=600;
const int K_deboor = 3;
struct point{
	float x, y;
	point(){}
	point(float _x, float _y)
		:x(_x), y(_y) {}
    point(int _x, int _y)
		:x(_x), y(_y) {}
};
list<point> vertex;
vector<point> point_to_draw;
void drawBigPixelf(float x,float y){
    glColor3f(0, 0, 1);
	glPointSize(5);
    glBegin(GL_POINTS);
	glVertex2f(x, y);
    glEnd();
    glFlush();
}
void drawControlPoint(){
    glColor3f(0, 0, 1); 
    glPointSize(5);
    glBegin(GL_POINTS);
    for(auto i : vertex){
        glVertex2f(i.x, i.y);
    }
    glEnd();
}
void drawControlPolygon(){
    glColor3f(0, 1, 0);
     glLineWidth(1);
    glBegin(GL_LINE_STRIP);
    for(auto i : vertex){
        glVertex2f(i.x, i.y);
    }
    glEnd();
}
void drawPointToDraw(){
    glColor3f(1, 0, 0);
    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
    for(auto i : point_to_draw){
        glVertex2f(i.x, i.y);
    }
    glEnd();
}
void deCasteljau(){
    glClear(GL_COLOR_BUFFER_BIT);
    drawControlPoint();
    drawControlPolygon();

    point_to_draw.clear();
    vector<point> p;
    int n = vertex.size() - 1;
    auto iver = vertex.begin();
    for(int i = 0; i <= n ; i++){
        // px[0][i] = vertex[i].x;
        // py[0][i] = vertex[i].y;
        p.push_back(*iver);
        iver++;
    }

    for(float t = 0; t <= 1;t += 0.001){
        for(int k = 1; k <= n; k++){
            for(int i = 0; i <= n-k; i++){
                // px[k][i] = (1-t)*px[k-1][i] + t*px[k-1][i+1];
                // py[k][i] = (1-t)*py[k-1][i] + t*py[k-1][i+1];
                p[i].x = (1-t)*p[i].x + t*p[i+1].x;
                p[i].y = (1-t)*p[i].y + t*p[i+1].y;

            }
        }
        //point p(px[n][0], py[n][0]);
        point_to_draw.push_back(p[0]);
    }
    drawPointToDraw();
    glFlush();
}


void deBoor(int k){
    glClear(GL_COLOR_BUFFER_BIT);
    drawControlPoint();
    drawControlPolygon();

    point_to_draw.clear();
    
    vector<point> p;
    int n = vertex.size() - 1;
    for(int i=0;i<=n;i++)  p.push_back(point(0,0));

    vector<float> t;
    float step=1.0/(n+k),nowt=0;
    t.push_back(0);
    for(int i=1;i<=n+k;i++){
        nowt+=step;
        t.push_back(nowt);
    }

    auto stver=vertex.begin();
    for(int j=k-1;j<=n;j++,stver++){
        for(float pt = t[j]; pt < t[j+1];pt += 0.001){
            auto iver = stver;
            for(int i=j-k+1;i<=j;i++){
                // px[0][i] = vertex[i].x;
                // py[0][i] = vertex[i].y;
                p[i] = *iver;
                iver++;
            }
            for(int r=1;r<=k-1;r++){
                //for(int i=j-k+r+1;i<=j;i++){
                    // p[r][i].x =(pt - t[i])/(t[i+k-r] - t[i]) * p[r-1][i].x 
                    //         + (t[i+k-r] - pt)/(t[i+k-r] - t[i]) * p[r-1][i-1].x;
                    // p[r][i].y =(pt - t[i])/(t[i+k-r] - t[i]) * p[r-1][i].y 
                    //         + (t[i+k-r] - pt)/(t[i+k-r] - t[i]) * p[r-1][i-1].y;
                //}
                for(int i=j;i>=j-k+r+1;i--){
                    p[i].x =(pt - t[i])/(t[i+k-r] - t[i]) * p[i].x 
                             + (t[i+k-r] - pt)/(t[i+k-r] - t[i]) * p[i-1].x;
                    p[i].y =(pt - t[i])/(t[i+k-r] - t[i]) * p[i].y 
                             + (t[i+k-r] - pt)/(t[i+k-r] - t[i]) * p[i-1].y;
                }
            }
            //point_to_draw.push_back(p[k-1][j])
            point_to_draw.push_back(p[j]);
        }
    } 
    drawPointToDraw();
    glFlush();
}



int use_option;
char draw_option;
list<point>::iterator chs_ver;
list<point>::iterator getpoint(float x,float y){
    float accuracy = 5;
    for(auto iver = vertex.begin();iver!=vertex.end();iver++){
        if((abs(iver->x - x ) < accuracy) && (abs(iver->y - y ) < accuracy)){
            return iver;
        }
    }
    return vertex.end();
}
void mymouse(int button, int state, int x, int y){
    y = h - y;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        chs_ver = getpoint(x,y);
	}
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
        if(draw_option == 'i'){
            drawBigPixelf(x, y);
            if(chs_ver != vertex.end()) chs_ver++;
		    vertex.insert(chs_ver , point(x, y));
        }
        if(draw_option == 'd'){
            if(chs_ver != vertex.end())
		        vertex.erase(chs_ver);
        }
        if(draw_option == 'm'){
            if(chs_ver != vertex.end()){
                chs_ver = vertex.erase(chs_ver);
                vertex.insert(chs_ver , point(x, y));
            }
        }
        if(use_option == 0) deCasteljau();
        else deBoor(K_deboor);
	}

}
void myKeyboard(unsigned char key, int x, int y){
    if (key == 9){
        use_option^=1;
    }
    if(key == 'i'){
        draw_option = 'i';
    }
    if(key == 'd'){
        draw_option = 'd';
    }
    if(key == 'm'){
        draw_option = 'm';
    }
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
    draw_option = 'i';
    use_option = 0;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    //设置初始窗口的位置
    glutInitWindowPosition(200, 50);
    //设置初始窗口的大小
    glutInitWindowSize(w, h);
    //根据前面设置建立窗口，参数设置为变体
    glutCreateWindow("Experiment5");
    Init();
    //绘图时被调用的函数
    glutDisplayFunc(display);
    glutMouseFunc(mymouse);
    glutKeyboardFunc(myKeyboard);

    //进行消息循环，用于显示窗体，窗体关闭后自动退出循环
    glutMainLoop();
	return 0;
}