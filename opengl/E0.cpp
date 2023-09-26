#include<GL/glut.h>
#define EXIT_SUCCESS 0
#include<stdio.h>
#include<math.h>
bool mouseLeftDown;
bool mouseRightDown;    
float mouseX, mouseY;   
float triangleAngleX=0; 
float triangleAngleY=0; 

float CircleAngleX=0;   
float CircleAngleY=0; 

float PI = 3.415926535;

float triangleBiasX = 0.5;
float triangleBiasY = -0.5;

int selected = 0;   
float circleBiasX = -0.5;
float circleBiasY = 0.5;

int added_z_mode =-1;

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
}


void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    if (w <= h)

        glOrtho(-1.5, 1.5, -1.5 * (GLfloat)h / (GLfloat)w, 1.5 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);

    else

        glOrtho(-1.5 * (GLfloat)w / (GLfloat)h, 1.5 * (GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 0);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);

   
    glPushMatrix();
  
    glTranslatef(circleBiasX, circleBiasY, 0);                          

    glRotatef(CircleAngleX+CircleAngleY, 0, 0, 1);

    float R = 0.4f;
    int n=80;
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++)                                        
    {
        glColor3f(1,0,0);
        glVertex2f(R * cos(2* PI * i / n), R * sin(2 * PI * i / n));
    }
    glEnd();
    glTranslatef(-circleBiasX, -circleBiasY, 0);                        
    glPopMatrix();                                                      



    glPushMatrix();
    glTranslatef(triangleBiasX, triangleBiasY, 0);                    


    glRotatef(triangleAngleX+triangleAngleY, 0, 0, 1);


    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0, 0);
    glVertex3f(0, 2.0 / 4, 0);
    glColor3f(1, 0, 0);
    glVertex3f(-1.732 / 4, -1.0 / 4, 0);
    glColor3f(1, 0, 0);
    glVertex3f( 1.732 / 4, -1.0 / 4, 0);
    glEnd();

    glTranslatef(-triangleBiasX, -triangleBiasY, 0);                    // 复位
    glPopMatrix();
    glutSwapBuffers();
}
int saveStack = 0;
int firstSaveFlag = -1;
void keyboard(unsigned char key, int x, int y)

{
    switch (key) {
    case 033: case 'q': case 'Q':
        exit(EXIT_SUCCESS);
        break;
    }
}


void mouse_process(int button, int state, int x, int y)
{
    mouseX = x;
    mouseY = y;
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            mouseLeftDown = true;
        }
        else if (state == GLUT_UP)
            mouseLeftDown = false;
    }

    else if (button == GLUT_RIGHT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            mouseRightDown = true;
        }
        else if (state == GLUT_UP)
            mouseRightDown = false;
    }

    float Y = -10.0 * (x- 0.5 * glutGet(GLUT_WINDOW_WIDTH)) / 3.0 / glutGet(GLUT_WINDOW_WIDTH);
    float X = -10.0 * (y - 0.5 * glutGet(GLUT_WINDOW_HEIGHT)) / 3.0 / glutGet(GLUT_INIT_WINDOW_HEIGHT);
    float mouseToTriangle = (triangleBiasX - X) * (triangleBiasX - X) + (triangleBiasY - Y) * (triangleBiasY - Y);
    float mouseToCircle = (circleBiasX - X) * (circleBiasX - X) + (circleBiasY - Y) * (circleBiasY - Y);
    if (mouseToTriangle < 0.25 && mouseToCircle < 0.11)selected = 1;
    else if (mouseToTriangle < 0.25)selected = 1;
    else if (mouseToCircle < 0.11)selected = 2;
    else selected = 0;
}

void mouse_process_active(int x, int y)
{

    if (mouseLeftDown){
        if (selected==1) {
             triangleBiasY -= 3*((float)x - mouseX)/ glutGet(GLUT_WINDOW_WIDTH);
             triangleBiasX -= 3*((float)y - mouseY)/ glutGet(GLUT_WINDOW_HEIGHT);
        }
        else if (selected == 2) {
            circleBiasY -= 3 * ((float)x - mouseX) / glutGet(GLUT_WINDOW_WIDTH);
            circleBiasX -= 3 * ((float)y - mouseY) / glutGet(GLUT_WINDOW_HEIGHT);
        }

        mouseX = x;
        mouseY = y;
    }
    if(mouseRightDown)
    {   
        if (selected == 1) {
            triangleAngleY += (y - mouseY) * 0.2f;
            triangleAngleX += (x - mouseX) * 0.2f;
        }
        else if (selected == 2) {
            CircleAngleY += (y - mouseY) * 0.2f;
            CircleAngleX += (x - mouseX) * 0.2f;
        }
        mouseX = x;
        mouseY = y;
    }

    glutPostRedisplay();

}
void mouse_process_passtive(int x, int y) {}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(512, 512);
    glutCreateWindow("E0");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    // later Edition
    glutMouseFunc(mouse_process);
    glutMotionFunc(mouse_process_active);
    glutPassiveMotionFunc(mouse_process_passtive);


    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}