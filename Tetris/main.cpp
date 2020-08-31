
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <windows.h>
//#include <Turboc.h>
#include <math.h>

GLfloat width = 5.0;
GLfloat height = 8.0;
bool isCube[19][29];
GLdouble cubesize = 0.5;
GLfloat x_Rotate = 0.0;
GLfloat x_location = 0.0;
float time_trans = 0.0;
int objectShape = 1;
GLfloat CubeLocate[4][2];
GLfloat yMinXlocate[4];
GLfloat max_cube[19];
bool init = true;


void line()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glBegin(GL_LINES);
    glColor3f(1.0,0.0,0.0);
    glVertex3f(-100.0,0.0,0.0);
    glVertex3f(100.0,0.0,0.0);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0,1.0,0.0);
    glVertex3f(0.0,100.0,0.0);
    glVertex3f(0.0,-100.0,0.0);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0,0.0,1.0);
    glVertex3f(0.0,0.0,100.0);
    glVertex3f(0.0,0,-100.0);
    glEnd();
    glPopMatrix();
}
void CheckMax()
{
        for(int i = 0; i<19;i++)
            {
                for(int j = 0; j<29;j++)
                {

                    if(isCube[i][j])
                    {
                        if(max_cube[i]<((float)j/2 - 12.0 + cubesize))
                        {
                            printf("max : %f->%f",max_cube[i],j/2-12.0);
                            max_cube[i] = (float)j/2 - 12.0 + cubesize;
                        }
                    }
                }

            }
}

void MyKeyboard(unsigned char key, int p, int k)
{
    switch (key) {
        case 'd':
            if(x_location < width - cubesize)
            {
            CubeLocate[0][0] += cubesize;
            CubeLocate[1][0] += cubesize;
            CubeLocate[2][0] += cubesize;
            CubeLocate[3][0] += cubesize;
            x_location=x_location+cubesize;
            }
        break;
        case 'a':
            if(x_location > -1.0 * width + cubesize)
            {
            CubeLocate[0][0] -= cubesize;
            CubeLocate[1][0] -= cubesize;
            CubeLocate[2][0] -= cubesize;
            CubeLocate[3][0] -= cubesize;
                x_location=x_location-cubesize;
            }
        break;
        case 32:
            if(objectShape == 0)
            {
                if(x_Rotate == 270.0) x_Rotate = 0.0;
                else x_Rotate +=90.0;

                if(45.0 <= x_Rotate && x_Rotate <= 135.0)
                {
                    //CubeLocate[0][0] = CubeLocate[0][0] -cubesize;
                    //CubeLocate[0][1] = CubeLocate[0][1] -cubesize;
                    CubeLocate[1][0] = CubeLocate[1][0] - cubesize;
                    CubeLocate[1][1] = CubeLocate[1][1] - cubesize;
                    CubeLocate[2][0] = CubeLocate[2][0] -2*cubesize;
                    CubeLocate[2][1] = CubeLocate[2][1] -2*cubesize;
                    CubeLocate[3][0] = CubeLocate[3][0] -3*cubesize;
                    CubeLocate[3][1] = CubeLocate[3][1] -3*cubesize;
                }
                else if(135.0 <= x_Rotate && x_Rotate <= 225.0)
                {
                    //CubeLocate[0][0] = CubeLocate[0][0] -cubesize;
                    //CubeLocate[0][1] = CubeLocate[0][1] -cubesize;
                    CubeLocate[1][0] = CubeLocate[1][0] + cubesize;
                    CubeLocate[1][1] = CubeLocate[1][1] - cubesize;
                    CubeLocate[2][0] = CubeLocate[2][0] +2*cubesize;
                    CubeLocate[2][1] = CubeLocate[2][1] -2*cubesize;
                    CubeLocate[3][0] = CubeLocate[3][0] +3*cubesize;
                    CubeLocate[3][1] = CubeLocate[3][1] -3*cubesize;
                }
                else if(225.0 <= x_Rotate && x_Rotate <= 315.0)
                {
                    //CubeLocate[0][0] = CubeLocate[0][0] -cubesize;
                    //CubeLocate[0][1] = CubeLocate[0][1] -cubesize;
                    CubeLocate[1][0] = CubeLocate[1][0] + cubesize;
                    CubeLocate[1][1] = CubeLocate[1][1] + cubesize;
                    CubeLocate[2][0] = CubeLocate[2][0] +2*cubesize;
                    CubeLocate[2][1] = CubeLocate[2][1] +2*cubesize;
                    CubeLocate[3][0] = CubeLocate[3][0] +3*cubesize;
                    CubeLocate[3][1] = CubeLocate[3][1] +3*cubesize;
                }
                else
                {
                    //CubeLocate[0][0] = CubeLocate[0][0] -cubesize;
                    //CubeLocate[0][1] = CubeLocate[0][1] -cubesize;
                    CubeLocate[1][0] = CubeLocate[1][0] - cubesize;
                    CubeLocate[1][1] = CubeLocate[1][1] + cubesize;
                    CubeLocate[2][0] = CubeLocate[2][0] -2*cubesize;
                    CubeLocate[2][1] = CubeLocate[2][1] +2*cubesize;
                    CubeLocate[3][0] = CubeLocate[3][0] -3*cubesize;
                    CubeLocate[3][1] = CubeLocate[3][1] +3*cubesize;
                }
            }

            //CubeLocate[0][1] -= cubesize;
            //CubeLocate[1][1] = cos(x_Rotate) * CubeLocate[1][1];
            //CubeLocate[2][1] = cubesize;
            //CubeLocate[3][1] = cubesize;
            //CubeLocate[1][0] = cubesize;
            //CubeLocate[2][0] = cubesize;
            //CubeLocate[3][0] = cubesize;
        break;
        default:
        break;
 }
 for(int i = 0;i<4;i++)
 {
     printf("c[%d] : (%f,%f)\n",i,CubeLocate[i][0],CubeLocate[i][1]);
 }
 glutPostRedisplay();
}


