/*
	Author: Tarun Jain
	Roll Number: MT2015120
	Title: Assignment 2 Computer Graphics: 3D Model with Lighting
*/

#include "myheaderfile.h"

View view;

void View ::drawBunny()
{
	int n;
	glPushMatrix();	
	glColor3f( 0.75, 0.75, 1.0);
	for( n =0; n < nof; n++)
	{
		glBegin(GL_POLYGON);
			glNormal3f( normals[n].getter(0),normals[n].getter(1), normals[n].getter(2) );
			int face_no = faces[n].getter(0);
			glVertex3f( vertices[face_no].getter(0), vertices[face_no].getter(1), vertices[face_no].getter(2)); 

			face_no = faces[n].getter(1);
			glVertex3f( vertices[face_no].getter(0), vertices[face_no].getter(1), vertices[face_no].getter(2)); 

			face_no = faces[n].getter(2);
			glVertex3f( vertices[face_no].getter(0), vertices[face_no].getter(1), vertices[face_no].getter(2)); 
		glEnd();
	}
	glPopMatrix(); 
	glutPostRedisplay();
}
void View ::drawBox()
{
	glPushMatrix();
	glBegin( GL_LINES);
		glColor3f( 1.0, 1.0,0.0);		
		// Front Box
		float trans_z1 = nearZ - 0.111;
		glVertex3f(-0.2, -0.05, trans_z1);			//A	// Bottom Line
		glVertex3f(0.2, -0.05, trans_z1);			//B	
		glVertex3f(-0.2, 0.28, trans_z1);			//C	// Top Line
		glVertex3f(0.2, 0.28, trans_z1);			//D
		glVertex3f(-0.2, -0.05, trans_z1);			//A	// Left Line
		glVertex3f(-0.2, 0.28, trans_z1);			//C
		glVertex3f(0.2, -0.05, trans_z1);			//B	// Right Line
		glVertex3f(0.2, 0.28, trans_z1);			//D
		
		// Back box
		//glTranslatef(0.0, 0.0,-0.5);
		float trans_z2 = farZ + 0.111;
		glVertex3f(-0.2, -0.05, trans_z2);			//A1	// Bottom Line
		glVertex3f(0.2, -0.05, trans_z2);			//B1	
		glVertex3f(-0.2, 0.28, trans_z2);			//C1	// Top Line
		glVertex3f(0.2, 0.28, trans_z2);			//D1
		glVertex3f(-0.2, -0.05, trans_z2);			//A1	// Left Line
		glVertex3f(-0.2, 0.28, trans_z2);			//C1
		glVertex3f(0.2, -0.05, trans_z2);			//B1	// Right Line
		glVertex3f(0.2, 0.28, trans_z2);			//D1
		
		// Side Line Left
		glVertex3f(-0.2, -0.05, trans_z1);			//A	// Bottom Line
		glVertex3f(-0.2, -0.05, trans_z2);			//A1	// Bottom Line
		glVertex3f(-0.2, 0.28, trans_z1);			//C	// Top Line
		glVertex3f(-0.2, 0.28, trans_z2);			//C1	// Top Line

		// Side Line Right
		glVertex3f(0.2, -0.05, trans_z1);			//B	
		glVertex3f(0.2, -0.05, trans_z2);			//B1	
		glVertex3f(0.2, 0.28, trans_z1);			//D
		glVertex3f(0.2, 0.28, trans_z2);			//D1
	glEnd();
	
	glPopMatrix();
	glutPostRedisplay();
}
void View :: drawAxis()
{
	glPushMatrix();
	glBegin( GL_LINES);
		glColor3f( 1.0, 0.0,0.0);
		glVertex3f(-250.0, 0.0, -1.0f);
		glVertex3f(250.0, 0.0, -1.0f);		
	glEnd();
	glBegin( GL_LINES);
		glColor3f( 0.0, 0.0,1.0);
		glVertex3f(0.0, -250.0, -1.0f);
		glVertex3f(0.0, 250.0, -1.0f);		
	glEnd();
	glPopMatrix();
	glutPostRedisplay();
}

// Display
void display()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode( GL_MODELVIEW);
	glLoadIdentity(); 
	view.drawAxis();
	glPushMatrix();
		controller.quaternion( 'x',trackBallRotate[0]) ;
		controller.quaternion( 'y',trackBallRotate[1]) ;
		glScalef(zoom[0],zoom[1], zoom[2]);
		glTranslatef( 0.0, -0.1f, 0.0f);
		view.drawBox();
		view.drawBunny();
	
	glPopMatrix();
	controller.lighting();
	glutSwapBuffers();
}
