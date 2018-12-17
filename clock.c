#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define PI 3.14159
static GLfloat spinUp = 0.0;
static GLfloat spinRight = 0.0;
static GLfloat minSpin = 0.0;
static GLfloat hourSpin = 0.0;
static GLfloat secondSpin = 0.0;
static int lock = 0;
float checkTime;
clock_t startSeconds, endSeconds;
clock_t startMins, endMins;

void getCurrentTime(void){ //corrects time to current time
    time_t rawtime;
    struct tm * timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    secondSpin = -((360 * timeinfo->tm_sec) / 60);
    minSpin = -((360 * timeinfo->tm_min) / 60);
    hourSpin = -(0.5*((60 * timeinfo->tm_hour) + timeinfo->tm_min));
    
}

void init(void){
    getCurrentTime();
    startSeconds = clock();
    startMins = clock();
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
    glEnable(GL_DEPTH_TEST);
}

void drawCircle(int x, int y, int z, int r){ //draws circles input = center and radius
	
	glBegin(GL_POLYGON);
	for(int i = 0; i < 50; i++){
		float theta = 2.0f * 3.1415926f * (float) i / (float)50;//get the current angle
    
        float tempX = r * cosf(theta);//calculate the x component
        float tempY = r * sinf(theta);//calculate the y component

        glVertex3f(x + tempX, tempY + y, z);//output vertex
	}
	glEnd();
}

void drawNumbers(){ //draws numbers on the clock   
    glColor3f(0,0,1);
    /* Number 1 */
    glBegin(GL_POLYGON);
     glVertex3f(-0.5,7.5,1.01);
     glVertex3f(-0.5,6,1.01);
     glVertex3f(-0.1,6,1.01);
     glVertex3f(-0.1,7.5,1.01);
    glEnd();
    glBegin(GL_POLYGON);
     glVertex3f(-0.5,7.5,1.01);
     glVertex3f(-0.5,7,1.01);
     glVertex3f(-0.8,6.5,1.01);
     glVertex3f(-0.8,7,1.01);
    glEnd();

    /* Number 2 */
    glBegin(GL_POLYGON);
     glVertex3f(1,7.5,1.01);
     glVertex3f(1,7,1.01);
     glVertex3f(0.1,7,1.01);
     glVertex3f(0.1,7.5,1.01);
    glEnd();
    glBegin(GL_POLYGON);
     glVertex3f(1,7,1.01);
     glVertex3f(0.7,7,1.01);
     glVertex3f(0.1,6.3,1.01);
     glVertex3f(0.4,6.3,1.01);
    glEnd();
    glBegin(GL_POLYGON);
     glVertex3f(0.1,6,1.01);
     glVertex3f(0.1,6.3,1.01);
     glVertex3f(1,6.3,1.01);
     glVertex3f(1,6,1.01);
    glEnd();
    
    /* Number 3 */

    glBegin(GL_POLYGON);
     glVertex3f(7.5,-1,1.01);
     glVertex3f(7.5,1,1.01);
     glVertex3f(7.2,1,1.01);
     glVertex3f(7.2,-1,1.01);
    glEnd();
    glBegin(GL_POLYGON);
     glVertex3f(6.7,-1,1.01);
     glVertex3f(6.7,-0.7,1.01);
     glVertex3f(7.2,-0.7,1.01);
     glVertex3f(7.2,-1,1.01);
    glEnd();
    glBegin(GL_POLYGON);
     glVertex3f(6.7,0.7,1.01);
     glVertex3f(6.7,1,1.01);
     glVertex3f(7.2,1,1.01);
     glVertex3f(7.2,0.7,1.01);
    glEnd();
    glBegin(GL_POLYGON);
     glVertex3f(6.7,-0.15,1.01);
     glVertex3f(6.7,0.15,1.01);
     glVertex3f(7.2,0.15,1.01);
     glVertex3f(7.2,-0.15,1.01);
    glEnd();
   
    /* Number 6 */

    glBegin(GL_POLYGON);
     glVertex3f(-0.4,-7.5,1.01);
     glVertex3f(-0.4,-6,1.01);
     glVertex3f(0.0,-6,1.01);
     glVertex3f(0.0,-7.5,1.01);
    glEnd();
    glBegin(GL_POLYGON);
     glVertex3f(0.6,-7.5,1.01);
     glVertex3f(0.6,-7.2,1.01);
     glVertex3f(0.0,-7.2,1.01);
     glVertex3f(0.0,-7.5,1.01);
    glEnd();
    glBegin(GL_POLYGON);
     glVertex3f(0.6,-6.8,1.01);
     glVertex3f(0.3,-6.8,1.01);
     glVertex3f(0.3,-7.2,1.01);
     glVertex3f(0.6,-7.2,1.01);
    glEnd();
    glBegin(GL_POLYGON);
     glVertex3f(0.6,-6.7,1.01);
     glVertex3f(0.6,-7.0,1.01);
     glVertex3f(0.0,-7.0,1.01);
     glVertex3f(0.0,-6.7,1.01);
    glEnd();
    
    /* Number 9 */

    glBegin(GL_POLYGON);
     glVertex3f(-7.2,-1,1.01);
     glVertex3f(-7.2,1,1.01);
     glVertex3f(-6.8,1,1.01);
     glVertex3f(-6.8,-1,1.01);
    glEnd();
    glBegin(GL_POLYGON);
     glVertex3f(-7.8,0,1.01);
     glVertex3f(-7.8,1,1.01);
     glVertex3f(-7.5,1,1.01);
     glVertex3f(-7.5,0,1.01);
    glEnd();
    glBegin(GL_POLYGON);
     glVertex3f(-6.8,0.7,1.01);
     glVertex3f(-6.8,1,1.01);
     glVertex3f(-7.7,1,1.01);
     glVertex3f(-7.7,0.7,1.01);
    glEnd();
    glBegin(GL_POLYGON);
     glVertex3f(-6.8,0,1.01);
     glVertex3f(-6.8,0.3,1.01);
     glVertex3f(-7.7,0.3,1.01);
     glVertex3f(-7.7,0,1.01);
    glEnd();

}