void StackCube(int ObjectName)
{
    if(ObjectName == 0)
    {
        isCube[9+(int)(x_location*2)][24 + (int)(time_trans*2)] = true;
        isCube[9+(int)(x_location*2)][24 + (int)(time_trans*2) + 1] = true;
        isCube[9+(int)(x_location*2)][24 + (int)(time_trans*2) + 2] = true;
        isCube[9+(int)(x_location*2)][24 + (int)(time_trans*2) + 3] = true;


    }
    else if(ObjectName == 1)
    {
        isCube[9+(int)(x_location*2)][24 + (int)(time_trans*2)] = true;
        isCube[9+(int)(x_location*2)+1][24 + (int)(time_trans*2)+1] = true;
        isCube[9+(int)(x_location*2)][24 + (int)(time_trans*2) + 1] = true;
        isCube[9+(int)(x_location*2)][24 + (int)(time_trans*2) + 2] = true;
    }
    else if(ObjectName == 2)
    {
        isCube[9+(int)(x_location*2)][24 + (int)(time_trans*2)] = true;
        isCube[9+(int)(x_location*2)+1][24 + (int)(time_trans*2)] = true;

        isCube[9+(int)(x_location*2)+1][24 + (int)(time_trans*2) + 1] = true;
        isCube[9+(int)(x_location*2)][24 + (int)(time_trans*2) + 1] = true;
    }
    else if(ObjectName == 3)
    {
        isCube[9+(int)(x_location*2)][24 + (int)(time_trans*2)] = true;
        isCube[9+(int)(x_location*2)][24 + (int)(time_trans*2) + 1] = true;
        isCube[9+(int)(x_location*2)+1][24 + (int)(time_trans*2)+2] = true;
        isCube[9+(int)(x_location*2)][24 + (int)(time_trans*2) + 2] = true;
    }
    CheckMax();


}

