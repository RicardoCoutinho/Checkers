//
//  Texture.cpp
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 01/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#include "Texture.h"

#include "Application.h"
#include "imagetools.h"

Texture::Texture(string ids, string file)
{
    setIds(ids);
    setFile(file);
    setTexID(-1);
    
    loadTexture();
}
Texture::~Texture()
{
    if (texID!=-1)
		glDeleteTextures(1,&texID);
}


string Texture::getIds() {return ids;}
string Texture::getFile() {return file;}
GLint Texture::getWidth() {return width;}
GLint Texture::getHeight() {return height;}
GLuint Texture::getTexID() {return texID;}


void Texture::setIds(string ids) {this->ids = ids;}
void Texture::setFile(string file) {this->file = file;}
void Texture::setWidth(GLint width) {this->width = width;}
void Texture::setHeight(GLint height) {this->height = height;}
void Texture::setTexID(GLuint texID) {this->texID = texID;}


bool Texture::operator() (Texture* a, Texture* b) {return (a->getIds().compare(b->getIds()));}


void Texture::print()
{
    cout << "Texture :: ";
    cout << "id: " << getIds() << endl;
    cout << "file: " << getFile() << endl;
}


void Texture::loadTexture()
{    
	if (texID==-1)
		glGenTextures(1,&texID);
    
    #ifdef __APPLE__
    string str = "";
    #else
    string str = "..\\data\\";
    #endif
	
	str.append(file);

	unsigned char *data = loadRGBImage(str.c_str(), &width, &height);

	if (data)
	{
		glPixelStorei(GL_UNPACK_ROW_LENGTH, width);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        
		glBindTexture(GL_TEXTURE_2D, texID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        
		free(data);
	}
	else
		throw GLexception("Texture::loadTexture failed");
}

void Texture::apply()
{
	if (texID!=-1)
		glBindTexture(GL_TEXTURE_2D, texID);
}


