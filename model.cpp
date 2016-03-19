/*
	Author: Tarun Jain
	Roll Number: MT2015120
	Title: Assignment 2 Computer Graphics: 3D Model with Lighting
*/

#include "myheaderfile.h"

// Global Variables
float zoom[3];
int win_size_x = 500;
int win_size_y = 500;
float _angle = 0.0;
int currentX = 0;
int currentY = 0;
float trackBallRotate[3] ;
int mState;
int nov = 35947;
int nof = 69451;
int count_vertex = 0;
int count_face = 0;
double leftX = win_size_x /2;
double rightX = -win_size_x /2;
double topY = -win_size_y /2;
double bottomY = win_size_y /2;
double nearZ = 200.0f;
double farZ = -1.0f;
readPly vertices[35947];
readPly faces[69451];
readPly normals[69451];
Model model;

// Set Value of Vertex of an Object
void readPly :: setter_vertex(int i, double value)
{
	if( i == 0)
		x = value;
	if( i == 1)
		y = value;
	if( i == 2)
		z = value;
}

// Retrieve Value of Vertex of an Object
double readPly :: getter( int i)
{
	if( i == 0)
		return x;
	if( i == 1)
		return y;
	if( i == 2)
		return z;
}

// Callback Function for Vertex
int vertex_cb(p_ply_argument argument) 
{
	static int index = 0;
	long eol;
	ply_get_argument_user_data(argument, NULL, &eol);
	double temp = ply_get_argument_value(argument);

	if( index == 0 )
	{
		if( leftX > temp)
			leftX = temp;
		if( rightX < temp)
			rightX = temp;
	}
	if( index == 1 )
	{
		if( topY < temp)
			topY = temp;
		if( bottomY > temp)
			bottomY = temp;
	}
	if( index == 2 )
	{
		if( nearZ > temp)
			nearZ = temp;
		if( farZ < temp)
			farZ = temp;
	}
	
	vertices[ count_vertex].setter_vertex( index++, temp); 

	if (eol) 
	{
		index = 0;
		count_vertex++;
	}
	return 1;
}

// Callback Function for Faces
int face_cb(p_ply_argument argument) 
{
	long length, value_index;
	static int index = 0;
	ply_get_argument_property(argument, NULL, &length, &value_index);
	double temp;
	switch (value_index) 
	{
		case 0:
	        case 1: 
			temp = ply_get_argument_value(argument);
	        	faces[ count_face].setter_vertex( index++, temp);
        		break;
	        case 2:
			temp = ply_get_argument_value(argument);
	        	faces[ count_face].setter_vertex( index++, temp);
	        	index = 0;
	        	count_face++;
        		break;
		default:
			break;
    	}
    	return 1;
}

int Model :: entry() 
{
	long nvertices, ntriangles;
	// Open Ply File and Get Handle
	p_ply ply = ply_open("bunny.ply", NULL, 0, NULL);
	
	// not a ply file
	if (!ply) 
		return 1;
	// Parse Header
	if (!ply_read_header(ply)) 
		return 1;
		
	// Read 1st Element type and specified properties
	nvertices = ply_set_read_cb(ply, "vertex", "x", vertex_cb, NULL, 0);
	ply_set_read_cb(ply, "vertex", "y", vertex_cb, NULL, 0);
	ply_set_read_cb(ply, "vertex", "z", vertex_cb, NULL, 1);
	
	// Read 2nd Element type and specified properties
	ntriangles = ply_set_read_cb(ply, "face", "vertex_indices", face_cb, NULL, 0);

	// Read all vertices and faces
	if (!ply_read(ply)) 
		return 1;

	// Close Ply File
	ply_close(ply);
	return 0;
}

void Model :: initNormals()
{
	int i;
	double s[3], t[3], v[3], length;
	
	for( i = 0; i < nof; i++)
	{
		// Finding Vectors
		s[0] = vertices[(int)faces[i].getter(1)].getter(0) - vertices[(int)faces[i].getter(0)].getter(0);
		s[1] = vertices[(int)faces[i].getter(1)].getter(1) - vertices[(int)faces[i].getter(0)].getter(1);
		s[2] = vertices[(int)faces[i].getter(1)].getter(2) - vertices[(int)faces[i].getter(0)].getter(2);
		
		t[0] = vertices[(int)faces[i].getter(2)].getter(0) - vertices[(int)faces[i].getter(0)].getter(0);
		t[1] = vertices[(int)faces[i].getter(2)].getter(1) - vertices[(int)faces[i].getter(0)].getter(1);
		t[2] = vertices[(int)faces[i].getter(2)].getter(2) - vertices[(int)faces[i].getter(0)].getter(2);
		
		// Cross Product
		v[0] = s[1] * t[2] - t[1] * s[2]; 
		v[1] = s[2] * t[0] - t[2] * s[0];
		v[2] = s[0] * t[1] - t[0] * s[1];
		
		// Normalization Factor
		length = sqrt( ( v[0] * v[0] ) + (v[1] * v[1]) + (v[2] * v[2]) );
		
		normals[i].setter_vertex(0 , (v[0] / length));
		normals[i].setter_vertex(1 , (v[1] / length));
		normals[i].setter_vertex(2 , (v[2] / length));
		
	}
}

// Initialize
void Model :: initRendering()
{
	glEnable( GL_DEPTH_TEST);
	glEnable( GL_COLOR_MATERIAL);
	glEnable( GL_LIGHTING);
	glEnable( GL_LIGHT0);
	glEnable( GL_LIGHT1);
	glEnable( GL_LIGHT2);
	glEnable( GL_LIGHT3);	
	glEnable( GL_NORMALIZE);
	zoom[0] = 1.0;
	zoom[1] = 1.0;
	zoom[2] = 1.0;
	model.initNormals();
}



// Main
int main( int argc, char **argv)
{
	model.entry();
	glutInit( &argc, argv);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize( win_size_x, win_size_y);
	glutInitWindowPosition( 100, 200);
	glutCreateWindow( argv[1]);
	
	model.initRendering();
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);	
	glutTimerFunc(100, update, 0);
	glutMainLoop();
	return 0;
}
