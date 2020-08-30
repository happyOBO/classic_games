
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
bool lightOn = false;


void MyLightInit()
{
    //색깔 조정
    GLfloat global_ambient[] = {0.1,0.1,0.1,1.0};

    GLfloat light0_ambient[] = {0.5,0.4,0.3,1.0};
    GLfloat light0_diffuse[] = {0.5,0.4,0.3,1.0};
    GLfloat light0_speccular[] = {1.0,1.0,1.0,1.0};

    GLfloat light1_ambient[] = {0.0,0.0,0.0,1.0};
    GLfloat light1_diffuse[] = {0.5,0.2,0.3,1.0};
    GLfloat light1_speccular[] = {0.0,0.0,0.0,1.0};

    GLfloat material_ambient[] = {0.3,0.3,0.3,1.0};
    GLfloat material_diffuse[] = {0.8,0.8,0.8,1.0};
    GLfloat material_specular[] = {0.0,0.0,1.0,1.0};
    GLfloat material_shininess[] = {25.0};

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);// 이게 있어야 깊이가 제대로 나온다.
    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0,GL_AMBIENT,light0_ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,light0_diffuse);
    glLightfv(GL_LIGHT0,GL_SPECULAR,light0_speccular);

    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1,GL_AMBIENT,light1_ambient);
    glLightfv(GL_LIGHT1,GL_DIFFUSE,light1_diffuse);
    glLightfv(GL_LIGHT1,GL_SPECULAR,light1_speccular);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    // 아래 코드 지엘_000 이부분이 잘못되면 도넛에 그라데이션이 안보인다.
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT,global_ambient);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);






    /*
     GLint n;
     glGetIntegerv(GL_MAX_LIGHTS, &n); // 현재의 드라이버가 몇 개의 광원을 지원하는지 검색
     printf("n = %ld\n", n);
     */



}
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
            case 'l':
                lightOn = true;
            break;
            case 'u':
                lightOn = false;
            break;
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
    GLfloat LightPosition0[] = {0.0, 0.0, 2.0, 1.0};
    GLfloat LightPosition1[] = {1.0,1.0,1.0,1.0};
    GLfloat LightDirection1[] = {-0.5, -1.0,-1.0};
    GLfloat SpotAngle1[] = {20.0};
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
                        if(lightOn){
                            MyLightInit();
                            glLightfv(GL_LIGHT0 , GL_POSITION, LightPosition0);
                            glLightfv(GL_LIGHT1 , GL_POSITION ,LightPosition1);
                            glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION, LightDirection1);
                            glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF , SpotAngle1);
                            glLightf(GL_LIGHT1, GL_SPOT_EXPONENT , 1.0);
                        }
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
    time_trans -= 0.005;
    //Sleep(100);
// 쌓인거 표시

    glutPostRedisplay();

}

void MyReshape(int w,int h)
{

    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
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
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1*width,width,-1*height,height,-5.0,5.0);

    glutDisplayFunc(DrawTetris);
    glutIdleFunc(TransScene);
    glutKeyboardFunc(MyKeyboard);
    //glutReshapeFunc(MyReshape);
    glutMainLoop();
    return 0;
}
