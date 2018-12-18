#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define PI 3.1415
static char header[100] = "Hypno Clock";
const char name[] = "| Hypno Clock ";
static GLint fpsCount = 0;
static GLfloat spinUp = 0.0;
static GLfloat spinRight = 0.0;
static GLfloat clockRotation = 0.0;
static GLfloat minSpin = 0.0;
static GLfloat hourSpin = 0.0;
static GLfloat secondSpin = 0.0;
static GLfloat analogDistance = 0;
static GLfloat digitalDistance = 0;
static GLfloat analogPos = 0;
static GLfloat digitalPos = -50;
static GLfloat clockBalance = 0;
static GLint right = 1;
static GLint barrelRoll = 0;
static GLfloat alpha = 0;
static GLfloat changer = 0.01;
static GLfloat rotateZ = 0.0;

float checkTime;
clock_t startSeconds, endSeconds;
clock_t startMins, endMins;

void fpsCounter(void){//fpsCounter
    endSeconds = clock();
    fpsCount++;
    float checkTime = endSeconds - startSeconds;
    if(((double)checkTime)/CLOCKS_PER_SEC >= 1){
        startSeconds = clock();
        
        printf("%d fps\n", fpsCount);
        sprintf(header, "%d fps ", fpsCount);
        strcat(header, name);
        glutSetWindowTitle(header);

        fpsCount = 0;
    }    
}

void animateHypno(void){//calculates transparacy and rotation
    rotateZ = rotateZ + 0.5;
    if(alpha > 1 || alpha < 0){
        changer = changer * -1;
    }
    alpha = alpha + changer;
    
    if(rotateZ <= 359){
        rotateZ = rotateZ - 358;
    }
}

void calculateClockAngle(void){ //calculates clock angle 

    if(right == 1 && barrelRoll != 1){
        clockBalance = clockBalance + 0.5;

        if(clockBalance == 20){
            right = 0;
        }
    } else if(right == 0 && barrelRoll != 1){
        clockBalance = clockBalance - 0.5;

        if(clockBalance == -20){
            right = 1;
        }
    }
}

/*struct tm */void getCurrentTime(void){ //corrects time to current time
    calculateClockAngle();

    time_t rawtime;
    struct tm * timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    secondSpin = -((360 * timeinfo->tm_sec) / 60);
    minSpin = -((360 * timeinfo->tm_min) / 60);
    hourSpin = -(0.5*((60 * timeinfo->tm_hour) + timeinfo->tm_min));

    glutPostRedisplay();
    
    // return timeinfo;
}

