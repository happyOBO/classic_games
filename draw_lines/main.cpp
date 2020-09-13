#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>

GLsizei winW = 500, winH=500, boxSize = 50;
int TopLeftX, BottomRightX, TopLeftY, BottomRightY,colortype = 1;


void MyDisplay(){
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON);
    glColor3f(1.0,0.0,0.0);
        glVertex2i(winW - boxSize,winH);
        glVertex2i(winW - boxSize,winH - boxSize);
        glVertex2i(winW,winH - boxSize);
        glVertex2i(winW,winH);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.0,1.0,0.0);
        glVertex2i(winW - boxSize,winH - boxSize);
        glVertex2i(winW - boxSize,winH - boxSize * 2);
        glVertex2i(winW,winH - boxSize * 2);
        glVertex2i(winW,winH - boxSize);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.0,0.0,1.0);
        glVertex2i(winW - boxSize,winH - boxSize * 2);
        glVertex2i(winW - boxSize,winH - boxSize * 3);
        glVertex2i(winW,winH - boxSize * 3);
        glVertex2i(winW,winH - boxSize * 2);
    glEnd();
    glFlush();

}


void MyMouseClick(GLint button, GLint action, GLint xMouse,GLint yMouse){

    if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && (450 <xMouse && xMouse < 500 ) &&(450 < winH - yMouse && winH - yMouse <500))
    {
        colortype = 1;

    }
    else if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && (450 <xMouse && xMouse < 500 ) &&(400< winH - yMouse && winH - yMouse <450))
    {
        colortype = 2;

    }
    else if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN && (450 <xMouse && xMouse < 500 ) &&(350 < winH - yMouse && winH - yMouse <400))
    {
        colortype = 3;

    }
    else if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
    {
        TopLeftX = xMouse;
        TopLeftY = winH - yMouse;
    }
}

void  MyMouseMove(GLint xMouse,GLint yMouse){
        BottomRightX = xMouse;
        BottomRightY = winH - yMouse;

        glBegin(GL_LINES);
            if(colortype == 1) glColor3f(1.0,0.0,0.0);
            else if(colortype == 2) glColor3f(0.0,1.0,0.0);
            else if(colortype == 3) glColor3f(0.0,0.0,1.0);
            glVertex2i(TopLeftX,TopLeftY);
            glVertex2i(BottomRightX,BottomRightY);
        glEnd();

        TopLeftX =  BottomRightX;
        TopLeftY =  BottomRightY;
        glFlush();
        //glutPostRedisplay();



}

int main(int argc, char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(200,200);
    glutInitWindowSize(winW,winH);
    glutCreateWindow("Draw Line");
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,500.0,0.0,500.0);
    glutDisplayFunc(MyDisplay);
    glutMouseFunc(MyMouseClick);
    glutMotionFunc(MyMouseMove);
    glutMainLoop();
    return 0;
}