void tetris()
{

    glMatrixMode(GL_MODELVIEW);
    // 1st object

    //glPushMatrix();

    //glTranslatef(0.0,5.0,0.0);

    if(objectShape == 0)
    {
        if(init)
        {
        CubeLocate[0][0] = 0.0;
        CubeLocate[0][1] = 0.0;
        CubeLocate[1][0] = 0.0;
        CubeLocate[1][1] = cubesize;
        CubeLocate[2][0] = 0.0;
        CubeLocate[2][1] = cubesize*2;
        CubeLocate[3][0] = 0.0;
        CubeLocate[3][1] = cubesize*3;
        init = false;
        }
        glPushMatrix();
            glColor3f(1.0,0.0,0.0);
            glutSolidCube(cubesize);
            glColor3f(0.0,0.0,0.0);
            glutWireCube(cubesize);
        glPopMatrix();


        glPushMatrix();
        glTranslatef(0.0,cubesize,0.0);
            glColor3f(1.0,0.0,0.0);
            glutSolidCube(cubesize);
            glColor3f(0.0,0.0,0.0);
            glutWireCube(cubesize);
        glPopMatrix();


        glPushMatrix();
        glTranslatef(0.0,cubesize*2,0.0);
            glColor3f(1.0,0.0,0.0);
            glutSolidCube(cubesize);
            glColor3f(0.0,0.0,0.0);
            glutWireCube(cubesize);
        glPopMatrix();


        glPushMatrix();
        glTranslatef(0.0,cubesize*3,0.0);
            glColor3f(1.0,0.0,0.0);
            glutSolidCube(cubesize);
            glColor3f(0.0,0.0,0.0);
            glutWireCube(cubesize);
        glPopMatrix();
    }
    else if(objectShape == 1)
    {
        if(init)
        {
        CubeLocate[0][0] = 0.0;
        CubeLocate[0][1] = 0.0;
        CubeLocate[1][0] = 0.0;
        CubeLocate[1][1] = cubesize;
        CubeLocate[2][0] = cubesize;
        CubeLocate[2][1] = cubesize;
        CubeLocate[3][0] = 0.0;
        CubeLocate[3][1] = cubesize*2;
        init = false;
        }
        glPushMatrix();
            glColor3f(0.0,1.0,0.0);
            glutSolidCube(cubesize);
            glColor3f(0.0,0.0,0.0);
            glutWireCube(cubesize);
        glPopMatrix();



        glPushMatrix();
        glTranslatef(0.0,cubesize,0.0);
            glColor3f(0.0,1.0,0.0);
            glutSolidCube(cubesize);
            glColor3f(0.0,0.0,0.0);
            glutWireCube(cubesize);
        glPopMatrix();


        glPushMatrix();
        glTranslatef(cubesize,cubesize,0.0);
            glColor3f(0.0,1.0,0.0);
            glutSolidCube(cubesize);
            glColor3f(0.0,0.0,0.0);
            glutWireCube(cubesize);
        glPopMatrix();


        glPushMatrix();
        glTranslatef(0.0,cubesize*2,0.0);
            glColor3f(0.0,1.0,0.0);
            glutSolidCube(cubesize);
            glColor3f(0.0,0.0,0.0);
            glutWireCube(cubesize);
        glPopMatrix();
    }

    else if(objectShape == 2)
    {
        if(init)
        {
        CubeLocate[0][0] = 0.0;
        CubeLocate[0][1] = 0.0;
        CubeLocate[1][0] = 0.0;
        CubeLocate[1][1] = cubesize;
        CubeLocate[2][0] = cubesize;
        CubeLocate[2][1] = cubesize;
        CubeLocate[3][0] = cubesize;
        CubeLocate[3][1] = 0.0;
        init =false;
        }
        glPushMatrix();
            glColor3f(0.0,0.0,1.0);
            glutSolidCube(cubesize);
            glColor3f(0.0,0.0,0.0);
            glutWireCube(cubesize);
        glPopMatrix();


        glPushMatrix();
        glTranslatef(0.0,cubesize,0.0);
            glColor3f(0.0,0.0,1.0);
            glutSolidCube(cubesize);
            glColor3f(0.0,0.0,0.0);
            glutWireCube(cubesize);
        glPopMatrix();


        glPushMatrix();
        glTranslatef(cubesize,cubesize,0.0);
            glColor3f(0.0,0.0,1.0);
            glutSolidCube(cubesize);
            glColor3f(0.0,0.0,0.0);
            glutWireCube(cubesize);
        glPopMatrix();


        glPushMatrix();
        glTranslatef(cubesize,0.0,0.0);
            glColor3f(0.0,0.0,1.0);
            glutSolidCube(cubesize);
            glColor3f(0.0,0.0,0.0);
            glutWireCube(cubesize);
        glPopMatrix();


    }
    else if(objectShape == 3)
    {
        if(init)
        {
        CubeLocate[0][0] = 0.0;
        CubeLocate[0][1] = 0.0;
        CubeLocate[1][0] = 0.0;
        CubeLocate[1][1] = cubesize;
        CubeLocate[2][0] = cubesize;
        CubeLocate[2][1] = cubesize*2;
        CubeLocate[3][0] = 0.0;
        CubeLocate[3][1] = cubesize*2;
        }

        glPushMatrix();
            glColor3f(1.0,1.0,0.0);
            glutSolidCube(cubesize);
            glColor3f(0.0,0.0,0.0);
            glutWireCube(cubesize);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.0,cubesize,0.0);
            glColor3f(1.0,1.0,0.0);
            glutSolidCube(cubesize);
            glColor3f(0.0,0.0,0.0);
            glutWireCube(cubesize);
        glPopMatrix();



        glPushMatrix();
        glTranslatef(cubesize,cubesize*2,0.0);
            glColor3f(1.0,1.0,0.0);
            glutSolidCube(cubesize);
            glColor3f(0.0,0.0,0.0);
            glutWireCube(cubesize);
        glPopMatrix();


        glPushMatrix();
        glTranslatef(0.0,cubesize*2,0.0);
            glColor3f(1.0,1.0,0.0);
            glutSolidCube(cubesize);
            glColor3f(0.0,0.0,0.0);
            glutWireCube(cubesize);
        glPopMatrix();
    }
    else
    {
        glPushMatrix();
            glColor3f(1.0,0.0,0.0);
            glutSolidCube(cubesize);
            glColor3f(0.0,0.0,0.0);
            glutWireCube(cubesize);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(cubesize,0.0,0.0);
            glColor3f(1.0,0.0,0.0);
            glutSolidCube(cubesize);
            glColor3f(0.0,0.0,0.0);
            glutWireCube(cubesize);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.0,cubesize,0.0);
            glColor3f(1.0,0.0,0.0);
            glutSolidCube(cubesize);
            glColor3f(0.0,0.0,0.0);
            glutWireCube(cubesize);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(-cubesize,cubesize,0.0);
            glColor3f(1.0,0.0,0.0);
            glutSolidCube(cubesize);
            glColor3f(0.0,0.0,0.0);
            glutWireCube(cubesize);
        glPopMatrix();
    }
    //glPopMatrix();
}

