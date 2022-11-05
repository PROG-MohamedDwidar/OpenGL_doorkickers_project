/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, coneaaa
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#include <bits/stdc++.h>

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <windows.h>
using namespace std;


class Alien;
class Shot
{
public:
    static std::vector<Shot>shots;
    double x=0,y=0,direction=0,originX,originY;

    Shot(double playerX,double playerY,double pdirection)
    {
        originX=x;
        originY=y;
        x=playerX;
        y=playerY;
        direction=pdirection;
        shots.push_back(*this);
        glutTimerFunc(1000/60 ,bulletControl, 0);

    }
    void draw()
    {
        glPushMatrix();

        glRotatef(direction,originX,originY,1);

        glColor3f(0,0,0);
        glBegin(GL_POLYGON);//---------------start drawing bullet--------------
        glVertex2d(x, y+1);
        glVertex2d(x+0.3, y-1);
        glVertex2d(x-0.3, y-1);
        glEnd();//---------------end drawing--------------

        glPopMatrix();
    }


    static void bulletControl(int)
{
    if(shots.empty())
    {

    }
    else
    {
        for(int i=0;i<shots.size();i++)
        {
            if(shots[i].y>=57){
                shots.erase(shots.begin()+i);
            }
            shots[i].y+=1;
        }

        glutTimerFunc(1000/60, bulletControl, 0);
    }
}
};


class Player{
public:
    double x=0,y=0, direction=0;
    static std::vector<Player>players;
    static std::queue<Alien>contacts;

    Player(double x,double y){
        this->x=x;
        this->y=y;
        players.push_back(*this);
    }

    void draw(){
        glPushMatrix();

        glRotatef(direction,x,y,1);

        glLineWidth(10.0);
        glColor3f(1,0,1);
        glBegin(GL_POLYGON);//---------------start drawing body--------------
        glVertex2d(x-4, y+2);
        glVertex2d(x+4, y+2);
        glVertex2d(x+4, y-2);
        glVertex2d(x-4, y-2);
        glEnd();//---------------end drawing--------------

        glColor3f(0,0,0);
        glBegin(GL_POLYGON);//---------------start drawing gun--------------
        glVertex2d(x+2, y+7);
        glVertex2d(x+2.8, y+7);
        glVertex2d(x+2.8, y+2);
        glVertex2d(x+2, y+2);
        glEnd();//---------------end drawing--------------

        glColor3f(0.31,1,0.31);
        glBegin(GL_POLYGON);//---------------start drawing head--------------
        double theta;
        for(double i=0;i<=360;i+=1)
        {
            theta=i*3.14/180;
            glVertex2d(3*cos(theta)+x,3*sin(theta)+y);
        }
        glEnd();//---------------end drawing--------------


        glPopMatrix();

    }


    void rotate(double dir)
    {
        this->direction=dir;
    }
    void shoot()
    {

    }
};

class Alien
{
public:
    double x,y,direction;
    static std::vector<Alien>aliens;

    Alien(double x=0,double y=60,double direction=180)
    {
        this->x=x;
        this->y=y;
        this->direction=direction;

    }
    void draw()
    {
        glPushMatrix();

        glRotatef(direction,x,y,1);

        glLineWidth(10.0);
        glColor3f(1,0,0);
        glBegin(GL_POLYGON);//---------------start drawing body--------------
        glVertex2d(x-2.5, y+5);
        glVertex2d(x+2.5, y+5);
        glVertex2d(x+2.5, y-5);
        glVertex2d(x-2.5, y-5);
        glEnd();//---------------end drawing--------------



        glPopMatrix();

    }
};












void display();
void reshape(int,int);
void timer(int);
void changer(int);
void mousedet(int button,int state,int x,int y);









vector<Shot> Shot::shots;
vector<Player> Player::players;
int mouseflag=0;
int main(int argc,char**argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);

    glutInitWindowPosition(0,0);


    glutCreateWindow("Road");
    glutFullScreen();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0,timer,0);
    glutMouseFunc(mousedet);
    Shot shot(0,0,0);


    glClearColor(0.6,0.3,0.0,1.0);

    glutMainLoop();
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();





    //printf("size = %d \n",Shot::shots.size());
    if(!Shot::shots.empty())
    {

        for(int i=0;i<Shot::shots.size();i++)
        {
            //printf("size = %d \n",Shot::shots.size());
            Shot::shots[i].draw();
        }
    }



    for(int i=0;i<Player::players.size();i++)
    {
        //printf("size = %d \n",Shot::shots.size());
        Player::players[i].draw();
    }


    glColor3f(1,0.6,1);
    glBegin(GL_POLYGON);
    glVertex2d(80,-46.25);
    glVertex2d(100,-46.25);
    glVertex2d(100,-56.25);
    glVertex2d(80,-56.25);
    glEnd();



    glutSwapBuffers();





}
void reshape(int w,int h){
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100,100,-56.25,56.25);

    glMatrixMode(GL_MODELVIEW);
}

void timer(int){
    glutPostRedisplay();
    glutTimerFunc(1000/60,timer,0);
}

void mousedet(int button,int state,int x,int y)
{

    GLint viewport[4]; //var to hold the viewport info
    GLdouble modelview[16]; //var to hold the modelview info
    GLdouble projection[16]; //var to hold the projection matrix info
    GLfloat winX, winY, winZ; //variables to hold screen x,y,z coordinates
    GLdouble worldX, worldY, worldZ; //variables to hold world x,y,z coordinates

    glGetDoublev( GL_MODELVIEW_MATRIX, modelview ); //get the modelview info
    glGetDoublev( GL_PROJECTION_MATRIX, projection ); //get the projection matrix info
    glGetIntegerv( GL_VIEWPORT, viewport ); //get the viewport info

	winX = (float)x;
    winY = (float)viewport[3] - (float)y;
	winZ = 0;

	//get the world coordinates from the screen coordinates
    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &worldX, &worldY, &worldZ);


    switch (button)
    {
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN)
            {

                if (worldX>=80 && worldY<=-46)
                {
                    printf("mouse clicked %f %f \n",worldX,worldY);
                    mouseflag=1;
                }

            }
            if(state == GLUT_UP)
            {

                if(worldX<=80 && worldY>=-46)
                {
                    printf("mouse lifted %f %f \n",worldX,worldY);
                    mouseflag=0;
                    Player player(worldX,worldY);
                }

            }
        break;
    }
}








