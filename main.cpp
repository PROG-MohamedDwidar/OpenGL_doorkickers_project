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

int warn=0;
class Alien
{
public:
    double x,y,direction,health=100,hit=0;
    static std::vector<Alien *>aliens;
    static int alienCount,maxAttack,marchingFlag;
    static double maxhealth;
    Alien(double x=0,double y=60,double direction=180)
    {
        //printf("start constructor alien\n");
        alienCount++;
        this->health=maxhealth;
        this->x=x;
        this->y=y;
        this->direction=direction;

        //printf("alien called x = %f y = %f dir = %f \n",x,y,direction);

        aliens.push_back(this);
        if(marchingFlag==0){
            marchingFlag=1;
            glutTimerFunc(1000/60 , alienMarch, 0);
        }

        //printf("end constructor alien\n");
    }
    void draw()
    {
        hit--;
        //printf("start draw alien\n");
        if(health>0){

        glPushMatrix();

        //glRotatef(90,x,y,1);

        glLineWidth(10.0);
        glColor3f(0.8,0,0);
        if(hit>0)glColor3f(0.8,0.8,0);
        glBegin(GL_POLYGON);

        //---------------start drawing body--------------
        glVertex2d(x-2.5, y+5);
        glVertex2d(x+2.5, y+5);
        glVertex2d(x+2.5, y-5);
        glVertex2d(x-2.5, y-5);
        glEnd();//---------------end drawing--------------

        glPopMatrix();
        }
        //printf("end draw alien 1\n");

    }
    static void alienMarch(int){
        if(aliens.empty())
        {
            //printf("start 1\n");
            marchingFlag=0;
            if(maxAttack<=5)maxAttack++;
            //maxhealth+=10;
            int liner=50;
            for(int i=0;i<maxAttack;i++){
                liner+=10;
                double randX = -100 + (rand() % ( 100 + 100 + 1 ) );
                //if(liner%10==0)liner+=10;
                //printf("creating liner = %ld\n",liner);

                //printf("x = %f y = %d --------alien draw \n",randX,liner);
                new Alien(randX, liner, 180);
                //printf("in loop 1 i = %d\n",i);
            }
            //printf("done 1 \n");
        }
        else
        {
            //printf("start 2\n");
            for(int i=0;i<aliens.size();i++)
            {
                //printf("in loop 2 i = %d\n",i);
                //if(aliens.size()!=1)printf("inside move loop for alien %d\n",i);
                aliens[i]->y-=1;
                //if(aliens.size()!=1)printf("pos %f\n",aliens[i]->y);
                if(aliens[i]->y<=-56){
                    aliens.erase(aliens.begin()+i);
                    alienCount--;
                    if(aliens[i]->health>0){
                        warn=15;
                    }

                }

            }
            //printf("done 2\n");
            glutTimerFunc(1000/30, alienMarch, 0);
        }
    }

};


class Shot
{
public:
    //static std::vector<Shot>shots;
    double x=0,y=0,direction=0,originX,originY;

    Shot(double playerX,double playerY,double pdirection)
    {
        //printf("start shot construct\n");
        originX=x;
        originY=y;
        x=playerX;
        y=playerY;
        direction=pdirection;
        //shots.push_back(*this);
        //glutTimerFunc(1000/60 ,bulletControl, 0);
        //printf("end shot construct\n");

    }
    void draw()
    {
        //printf("start shot draw\n");
        glColor3f(0,0,0);
        glBegin(GL_POLYGON);//---------------start drawing bullet--------------
        glVertex2d(x, y+1);
        glVertex2d(x+0.3, y-1);
        glVertex2d(x-0.3, y-1);
        glEnd();//---------------end drawing--------------
        //printf("end shot draw\n");
    }



};


class Player{
public:
    double x=0,y=0, direction=0;
    static std::vector<Player>players;
    std::queue<int>contacts;
    std::vector<Shot>shots;
    Player(double x,double y){
        this->x=x;
        this->y=y;
        players.push_back(*this);

    }

    void draw(){
        //printf("start player draw\n");
        glPushMatrix();

        //glLoadIdentity();

        glTranslated(x,y,0);
        glRotatef(direction,0,0,1);
        glTranslated(-x,-y,0);

        //printf("start shot loop\n");
        //printf("No. shots = %d\n",shots.size());
        for(int i=0;i<shots.size();i++)
        {
            /*if(shots[i].y<=contacts.front()->y+5 && shots[i].y>=contacts.front()->y-5){
                shots.erase(shots.begin()+i);
                printf("bullseye health= %f\n",contacts.front()->health);
                contacts.front()->health-=50;
                if(contacts.front()->health<=0){
                    //printf("before pop\n");
                    contacts.pop();
                    direction=0;
                    //printf("after pop\n");
                }
            }*/
           // printf("nom i = %d\n",i);
            shots[i].draw();
           // printf("increment y\n");
            shots[i].y+=8;
           // printf("check out\n");
            if(shots[i].y>77){
                //printf("start erase shot\n");
                shots.erase(shots.begin()+i);
                //Alien::aliens[contacts.front()]->health-=50;
               // printf("check alien health\n");
                /*if(Alien::aliens[contacts.front()]->health<=0){
                    //printf("before pop\n");
                    Alien::aliens.erase(Alien::aliens.begin()+contacts.front());
                    contacts.pop();

                    direction=0;
                    //printf("after pop\n");
                }*/
                break;
            }
        }
        //printf("end shots loop\n");
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
        //printf("end player draw\n");

    }