void drawClock(){ //draws clock
    glColor3f(0.56,0.47,0);
    drawCircle(0,0,0,10);
    glutSolidTorus(1,10,10,50);

    glColor3f(1,1,1);
    drawCircle(0,0,1,9);

    glLineWidth(2.5);
    glColor3f(0,0,1);
    glBegin(GL_LINES);
    glVertex3f(9,0,1.01);
    glVertex3f(8,0,1.01);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(-9,0,1.01);
    glVertex3f(-8,0,1.01);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(0,-9,1.01);
    glVertex3f(0,-8,1.01);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(0,9,1.01);
    glVertex3f(0,8,1.01);
    glEnd();

    glPushMatrix();
    glRotatef(hourSpin,0,0,1);

    glColor3f(0,0,0);
    glLineWidth(10);
    glBegin(GL_LINES);
    glVertex3f(0,5,1.01);
    glVertex3f(0,0,1.01);
    glEnd();

    glPopMatrix();
    glPushMatrix();
    glRotatef(minSpin,0,0,1);

    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex3f(0,6.5,1.02);
    glVertex3f(0,0,1.02);
    glEnd();

    glPopMatrix();
    glPushMatrix();
    glRotatef(secondSpin,0,0,1);

    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex3f(0,8,1.02);
    glVertex3f(0,0,1.02);
    glEnd();

    glPopMatrix();
}

void display(void){ // function to draw objects
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT, GL_FILL);

    glPushMatrix();
    glLoadIdentity();
    glScalef(3,3,3);
    glRotatef(spinUp, 1, 0, 0);
    glRotatef(spinRight, 0, 1, 0);

    drawClock(); 
    drawNumbers();

    glPopMatrix();
  
    glutSwapBuffers();

}

