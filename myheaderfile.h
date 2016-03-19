/*
	Author: Tarun Jain
	Roll Number: MT2015120
	Title: Assignment 2 Computer Graphics: 3D Model with Lighting
*/


// MyHeaderFile.h
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <stdlib.h>
#include "rply.h"

// Read and Store Ply File - Class
class readPly
{
	private:
		double x;
		double y;
		double z;
	public:
		double getter(int i);
		void setter_vertex( int i , double value);
};
// Model Class
class Model
{
	public:
		int entry();
		void initNormals();
		void initRendering();
} extern model;


// Controller Class
class Controller
{
	public:
		void lighting();
		void quaternion(char ,int );
		void dragRotation(int, int);
} extern controller;

// View Class
class View
{
	public:
		void drawAxis();
		void drawBox();
		void drawBunny();
}extern view;

extern int count_vertex;		// For Vertex counting
extern int win_size_x;			// Display Window Width
extern int win_size_y;			// Display Window Height

extern double leftX;			// Extreme Point on -X axis of OBJECT(Bunny)
extern double rightX;			// Extreme Point on +X axis of OBJECT(Bunny)
extern double topY;			// Extreme Point on +Y axis of OBJECT(Bunny)
extern double bottomY;			// Extreme Point on -Y axis of OBJECT(Bunny)
extern double nearZ;			// Extreme Point on +Z axis of OBJECT(Bunny)
extern double farZ ;			// Extreme Point on +Z axis of OBJECT(Bunny) 

// Object of Class ReadPly
extern readPly vertices[35947];		// Stores Vertices
extern readPly faces[69451];		// Stores Faces
extern readPly normals[69451];		// Stores Normal of Each Face

extern int currentX;			// Current X position of mouse
extern int currentY;			// Current Y position of mouse
extern int nov;				// Number of Vertices
extern int nof;				// Number of Faces
extern float trackBallRotate[3] ;	// Instantiate the trackball
extern int mState;			// Store Mouse State
static int count = 0;			// Timer for Light Change
extern float zoom[3];			// For Scaling


// Function Prototype
int vertex_cb( p_ply_argument);
int face_cb(p_ply_argument );
void update(int);
void keyboard( unsigned char, int, int);
void mouseMotion (int , int );
void mouse( int , int, int, int);
void display();

// Model Functions
int entry();
void initRendering();
void initNormals();

// Controller Functions
void quaternion(char ,int );
void lighting();
void dragRotation(int, int);

// View Functions
void drawAxis();
void drawBox();
void drawBunny();


