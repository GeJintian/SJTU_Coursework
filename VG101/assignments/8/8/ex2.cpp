#include<GL/freeglut.h>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<ctime>
#include"figures.h"
#include"parkinglot.h"

using namespace std;

void TimeStep(int n){
    glutTimerFunc(25,TimeStep,0);
    glutPostRedisplay();
}

void glDraw(){
    static int action = 0;
    static int slot   = 0;
    static int u_,s_,t_;
    static int* arr=new int[9];
    static float spin = 1.0;
    static float zoom = 1.0;
    static float a = -0.9;
    static float b = -0.8;
    static float c=0.0;
    static float d=0.0;
    if(action==0){
        u_ = rand()%7 + 1;
        s_ = rand()%(8-u_) + 1;
        t_ = rand()%(9-u_-s_) + 1;
        int t;
        for(int i=0;i<u_+s_+t_;i++){
            t=rand()%(u_+s_+t_);
            arr[i]=t;
            for(int j=0; j<i;j++){
                if(arr[j]==t){
                    i--;
                    break;
                }
            }
        }
        action = 1;
    }
    Parkinglot test(arr,u_,s_,t_,zoom,spin,a,b,c,d);
    if(slot==0){
        slot = test.findSlot();
    }
    test.Act(&spin,&zoom,&a,&b,&c,slot);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    test.Drawlot();
    glutSwapBuffers();
    glFlush();
}

int main(int argc,char *argv[]){
    srand(time(0));
    glutInit(&argc,argv);
    glutInitWindowSize(700,700);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Parking Lot");
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(&glDraw);
    glutTimerFunc(25,TimeStep,0);
    glutMainLoop();
}
