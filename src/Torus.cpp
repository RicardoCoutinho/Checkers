#include "Torus.h"

Torus::Torus(GLfloat inner, GLfloat outer, GLint slices, GLint loops)
{
	setInner(inner);
	setOuter(outer);
	setSlices(slices);
	setLoops(loops);
}


GLfloat Torus::getInner(){return inner;}
GLfloat Torus::getOuter(){return outer;}
GLint Torus::getSlices(){return slices;}
GLint Torus::getLoops() {return loops;}


void Torus::setInner(GLfloat inner) {this->inner = inner;}
void Torus::setOuter(GLfloat outer) {this->outer = outer;}
void Torus::setSlices(GLint slices) {this->slices = slices;}
void Torus::setLoops(GLint loops) {this->loops = loops;}


void Torus::print()
{
	cout << "| | - Torus" << endl;
	cout << "| | | - inner: " << getInner() << endl;
	cout << "| | | - outer: " << getOuter() << endl;
	cout << "| | | - slices: " << getSlices() << endl;
	cout << "| | | - loops: " << getLoops() << endl;
}

void Torus::draw()
{
    glPushMatrix();
    
    glutSolidTorus(inner,outer,slices,loops);
    
    glPushMatrix();
    
}