    void shoot(int alienNum)
    {
        //printf("start shoot\n");
        glutTimerFunc(500,alienshoot,alienNum);
        if(Alien::aliens[alienNum]->health<=0)contacts.pop();
        direction=(atan((x-Alien::aliens[alienNum]->x)/(Alien::aliens[alienNum]->y-y)))*180.0/3.14;
        if(Alien::aliens[alienNum]->y<y)direction+=180;
        Shot shot(x+2.4,y,direction);
        shots.push_back(shot);
        //printf("end shoot\n");

    }
    static void alienshoot(int alienNum)
    {
        Alien::aliens[alienNum]->health-=50;
        Alien::aliens[alienNum]->hit=15;

    }

};














void display();
void reshape(int,int);
void timer(int);
void mousedet(int button,int state,int x,int y);
void contactControl(int);
void shootingControl(int id);







//vector<Shot> Shot::shots;
vector<Player> Player::players;
vector<Alien *> Alien::aliens;
//queue<Alien> Player::contacts;
//queue<Shot> Player::shots;
int Alien::alienCount = 0,Alien::maxAttack=1,Alien::marchingFlag=0;

double Alien::maxhealth=100;
int mouseflag=0;
int main(int argc,char**argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    //|GLUT_DOUBLE
    glutInitWindowPosition(0,0);


    glutCreateWindow("Road");
    glutFullScreen();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0,timer,0);
    glutMouseFunc(mousedet);

    //Shot shot(0,-40,-40);
    new Alien();
    //glutTimerFunc(0,Player::shootingController,0);
    glutTimerFunc(1000/30,contactControl,0);
    glClearColor(0.6,0.3,0.0,1.0);

    glutMainLoop();
}
void display(){
    //printf("start display\n");
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();





    //printf("size = %d \n",Shot::shots.size());
    /*if(!Shot::shots.empty())
    {

        for(int i=0;i<Shot::shots.size();i++)
        {
            //printf("size = %d \n",Shot::shots.size());
            Shot::shots[i].draw();
        }
    }*/



    for(int i=0;i<Player::players.size();i++)
    {
        //printf("size = %d \n",Shot::shots.size());
        Player::players[i].draw();
    }

    for(int i=0;i<Alien::aliens.size();i++)
    {
        //printf("drawing alien num = %d pos %f , %f \n",i,Alien::aliens[i]->x,Alien::aliens[i]->y);
        Alien::aliens[i]->draw();
    }

    glColor3f(1,0.6,1);
    glBegin(GL_POLYGON);
    glVertex2d(80,-46.25);
    glVertex2d(100,-46.25);
    glVertex2d(100,-56.25);
    glVertex2d(80,-56.25);
    glEnd();


    if(warn>0){
        warn--;
        glColor3f(0.8,0,0);
        glBegin(GL_POLYGON);
        printf("drawing");
        //---------------start drawing body--------------
        glVertex2d(-100, -50);
        glVertex2d(100, -50);
        glVertex2d(100, -56);
        glVertex2d(-100, -56);
        glEnd();//---------------end drawing--------------
    }
    //glFlush();
    glutSwapBuffers();

    //printf("end display\n");



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
                    //printf("mouse clicked %f %f \n",worldX,worldY);
                    mouseflag=1;
                }

            }
            if(state == GLUT_UP)
            {

                if(worldX<=80 && worldY>=-46)
                {
                    //printf("mouse lifted %f %f \n",worldX,worldY);
                    if(mouseflag==1){
                        Player player(worldX,worldY);
                    }
                }
                mouseflag=0;

            }
        break;
    }
}
void shootingControl(int id)
{
    //printf("start shoot control\n");
    if((!Player::players[id].contacts.empty()) && Player::players[id].shots.empty()){
        double dirX=Alien::aliens[Player::players[id].contacts.front()]->x;
        double dirY=Alien::aliens[Player::players[id].contacts.front()]->y-5;
        Player::players[id].shoot(Player::players[id].contacts.front());
        glutTimerFunc(2000,shootingControl,id);
    }
   // printf("end shoot control\n");
}
void contactControl(int)
{
   // printf("start cont cont\n");
    for(int i=0; i<Player::players.size();i++)
    {
        if(!Player::players[i].contacts.empty())
        {
            continue;
        }
        for(int j=0; j<Alien::aliens.size(); j++)
        {
            if(Alien::aliens[j]->y>Player::players[i].y+10)
            {
                //printf("sadads\n");

                Player::players[i].contacts.push(j);
                glutTimerFunc(1000,shootingControl,i);

            }
            else
            {
                continue;
            }
        }
    }
    glutTimerFunc(1000/30,contactControl,0);
    //printf("end cont cont\n");
}








