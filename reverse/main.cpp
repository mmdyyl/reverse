//
// Created by 胡笛 on 2017/4/27.
//

#include"board.h"
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
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
void show_text(char *text_toshow, double x, double y);
void Mouse(int button, int state, int x, int y);
game hahagame=game(1,0,0);
board nowboard=board();
int main(int argc, char ** argv)
{
    player black(1),white(0);
    board bd;
    bd.print();
    black.nextMove(bd);
    bd.print();

    return 0;
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
    show_text("white",0.6,0.7);
    show_text("black",0.6,0.5);
    char num[20];
    sprintf(num,"%d",hahagame.geiboard().getWhiteCheeseNum());
    show_text(num,0.65,0.6);
    sprintf(num,"%d",hahagame.geiboard().getBlackCheeseNum());
    show_text(num,0.65,0.4);
    if(hahagame.getWhoseTurn()==1)
    {
        show_text("black's",0.6,0.1);
    }
    else
    {
        show_text("white's",0.6,0.1);
    }
    show_text("turn",0.6,0.0);
    show_text("time cost",0.55,-0.2);
    sprintf(num,"%f",hahagame.getTimeCost());
    show_text(num,0.65,-0.3);
    if(hahagame.geiboard().gameEnd()==1)
    {
        if(hahagame.geiboard().winner()==1)
        {
            show_text("game end, black win!!",-0.6,-0.6);
        } else{
            show_text("game end, white win!!",-0.6,-0.6);
        }
    }
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
    std::vector<point> avaliablevecc=hahagame.geiboard().getAvaliable(hahagame.getWhoseTurn());


    for(int k=0;k<avaliablevecc.size();k++) {
        int i=avaliablevecc[k].x;
        int j=avaliablevecc[k].y;
        glColor3f(0.6,0.6,0.6);
        glBegin(GL_POLYGON);
        for (int p = 0; p < cheesen; p++) {
            glVertex2f(cheeseR * cos(2 * Pi / cheesen * p) - 0.8 + 0.075 + 0.15 * i,
                       cheeseR * sin(2 * Pi / cheesen * p) + 0.8 - 0.075 - 0.15 * j);
        }
        glEnd();
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
                hahagame.checknextmove();
            }
        }
        else
        {
            std::set<point> tmp1 = hahagame.geiboard().getAvaliableset(0);
            if (tmp1.find(tmp) != tmp1.end()) {
                hahagame.peoplemove(tmp);
                hahagame.checknextmove();
            }
        }
        display();
    }
}

void show_text(char *text_toshow, double x, double y)
{
    /* There are 7 bitmap fonts available in GLUT. They are
        GLUT_BITMAP_8_BY_13
        GLUT_BITMAP_9_BY_15
        GLUT_BITMAP_TIMES_ROMAN_10
        GLUT_BITMAP_TIMES_ROMAN_24
        GLUT_BITMAP_HELVETICA_10
        GLUT_BITMAP_HELVETICA_12
        GLUT_BITMAP_HELVETICA_18 */
    void * font = GLUT_BITMAP_HELVETICA_18;
    glColor3f( 0.0,0.0,0.0);
    glRasterPos2f(x, y);
    for (int i=0; i<=strlen(text_toshow); ++i) {
        char c = text_toshow[i];
        glutBitmapCharacter(font, c);
    }
}