float Ymax()
{
    float y_max = 100.0;
    for(int i = 0; i< 3; i++)
    {
        if(CubeLocate[i][1] < y_max)
        {
            y_max = CubeLocate[i][1];
        }

    }
    return y_max;
}


void TransScene(void)
{
    glMatrixMode(GL_MODELVIEW);
    // 깊이 버퍼를 깨끗이 지워야합니다.
    // 깊이 버퍼가 꽉차있으면 아무것도 그려지지 않기 때문이죠.
    // 아래는 깊이버퍼를 지워주는 코드입니다.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        gluLookAt(0.5,0.5,2.0, 0.0,0.0,0.0, 0.0,1.0,0.0);
        line();
        glPushMatrix();
            glTranslatef(0.0,time_trans,0.0);

            glPushMatrix();
                glTranslatef(x_location,5.0,0.0);
                glRotatef(x_Rotate,0.0,0.0,1.0);
                tetris();
                //glPopMatrix();
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();

            //glTranslatef(0.0,-5.0,0.0); // 쌓인 큐브 맨 아래로 정렬
            for(int i = 0; i<19;i++)
            {
                for(int j = 0; j<29;j++)
                {

                    if(isCube[i][j])
                    {
                    glPushMatrix();
                    //if(init == 1)
                        //if(j == 0) ccount+=1;
                        glTranslatef((float)(i - 9)/2,(float)(j- 14)/2,0.0);
                        //if( init ==1){
                            //printf("ccount(%d) : %d",j,ccount);
                            //printf("trans(%d,%d) : (%f,%f)",i,j,(float)(i - 8)*0.5,(float)(j- 9)*0.5);
                          //  init =0;
                        //}
                        glColor3f(0.0,1.0,1.0);
                        glutSolidCube(cubesize);
                        glColor3f(0.0,0.0,0.0);
                        glutWireCube(cubesize);
                    glPopMatrix();

                    }
                }

            }
        glPopMatrix();

    glPopMatrix();


    //printf("time : %f",time_trans);
    glPopMatrix();

    //time_trans -= cubesize;
    CubeLocate[0][1] -= cubesize;
    CubeLocate[1][1] -= cubesize;
    CubeLocate[2][1] -= cubesize;
    CubeLocate[3][1] -= cubesize;
    float Max = Ymax();


  //  for(int i=0; i< 3 ;i++)
   // {
    //    if(Max - 0.25 < CubeLocate[i][1] -5.0 && CubeLocate[i][1] -5.0 < Max + 0.25)
    //    {
    //        if( Max <= max_cube[9+(int)(CubeLocate[i][0]*2)])
     //           {
     //   StackCube(objectShape);//stackcube 호출
     //   time_trans = 5.0; // 원래 y좌표 5.0으로 초기화
      //  // 모양 변수도 초기화
      //  x_Rotate = 0.0;// 로테이션 초기화 ,나중에는 이것도 랜덤으로 처리하자..!
      //  x_location = 0.0; // x 좌표 초기화
      //  objectShape = rand() % 4;
      //  init = true;
      //          }

      //  }

    //}

        if(time_trans < -12.0) // 나중에 여기를 max 갑 좌표로 초기화 할것
    {
        //printf("max_cube[%d] :%f > time_Trans :%f",(int) x_location,max_cube[(int)x_location],time_trans);
        StackCube(objectShape);//stackcube 호출
        time_trans = 5.0; // 원래 y좌표 5.0으로 초기화
        // 모양 변수도 초기화
        x_Rotate = 0.0;// 로테이션 초기화 ,나중에는 이것도 랜덤으로 처리하자..!
        x_location = 0.0; // x 좌표 초기화
        objectShape = rand()%4;

    }
    time_trans -= 0.01;
    //Sleep(100);
// 쌓인거 표시

    glutPostRedisplay();

}


void DrawTetris()
{
    glMatrixMode(GL_PROJECTION);
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    //tetris();

    glPopMatrix();
    //glPopMatrix();

    glFlush();

}

int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(500,800);
    glutInitWindowPosition(0,0);
    glutCreateWindow("TETRIS GAME");
    srand((unsigned int)time(0));

    objectShape = rand() % 4;
    //objectColor[] = (float)rand()%256/256;
    for(int i = 0; i< 19;i++) max_cube[i] = -12.0;
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1*width,width,-1*height,height,-5.0,5.0);
    glutDisplayFunc(DrawTetris);
    glutIdleFunc(TransScene);
    glutKeyboardFunc(MyKeyboard);
    glutMainLoop();
    return 0;
}
