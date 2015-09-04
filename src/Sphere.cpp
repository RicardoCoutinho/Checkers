#include "Sphere.h"

Sphere::Sphere(GLfloat radius, GLint slices, GLint stacks)
{
   setRadius(radius);
   setRadius(slices);
   setRadius(stacks);
}

GLfloat Sphere::getRadius() {return radius;}
GLint Sphere::getSlices() {return slices;}
GLint Sphere::getStacks() {return stacks;}


void Sphere::setRadius(GLfloat radius) {this->radius = radius;}
void Sphere::setSlices(GLint slices) {this->slices = slices;}
void Sphere::setStacks(GLint stacks) {this->stacks = stacks;}


void Sphere::print()
{
	cout << "| | -Sphere" << endl;
    cout << "| | | - radius: " << getRadius() << endl;
	cout << "| | | - slices: " << getSlices() << endl;
	cout << "| | | - stacks: " << getStacks() << endl;
}

void Sphere::draw()
{
    glPushMatrix();
    
    GLUquadric* quadric = gluNewQuadric();
    gluQuadricDrawStyle( quadric, GLU_FILL );
    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluQuadricTexture( quadric, GL_TRUE );
    
    gluSphere(quadric, radius, slices, stacks);
    
    gluQuadricTexture( quadric, GL_FALSE );
    gluDeleteQuadric(quadric);
    
    glPopMatrix();
}