#include <GL/glew.h>

#ifdef __APPLE__
#else
#include <GL/gl.h>
#endif

#include "Waterline.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <unistd.h>
#else
#include <GL/glut.h>
#endif


Waterline::Waterline(string heightmap, string texturemap, string fragmentshader, string vertexshader)
{	
   this->heightmap = heightmap;
   this->texturemap = texturemap;
   this->framgentshader = fragmentshader;
   this->vertexshader = vertexshader;   

    #ifdef __APPLE__
    char vert[] = "appValues.vert";
    char frag[] = "dualVaryingColor.frag";
    char base[] = "water.jpg";
    char sec[] = "watermap.jpg";
    #else
    char vert[] = "..\\data\\appValues.vert";
    char frag[] = "..\\data\\dualVaryingColor.frag";
    char base[] = "..\\data\\water.jpg";
    char sec[] = "..\\data\\watermap.jpg";
    #endif
    
   init(vert, frag);
   //init(fragmentshader, vertexshader);
	
   CGFshader::bind();
	this->pa = new Plane(20);


   // Initialize parameter in memory	
   normScale=0.0;
	
   // Store Id for the uniform "normScale", new value will be stored on bind()
   scaleLoc = glGetUniformLocation(id(), "normScale");

   /*baseTexture = new CGFtexture(heightmap);	
   secTexture = new CGFtexture(texturemap);*/
   baseTexture = new CGFtexture(base);
   secTexture = new CGFtexture(sec);
   // get the uniform location for the sampler
	
   baseImageLoc = glGetUniformLocation(id(), "baseImage");

   // set the texture id for that sampler to match the GL_TEXTUREn that you 
   // will use later e.g. if using GL_TEXTURE0, set the uniform to 0
	
   glUniform1i(baseImageLoc, 0);	
   // repeat if you use more textures in your shader(s)

   secImageLoc = glGetUniformLocation(id(), "secondImage");
   glUniform1i(secImageLoc, 1);
}

Waterline::~Waterline()
{
	delete(baseTexture);
}


void Waterline::print()
{
    cout << "heightmap: " << heightmap << endl;
	cout << "texturemap: " << texturemap << endl;
	cout << "framgentshader: " << framgentshader << endl;
	cout << "vertexshader: " << vertexshader << endl;
}

void Waterline::draw()
{	
	this->bind();
	
	this->pa->draw();
	this->unbind();
	
}

void Waterline::bind()
{
	CGFshader::bind();

	// update uniforms
	glUniform1f(scaleLoc, normScale);

	// make sure the correct texture unit is active
	glActiveTexture(GL_TEXTURE0);

	// apply/activate the texture you want, so that it is bound to GL_TEXTURE0
	baseTexture->apply();

	// do the same for other textures
	glActiveTexture(GL_TEXTURE1);

	secTexture->apply();

	glActiveTexture(GL_TEXTURE0);

}