void spinDisplayRight(void){ //spins display to the right
    spinRight=spinRight+1;

    if (spinRight > 360.0)
        spinRight=spinRight-360.0; 
	
    glutPostRedisplay();
}
void spinDisplayLeft(void){ //spins display to the right
    spinRight=spinRight-1;

    if (spinRight < -360.0)
        spinRight=spinRight+360.0; 
	
    glutPostRedisplay();
}
void spinDisplayUp(void){//spins display to the up
    spinUp=spinUp+1;

    if (spinUp > 360.0)
        spinUp=spinUp-360.0; 
	
    glutPostRedisplay();
}
void spinDisplayDown(void){//spins display to the down
    spinUp=spinUp-1;

    if (spinUp < -360.0)
        spinUp=spinUp+360.0; 
	
    glutPostRedisplay();
}
void minAdvance(void){ //advances one min
    minSpin = minSpin-6;
    hourSpin = hourSpin-0.5;
    if (minSpin < -360.0)
        minSpin=minSpin+360.0; 
    if (hourSpin < -360.0)
        hourSpin=hourSpin+360.0; 
	
    glutPostRedisplay();
}
void minRecede(void){ //recedes one min
    minSpin = minSpin+6;
    hourSpin = hourSpin+0.5;
    if (minSpin > 360.0)
        minSpin=minSpin-360.0; 
	if (hourSpin > 360.0)
        hourSpin=hourSpin-360.0; 
    glutPostRedisplay();
}
void secondAdvance(void){//advances one second
    secondSpin = secondSpin-6;

    if (secondSpin < -360.0)
        secondSpin=secondSpin+360.0; 
	
    glutPostRedisplay();
}
void secondRecede(void){//recedes one second
    secondSpin = secondSpin+6;

    if (secondSpin > 360.0)
        secondSpin=secondSpin-360.0; 
	
    glutPostRedisplay();
}

void timeCounter(void){//keeps notion of time, moves clock pointers
    endSeconds = clock();

    float checkTime = endSeconds - startSeconds;
    if(((double)checkTime)/CLOCKS_PER_SEC > 1){
        startSeconds = clock();
        
        secondAdvance();
        printf("time: %f seconds\n", ((double)checkTime)/CLOCKS_PER_SEC);
    }

    endMins = clock();
    checkTime = endMins - startMins;

    if(((double)checkTime)/CLOCKS_PER_SEC > 60){
        startMins = clock();
        
        minAdvance();

        printf("time: %f seconds\n", ((double)checkTime)/CLOCKS_PER_SEC);
    }
    
}

void mouse(int button, int state, int x, int y){
    switch (button) {

    }
}

void keyboard(unsigned char key, int x, int y){
    switch (key) {
        case 'w':
            glutIdleFunc(spinDisplayDown);
            break;
        case 's':
            glutIdleFunc(spinDisplayUp);
            break;
        case 'a':
            glutIdleFunc(spinDisplayLeft);
            break;
        case 'd':
            glutIdleFunc(spinDisplayRight);
            break;
        case 'i':
            glutIdleFunc(minAdvance);
            break;
        case 'k':
            glutIdleFunc(minRecede);
            break;
        case 'n':
            getCurrentTime();
            break;
        case 'l':
            if(lock == 1){
                lock = 0;
                glutIdleFunc(timeCounter);
            } else {
                lock = 1;
                glutIdleFunc(NULL);
            }
            break;
        default:
            break;
    }
}

void keyUp (unsigned char key, int x, int y) {  
    switch (key) {
        case 'w':
            if(lock == 0){
                glutIdleFunc(timeCounter);
            } else {
                glutIdleFunc(NULL);
            }
            break;
        case 's':
            if(lock == 0){
                glutIdleFunc(timeCounter);
            } else {
                glutIdleFunc(NULL);
            }
            break;
        case 'a':
            if(lock == 0){
                glutIdleFunc(timeCounter);
            } else {
                glutIdleFunc(NULL);
            }
            break;
        case 'd':
            if(lock == 0){
                glutIdleFunc(timeCounter);
            } else {
                glutIdleFunc(NULL);
            }
            break;
        case 'u':
            if(lock == 0){
                glutIdleFunc(timeCounter);
            } else {
                glutIdleFunc(NULL);
            }
            break;
        case 'j':
            if(lock == 0){
                glutIdleFunc(timeCounter);
            } else {
                glutIdleFunc(NULL);
            }
            break;
        case 'i':
            if(lock == 0){
                glutIdleFunc(timeCounter);
            } else {
                glutIdleFunc(NULL);
            }
            break;
        case 'k':
            if(lock == 0){
                glutIdleFunc(timeCounter);
            } else {
                glutIdleFunc(NULL);
            }
            break;
        default:
            break;
    }
} 

void reshape(int w, int h){
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50.0, 50.0, -50.0, 50.0, -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 900);
    glutInitWindowPosition(500, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyUp);
    glutIdleFunc(timeCounter);
    glutMainLoop();
    return 0;
}
