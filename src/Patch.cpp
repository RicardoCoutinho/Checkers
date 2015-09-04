//
//  Patch.cpp
//  CGFLib-1

#include "Patch.h"

Patch::Patch(GLint order, GLint partsU, GLint partsV, string compute, vector <vector<GLfloat> >  controlpoints)
{
    this->order = order;
	this->partsU = partsU;
	this->partsV = partsV;
	this->compute = compute;
	this->controlpoints = controlpoints;
}

void Patch::print()
{
}

void Patch::draw()
{
	glEnable(GL_MAP2_VERTEX_3);
   // glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 2, 0.0, 1.0, 2 * 3, 2, &grid2x2[0][0][0]); 
	glMapGrid2f(partsU, 0.0, 1.0, partsV, 0.0, 1.0);
	glEvalMesh2(GL_LINE, 0, partsU, 0, partsV); 
}