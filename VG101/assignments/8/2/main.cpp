#include <iostream>
#include<GL/freeglut.h>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include"figure.h"
#include"parkinglot.h"

using namespace std;

void TimeStep(int n){
    glutTimerFunc(25,TimeStep,0);
    glutPostRedisplay();
}

void glDraw(){
    int static action = 0;
    int static slot   = 0;
    int static u_,s_,t_;
    int static * arr=new int[9];
    float static spin = 1.0;
    float static zoom = 1.0;
    float static a = -0.9;
    float static b = -0.8;
    float static c=0.0;
    float static d=0.0;
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