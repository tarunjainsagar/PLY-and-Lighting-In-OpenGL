/*
	Author: Tarun Jain
	Roll Number: MT2015120
	Title: Assignment 2 Computer Graphics: 3D Model with Lighting
*/
#include "myheaderfile.h"

Controller controller;

// Keyboard Function
void keyboard( unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'i': 
			zoom[0] += 0.1;
			zoom[1] += 0.1;
			zoom[2] += 0.1;
			break;
		case 'o': 
			zoom[0] -= 0.1;
			zoom[1] -= 0.1;
			zoom[2] -= 0.1;
			break;
		case 27:
			exit(0);
	}
	glutPostRedisplay();
}

void Controller :: lighting()
{
	glPointSize(6);
	// Setting the Light Points
	glBegin(GL_POINTS);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(-0.6, -0.6, -(farZ + 0.111));
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.6, 0.6, -(farZ + 0.111));
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(-0.6, 0.6, -(farZ + 0.111));
		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(0.6, -0.6, -(farZ + 0.111));
	glEnd();
	
	GLfloat ambientColor[] = { 0.6f, 0.6f, 0.6f, 1.0f};
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, ambientColor);
	
	GLfloat lightColor0[] = { 0.5f, 0.5f, 0.5f, 1.0f};
	GLfloat lightPos0[] = { 1.5f, 2.5f, 0.0f, 1.0f};
	glLightfv( GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv( GL_LIGHT0, GL_POSITION, lightPos0);	

	GLfloat lightColor1[] = { 0.0f, 1.0f, 0.0f, 1.0f};
	GLfloat lightPos1[] = { -0.6, -0.6, -(farZ + 0.111), 0.0f};
	glLightfv( GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv( GL_LIGHT1, GL_POSITION, lightPos1);	
	
	GLfloat lightColor2[] = { 1.0f, 0.0f, 0.0f, 1.0f};
	GLfloat lightPos2[] = { 0.6, -0.6, -(farZ + 0.111), 0.0f};
	glLightfv( GL_LIGHT2, GL_DIFFUSE, lightColor2);
	glLightfv( GL_LIGHT2, GL_POSITION, lightPos2);	
	
	GLfloat lightColor3[] = { 1.0f, 1.0f, 0.0f, 1.0f};
	GLfloat lightPos3[] = { -0.6, 0.6, -(farZ + 0.111), 0.0f};
	glLightfv( GL_LIGHT3, GL_DIFFUSE, lightColor3);
	glLightfv( GL_LIGHT3, GL_POSITION, lightPos3);	

	
}

// Timer Function
void update(int value)
{
	if( count < 25)
	{	
		glEnable( GL_LIGHT0);
		glDisable( GL_LIGHT1);
		glDisable( GL_LIGHT2);
		glDisable( GL_LIGHT3);
		count++;
	}
	else if( count >= 25 && count < 50 )
	{	
		glEnable( GL_LIGHT1);
		glDisable( GL_LIGHT0);
		glDisable( GL_LIGHT2);
		glDisable( GL_LIGHT3);
		count++;
	}
	else if( count >= 50 && count < 75 )
	{	
		glEnable( GL_LIGHT2);
		glDisable( GL_LIGHT0);
		glDisable( GL_LIGHT1);
		glDisable( GL_LIGHT3);
		count++;
	}
	else if( count >= 75  && count < 100 )
	{	
		glEnable( GL_LIGHT3);
		glDisable( GL_LIGHT0);
		glDisable( GL_LIGHT1);
		glDisable( GL_LIGHT2);
		count++;
	}
	else
		count = 0;
	glutPostRedisplay();
	glutTimerFunc(100, update, 0);
}

void Controller :: quaternion(char ch,int angle)
{
    float quaternionRotateMatrix[16]={ 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
    
    float vx = 0.0,vy = 0.0,vz = 0.0,qCOS,qSINx,qSINy,qSINz;
	switch(ch)
	{
	    case 'x':   vx = 1.0;
                    vy = 0.0;
                    vz = 0.0;
                    break;
		case 'y':   vx = 0.0;
                    vy = 1.0;
                    vz = 0.0;
                    break;
		case 'z':   vx = 0.0;
                    vy = 0.0;
                    vz = 1.0;
                    break;
	}
	float radAngle = M_PI * angle/180;
    qCOS = cos(radAngle/2);
	qSINx = sin(radAngle/2) * vx;
	qSINy = sin(radAngle/2) * vy;
	qSINz = sin(radAngle/2) * vz;

	quaternionRotateMatrix[0] = 1.0f - 2.0f * qSINy * qSINy - 2.0f * qSINz * qSINz ;
	quaternionRotateMatrix[4] = 2.0f * qSINx * qSINy - 2.0f * qCOS * qSINz;
	quaternionRotateMatrix[8] = 2.0f * qSINx * qSINz + 2.0f * qCOS * qSINy;
	quaternionRotateMatrix[12] = 0.0f;

	quaternionRotateMatrix[1] = 2.0f * qSINx * qSINy + 2.0f * qCOS * qSINz;
	quaternionRotateMatrix[5] = 1.0f - 2.0f * qSINx * qSINx - 2.0f * qSINz * qSINz;
	quaternionRotateMatrix[9] = 2.0f * qSINy * qSINz - 2.0f * qCOS * qSINx;
	quaternionRotateMatrix[13] = 0.0f;

	quaternionRotateMatrix[2] = 2.0f * qSINx * qSINz - 2.0f * qCOS * qSINy;
	quaternionRotateMatrix[6] = 2.0f * qSINy * qSINz + 2.0f * qCOS * qSINx;
	quaternionRotateMatrix[10] = 1.0f - 2.0f * qSINx * qSINx - 2.0f * qSINy * qSINy;
	quaternionRotateMatrix[14] = 0.0f;

	quaternionRotateMatrix[3] = 0.0f;
	quaternionRotateMatrix[7] = 0.0f;
	quaternionRotateMatrix[11] = 0.0f;
	quaternionRotateMatrix[15] = 1.0f;

	glMultMatrixf(quaternionRotateMatrix);
}


void Controller :: dragRotation(int xPos, int yPos) 
{

	trackBallRotate[0] -= ((yPos - currentY) * 180.0f) / 100.0f;
	trackBallRotate[1] -= ((xPos - currentX) * 180.0f) / 100.0f;
	for (int i = 0; i < 3; i ++)
		if (trackBallRotate[i] > 360 || trackBallRotate[i] < -360)
			trackBallRotate[i] = 0.0f;
	currentX = xPos;
	currentY = yPos;
}

void mouseMotion (int x, int y) 
{

    if (mState == GLUT_LEFT_BUTTON) 
    {
        controller.dragRotation (x, y);
    }
}

void mouse( int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ) 
	{
        	mState = GLUT_LEFT_BUTTON;
        	currentX = x;
        	currentY = y;
	}
}

