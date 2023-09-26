#include<iostream>
#include <GL/glut.h>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
#include<list>
#include<map>
#include<Windows.h>
#include<cmath>
#include<cstring>
using namespace std;

const int w=1000,h=600;
const int K_deboor = 3;
const int MAXPOINTS =1000;
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
map<float,int> t_index;
void drawAll(){
    glClear(GL_COLOR_BUFFER_BIT);

    //drawControlPoint
    glColor3f(0, 0, 1); 
    glPointSize(5);
    glBegin(GL_POINTS);
    for(auto i : vertex){
        glVertex2f(i.x, i.y);
    }
    glEnd();

    //drawControlPolygon
    glColor3f(0, 1, 0);
    glLineWidth(1);
    glBegin(GL_LINE_STRIP);
    for(auto i : vertex){
        glVertex2f(i.x, i.y);
    }
    glEnd();

    //drawPointToDraw
    glColor3f(1, 0, 0);
    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
    for(auto i : point_to_draw){
        glVertex2f(i.x, i.y);
    }
    glEnd();
    glFlush();
}
void deCasteljau(){
    point_to_draw.clear();
    int n = vertex.size() - 1;
    vector<point> p(vertex.size());

    for(float t = 0; t <= 1;t += 0.001){
        //k=0
        auto iver = vertex.begin();
        for(int i = 0; i <= n ; i++){
            p[i] = *iver;
            iver++;
        }
        //k>0
        for(int k = 1; k <= n; k++){
            for(int i = 0; i <= n-k; i++){
                p[i].x = (1-t)*p[i].x + t*p[i+1].x;
                p[i].y = (1-t)*p[i].y + t*p[i+1].y;

            }
        }
        point_to_draw.push_back(p[0]);
    }
    drawAll();
}

char use_option;
//use_option='1' Bezier曲线
//use_option='2' 均匀B样条曲线
//use_option='3' 准均匀B样条曲线
vector<float> t;
void deBoor_draw(int k,int j); //绘制[ t_j , t_{j+1} )这一段曲线上的点
void set_t(int k,int n){
    t.clear();
    float step=1.0/(n+k),nowt=0;
    t.push_back(0);
    for(int i=1;i<=n+k;i++){
        nowt+=step;
        t.push_back(nowt);
    }

    point_to_draw.clear();
    t_index.clear();
    for(int j=k-1;j<=n;j++){
        for(float pt = t[j]; pt < t[j+1];pt += 0.001){
            point_to_draw.push_back(point(0,0));
            t_index[pt] = point_to_draw.size()-1;
        }
    }
}
void deBoor_init(int k){
    
    int n = vertex.size() - 1;
    if(use_option == '3') n = n + 2*(k-1);//开头末尾各多了k-1个元素
    set_t(k,n);
    
    for(int j=k-1;j<=n;j++){
        deBoor_draw(k,j);
    }
    drawAll();
}

void deBoor_draw(int k,int j){ //绘制[ t_j , t_{j+1} )这一段曲线上的点
    vector<point> p(vertex.size() + 2*(k-1));
    auto stiver = vertex.begin();
    if(use_option=='3') for(int i = k-1 + (k-1); i < j; i++) stiver++;//前k-1个点是额外的0号点
    else if(use_option=='2') for(int i = k-1; i < j; i++) stiver++;
    for(float pt = t[j]; pt < t[j+1];pt += 0.001){
        //r==0
        auto iver = stiver;
        for(int i=j-k+1;i<=j;i++){
            p[i] = *iver;
            if(use_option=='3'){
                if(i >= k-1) iver++; //前k-1个点都用vertex中的0号点
                if(iver==vertex.end()) iver--; //后k-1个点都用vertex中的最后一个点
            }else if(use_option=='2'){
                iver++;
            }
        }
        //r>0
        for(int r=1;r<=k-1;r++){
            for(int i=j;i>=j-k+r+1;i--){
                p[i].x =(pt - t[i])/(t[i+k-r] - t[i]) * p[i].x 
                            + (t[i+k-r] - pt)/(t[i+k-r] - t[i]) * p[i-1].x;
                p[i].y =(pt - t[i])/(t[i+k-r] - t[i]) * p[i].y 
                            + (t[i+k-r] - pt)/(t[i+k-r] - t[i]) * p[i-1].y;
            }
        }
        point_to_draw[t_index[pt]] = p[j];
    }
}

char act_option;
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
void act_deCasteljau(int x,int y){
    if(act_option == 'i'){
        if(chs_ver != vertex.end()) chs_ver++;
        vertex.insert(chs_ver , point(x, y));
    }
    if(act_option == 'd'){
        if(chs_ver == vertex.end()) return;
        vertex.erase(chs_ver);
    }
    if(act_option == 'm'){
        if(chs_ver == vertex.end()) return;
        chs_ver = vertex.erase(chs_ver);
        vertex.insert(chs_ver , point(x, y));
    }
    deCasteljau();
}
void chg_deBoor(int chg_point){
    int st,ed;
    if(use_option=='2'){
        st=max(chg_point,K_deboor-1);
        ed=min(chg_point+K_deboor-1,(int)vertex.size()-1);
    }else if(use_option=='3'){
        st=chg_point + (K_deboor-1);//前面加了k-1个点
        ed=chg_point+K_deboor-1 + (K_deboor-1); //后面也加了k-1个点,ed最多可以到n+2(k-1)
    }
    for(int j=st; j<=ed; j++){
        deBoor_draw(K_deboor,j);
    }
    drawAll();
}
void act_deBoor(int x,int y){
    int chg_point = 0;
    for(auto i =vertex.begin();i!=chs_ver;i++) chg_point++;
    if(act_option == 'i'){
        if(chs_ver != vertex.end()) chs_ver++,chg_point++;
        chs_ver = vertex.insert(chs_ver,point(x,y));

        deBoor_init(K_deboor);
    }
    if(act_option == 'd'){
        if(chs_ver == vertex.end()) return;
        chs_ver = vertex.erase(chs_ver);

        deBoor_init(K_deboor);
    }
    if(act_option == 'm'){
        if(chs_ver == vertex.end()) return;
        chs_ver = vertex.erase(chs_ver);
        chs_ver = vertex.insert(chs_ver , point(x, y));

        chg_deBoor(chg_point);
    }
}
void mymouse(int button, int state, int x, int y){
    y = h - y;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        chs_ver = getpoint(x,y);
	}
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
        if(use_option == '1') act_deCasteljau(x,y);
        else act_deBoor(x,y);
	}
}
void myKeyboard(unsigned char key, int x, int y){
    if (key == '1'||key == '2'|| key=='3'){
        use_option = key;
        if(use_option=='1') deCasteljau();
        else deBoor_init(K_deboor);
    }
    if(key == 'i'){
        act_option = 'i';
    }
    if(key == 'd'){
        act_option = 'd';
    }
    if(key == 'm'){
        act_option = 'm';
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
    act_option = 'i';
    use_option = '1';

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