//
// Created by 胡笛 on 2017/4/27.
//

#include"board.h"
#include"player.h"
#include "Socket.h"
#include "game.h"
#include<iostream>
#include<Opengl/gl.h>
#include<Opengl/glu.h>
#include<GLUT/glut.h>
#include<math.h>
const int cheesen=50;
const GLfloat cheeseR=0.13f/2;
const GLfloat Pi=3.1415926536f;
void display();
void Mouse(int button, int state, int x, int y);
game hahagame=game(1,0,0);
board nowboard=board();
int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(500,500);
    glutCreateWindow("Xcode Glut Demo");
    glutMouseFunc(Mouse);
    glutDisplayFunc(display);
    glutMainLoop();

/*
board bd;
bd=bd.oneStep(1,point(4,5));
bd.print();
std::cout<<bd.getAvaliable(1).size()<<std::endl;
std::cout<<point(0,0).toString()<<std::endl;
std::set<point>::iterator it;
std::set<point> tmp=bd.getAvaliable(1);
it=tmp.begin();
while(it!=tmp.end())
{
    std::cout<<it->toString()<<" ";
    it++;
}
 */
}

void display()
{
    glClearColor(1.0,1.0,1.0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.8,0.0);
    glRectd(-0.8,0.8,0.4,-0.4);
    glBegin(GL_LINES);
    glColor3f(0.0,0.0,0.0);
    for(int i=0;i<9;i++)
    {
        glVertex2f(-0.8,0.8-0.15*i);
        glVertex2f(0.4,0.8-0.15*i);
        glVertex2f(-0.8+0.15*i,0.8);
        glVertex2f(-0.8+0.15*i,-0.4);
    }
    glEnd();
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            point tmp=point(i,j);
            if(hahagame.geiboard()[tmp]!=-1)
            {
                if(hahagame.geiboard()[tmp]==1)
                    glColor3f(0.0,0.0,0.0);
                else
                    glColor3f(1.0,1.0,1.0);
                glBegin(GL_POLYGON);
                for(int p=0;p<cheesen;p++)
                {
                    glVertex2f(cheeseR*cos(2*Pi/cheesen*p)-0.8+0.075+0.15*i,cheeseR*sin(2*Pi/cheesen*p)+0.8-0.075-0.15*j);
                }
                glEnd();

            }
        }
    }
    glFlush();
}

void Mouse(int button, int state, int x, int y)
{
    if(state==GLUT_DOWN)
    {
        double positionx=(double)x/250;
        double positiony=(double)y/250;
        point tmp=point((int)((positionx-0.2)/0.15),(int)((positiony-0.2)/0.15));
        if(hahagame.getWhoseTurn()==1) {
            std::set<point> tmp1 = hahagame.geiboard().getAvaliableset(1);
            if (tmp1.find(tmp) != tmp1.end()) {
                hahagame.peoplemove(tmp);
            }
        }
        else
        {
            std::set<point> tmp1 = hahagame.geiboard().getAvaliableset(0);
            if (tmp1.find(tmp) != tmp1.end()) {
                hahagame.peoplemove(tmp);
            }
        }
        display();
    }
}