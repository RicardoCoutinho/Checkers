#ifndef __CGFLib_1__Waterline__
#define __CGFLib_1__Waterline__

#include <iostream>
#include <string>

#include "CGFshader.h"
#include "CGFtexture.h"
#include "Primitive.h"
#include "Plane.h"

using namespace std;

class Waterline : public Primitive, public CGFshader{
private:
    string heightmap;
	string texturemap;
	string framgentshader;
	string vertexshader;

	CGFtexture * baseTexture;
	CGFtexture * secTexture;
	int baseImageLoc;
	int secImageLoc;
	int scaleLoc;

	Primitive* pa;
    
public:
    Waterline(string heightmap, string texturemap, string fragmentshader, string vertexshader);   
	~Waterline();

	void bind();
	void setScale(float s);
	float normScale;
    void print();    
    void draw();

};

#endif /* defined(__CGFLib_1__Waterline__) */
