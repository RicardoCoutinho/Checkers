//
//  Plane.cpp
//  CGFLib-1

#include "Plane.h"

GLfloat grid2x2[4][3] = { {-0.5, -0.5, 0.0}, {0.5, -0.5, 0.0},
						  {-0.5,  0.5, 0.0}, {0.5, 0.5, 0.0}};

GLfloat nrmlcompon[4][3] = { { 0.0, 1.0, 0.0}, { 0.0, 1.0, 0.0}, 
							 { 0.0, 1.0, 1.0}, { 0.0, 1.0, 0.0}};

GLfloat textpoints[4][2] = { { 0.0, 0.0}, { 0.0, 1.0}, { 1.0, 0.0},	{ 1.0, 1.0} };

Plane::Plane(GLint divisions)
{	
    this->divisions = divisions;	
}

GLint Plane::getDivisions()
{
	return divisions;
}

void Plane::setDivisions(GLint divisions)
{
	this->divisions = divisions;
}

void Plane::print()
{
    cout << "Divisons: " << divisions << endl;
}

void Plane::draw()
{		
	//glEnable(GL_MAP2_VERTEX_3);
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 2, 0.0, 1.0, 2 * 3, 2, &grid2x2[0][0]); 
	glMap2f(GL_MAP2_NORMAL,   0.0, 1.0, 3, 2,  0.0, 1.0, 6, 2,  &nrmlcompon[0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2,  0.0, 1.0, 2, 2,  0.0, 1.0, 4, 2,  &textpoints[0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_NORMAL);
	glEnable(GL_MAP2_TEXTURE_COORD_2);
	glMapGrid2f(divisions, 0.0, 1.0, divisions, 0.0, 1.0);
	glEvalMesh2(GL_FILL, 0, divisions, 0, divisions); 
	
}