void init(void){
    getCurrentTime();
    startSeconds = clock();
    startMins = clock();
    
    GLfloat ambientLight[] = {0.3,0.3,0.3,1};
    GLfloat diffuseLight[] = {0.7,0.7,0.7,1};
    GLfloat lightPos[] = {10,0,-10,1};

    //enables transparacy
    glEnable (GL_BLEND); 
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //enables lighting
    glEnable(GL_LIGHTING);
    
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glShadeModel (GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    // glFrontFace(GL_CCW);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void drawCircle(float x, float y, float z, float r){ //draws circles input = center and radius
	
	glBegin(GL_POLYGON);
	for(int i = 0; i < 50; i++){
		float theta = 2.0f * 3.1415926f * (float) i / (float)50;//get the current angle
    
        float tempX = r * cosf(theta);//calculate the x component
        float tempY = r * sinf(theta);//calculate the y component

         glVertex3f(x + tempX, tempY + y, z);//output vertex
	}
	glEnd();
}

void drawCircleDifferentColors(float x, float y, float z, float r){ //draws circles input = center and radius
    
    for(int i = 0; i <= 10; i++){
        if(i%2==0){
            glColor4f(0,0,0,alpha);
        } else {
            glColor4f(1,1,1,alpha);
        }
	    glBegin(GL_POLYGON);
         glVertex3f(0,0,0);
        
        for(int j = i*5; j < (i+1)*10; j++){
            float theta = 2.0f * 3.1415926f * (float) j / (float)100;//get the current angle

            float tempX = r * cosf(theta);//calculate the x component
            float tempY = r * sinf(theta);//calculate the y component
             glVertex3f(x + tempX, tempY + y, z);//output vertex
        }

        glEnd();
    }
}

void drawChain(void){
    glColor3f(0.56,0.47,0);
    glPushMatrix();
    
    glTranslatef(0,12,0);
    glutSolidTorus(1,2,20,50);

    glPopMatrix();
    glPushMatrix();

    glRotated(90,0,1,0);
    glTranslatef(0,16,0);
    glutSolidTorus(1,4,20,50);

    glPopMatrix();
    glPushMatrix();

    glTranslatef(0,22,0);
    glutSolidTorus(1,4,20,50);

    glPopMatrix();
    glPushMatrix();

    glRotated(90,0,1,0);
    glTranslatef(0,28,0);
    glutSolidTorus(1,4,20,50);

    glPopMatrix();
}

void drawAnalogNumbers(void){ //draws numbers on the clock   
    glColor3f(0,0,1);
    /* Number 1 */
    glBegin(GL_POLYGON);
     glVertex3f(-0.5,7.5,analogDistance+0.51);
     glVertex3f(-0.5,6,analogDistance+0.51);
     glVertex3f(-0.1,6,analogDistance+0.51);
     glVertex3f(-0.1,7.5,analogDistance+0.51);
     glVertex3f(-0.5,7.5,analogDistance+0.51);
     glVertex3f(-0.5,7,analogDistance+0.51);
     glVertex3f(-0.8,6.5,analogDistance+0.51);
     glVertex3f(-0.8,7,analogDistance+0.51);
    glEnd();

    /* Number 2 */
    glBegin(GL_POLYGON);
     glVertex3f(1,7.5,analogDistance+0.51);
     glVertex3f(1,7,analogDistance+0.51);
     glVertex3f(0.1,7,analogDistance+0.51);
     glVertex3f(0.1,7.5,analogDistance+0.51);
    glEnd();
    glBegin(GL_POLYGON);
     glVertex3f(1,7,analogDistance+0.51);
     glVertex3f(0.7,7,analogDistance+0.51);
     glVertex3f(0.1,6.3,analogDistance+0.51);
     glVertex3f(0.4,6.3,analogDistance+0.51);
    glEnd();
    glBegin(GL_POLYGON);
     glVertex3f(0.1,6,analogDistance+0.51);
     glVertex3f(0.1,6.3,analogDistance+0.51);
     glVertex3f(1,6.3,analogDistance+0.51);
     glVertex3f(1,6,analogDistance+0.51);
    glEnd();
    
    /* Number 3 */

    glBegin(GL_POLYGON);
     glVertex3f(7.5,-1,analogDistance+0.51);
     glVertex3f(7.5,1,analogDistance+0.51);
     glVertex3f(7.2,1,analogDistance+0.51);
     glVertex3f(7.2,-1,analogDistance+0.51);
    glEnd();
    glBegin(GL_POLYGON);
     glVertex3f(6.7,-1,analogDistance+0.51);
     glVertex3f(6.7,-0.7,analogDistance+0.51);
     glVertex3f(7.2,-0.7,analogDistance+0.51);
     glVertex3f(7.2,-1,analogDistance+0.51);
    glEnd();
    glBegin(GL_POLYGON);
     glVertex3f(6.7,0.7,analogDistance+0.51);
     glVertex3f(6.7,1,analogDistance+0.51);
     glVertex3f(7.2,1,analogDistance+0.51);
     glVertex3f(7.2,0.7,analogDistance+0.51);
    glEnd();
    glBegin(GL_POLYGON);
     glVertex3f(6.7,-0.15,analogDistance+0.51);
     glVertex3f(6.7,0.15,analogDistance+0.51);
     glVertex3f(7.2,0.15,analogDistance+0.51);
     glVertex3f(7.2,-0.15,analogDistance+0.51);
    glEnd();
   
    /* Number 6 */

    glBegin(GL_POLYGON);
     glVertex3f(-0.4,-7.5,analogDistance+0.51);
     glVertex3f(-0.4,-6,analogDistance+0.51);
     glVertex3f(0.0,-6,analogDistance+0.51);
     glVertex3f(0.0,-7.5,analogDistance+0.51);
    glEnd();
    glBegin(GL_POLYGON);
     glVertex3f(0.6,-7.5,analogDistance+0.51);
     glVertex3f(0.6,-7.2,analogDistance+0.51);
     glVertex3f(0.0,-7.2,analogDistance+0.51);
     glVertex3f(0.0,-7.5,analogDistance+0.51);
    glEnd();
    glBegin(GL_POLYGON);
     glVertex3f(0.6,-6.8,analogDistance+0.51);
     glVertex3f(0.3,-6.8,analogDistance+0.51);
     glVertex3f(0.3,-7.2,analogDistance+0.51);
     glVertex3f(0.6,-7.2,analogDistance+0.51);
    glEnd();
    glBegin(GL_POLYGON);
     glVertex3f(0.6,-6.7,analogDistance+0.51);
     glVertex3f(0.6,-7.0,analogDistance+0.51);
     glVertex3f(0.0,-7.0,analogDistance+0.51);
     glVertex3f(0.0,-6.7,analogDistance+0.51);
    glEnd();
    
    /* Number 9 */

    glBegin(GL_POLYGON);
     glVertex3f(-7.2,-1,analogDistance+0.51);
     glVertex3f(-7.2,1,analogDistance+0.51);
     glVertex3f(-6.8,1,analogDistance+0.51);
     glVertex3f(-6.8,-1,analogDistance+0.51);
    glEnd();
    glBegin(GL_POLYGON);
     glVertex3f(-7.8,0,analogDistance+0.51);
     glVertex3f(-7.8,1,analogDistance+0.51);
     glVertex3f(-7.5,1,analogDistance+0.51);
     glVertex3f(-7.5,0,analogDistance+0.51);
    glEnd();
    glBegin(GL_POLYGON);
     glVertex3f(-6.8,0.7,analogDistance+0.51);
     glVertex3f(-6.8,1,analogDistance+0.51);
     glVertex3f(-7.7,1,analogDistance+0.51);
     glVertex3f(-7.7,0.7,analogDistance+0.51);
    glEnd();
    glBegin(GL_POLYGON);
     glVertex3f(-6.8,0,analogDistance+0.51);
     glVertex3f(-6.8,0.3,analogDistance+0.51);
     glVertex3f(-7.7,0.3,analogDistance+0.51);
     glVertex3f(-7.7,0,analogDistance+0.51);
    glEnd();

}

void drawAnalogClock(void){ //draws analog clock
    glColor3f(0.56,0.47,0);
    drawCircle(0,0,analogDistance-1,10);

    glutSolidTorus(1,10,20,50);

    glColor3f(1,1,1);
    drawCircle(0,0,analogDistance+0.5,9);

    glLineWidth(2.5);
    glColor3f(0,0,1);
    glBegin(GL_LINES);
     glVertex3f(9,0,analogDistance+0.51);
     glVertex3f(8,0,analogDistance+0.51);
    glEnd();
    glBegin(GL_LINES);
     glVertex3f(-9,0,analogDistance+0.51);
     glVertex3f(-8,0,analogDistance+0.51);
    glEnd();
    glBegin(GL_LINES);
     glVertex3f(0,-9,analogDistance+0.51);
     glVertex3f(0,-8,analogDistance+0.51);
    glEnd();
    glBegin(GL_LINES);
     glVertex3f(0,9,analogDistance+0.51);
     glVertex3f(0,8,analogDistance+0.51);
    glEnd();

    glPushMatrix();
    glRotatef(hourSpin,0,0,1);

    glColor3f(0,0,0);
    glLineWidth(10);
    glBegin(GL_LINES);
     glVertex3f(0,5,analogDistance+0.51);
     glVertex3f(0,0,analogDistance+0.51);
    glEnd();

    glPopMatrix();
    glPushMatrix();
    glRotatef(minSpin,0,0,1);

    glLineWidth(5);
    glBegin(GL_LINES);
     glVertex3f(0,6.5,analogDistance+0.52);
     glVertex3f(0,0,analogDistance+0.52);
    glEnd();

    glPopMatrix();
    glPushMatrix();
    glRotatef(secondSpin,0,0,1);

    glLineWidth(4);
    glBegin(GL_LINES);
     glVertex3f(0,8,analogDistance+0.52);
     glVertex3f(0,0,analogDistance+0.52);
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
    glRotatef(clockRotation, 0, 1, 0);
    glRotatef(clockBalance, 0, 0, 1);
    glTranslatef(analogPos,-30,-20);
    glRotatef(spinRight, 0, 1, 0);

    //draws analog clock
    drawAnalogClock(); 
    drawChain();
    drawAnalogNumbers();

    glPopMatrix();

    glPushMatrix(); 
    glScalef(3,3,3);

    animateHypno();

    glRotatef(spinUp, 1, 0, 0);
    glRotatef(clockBalance, 0, 0, 1);
    glTranslatef(analogPos,-30,-18.5);
    glRotatef(spinRight, 0, 1, 0);
    glRotatef(rotateZ,0,0,1);

    drawCircleDifferentColors(0,0,0,9);

    glPopMatrix();

    fpsCounter();
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
        default:
            break;
    }
}

void keyUp (unsigned char key, int x, int y) {  
    switch (key) {
        case 'w':
            glutIdleFunc(getCurrentTime);
            break;
        case 's':
            glutIdleFunc(getCurrentTime);
            break;
        case 'a':
            glutIdleFunc(getCurrentTime);
            break;
        case 'd':
            glutIdleFunc(getCurrentTime);
            break;
        default:
            break;
    }
} 

void reshape(int w, int h){
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-75.0, 75.0, -125, 25, -200.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 900);
    glutInitWindowPosition(500, 100);
    glutCreateWindow(header);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyUp);
    glutIdleFunc(getCurrentTime);
    glutMainLoop();
    return 0;
}