//
//  Animation.cpp
//  CGFLib-1
#include "Animation.h"

#include "imagetools.h"

Animation::Animation(string ids, GLfloat span, string type, GLint ncpt, GLfloat** cpt)
{
	setIds(ids);
	setSpan(span);
	setType(type);
    setNCpt(ncpt);
	setCpt(cpt);
}

Animation::~Animation()
{
    if (cpt != NULL)
    {
        for (int i=0; i<ncpt; i++)
            delete [] cpt[i];
        delete [] cpt;
    }
}

string Animation::getIds()
{
	return this->ids;
}
GLfloat  Animation::getSpan()
{
	return this->span;
}
string Animation::getType()
{
	return this->type;
}
GLint Animation::getCp()
{
    return this->cp;
}
GLfloat* Animation::getXYZ()
{
    return this->xyz;
}
GLint Animation::getNCpt()
{
    return this->ncpt;
}
GLfloat** Animation::getCpt()
{
    return this->cpt;
}
bool Animation::getLoop()
{
    return this->loop;
}
bool Animation::getReset()
{
    return this->reset;
}
GLfloat Animation::getStartTime()
{
    return this->startTime;
}
GLfloat Animation::getTime()
{
    return this->time;
}


void Animation::setIds(string ids)
{
	this->ids = ids;
}
void Animation::setSpan(GLfloat span)
{
	this->span = span;
}
void Animation::setType(string type)
{
	this->type = type;
}
void Animation::setCp(GLint cp)
{
    this->cp = cp;
}
void Animation::setXYZ(GLfloat* xyz)
{
    this->xyz[0] = xyz[0];
    this->xyz[1] = xyz[1];
    this->xyz[2] = xyz[2];
}
void Animation::setX(GLfloat x)
{
    this->xyz[0] = x;
}
void Animation::setY(GLfloat y)
{
    this->xyz[1] = y;
}
void Animation::setZ(GLfloat z)
{
    this->xyz[2] = z;
}
void Animation::setNCpt(GLint ncpt)
{
    this->ncpt = ncpt;
}
void Animation::setCpt(GLfloat** cpt)
{
    this->cpt = cpt;
}
void Animation::setLoop(bool loop)
{
    this->loop = loop;
}
void Animation::setReset(bool reset)
{
    this->reset = reset;
}
void Animation::setStartTime(GLfloat startTime)
{
    this->startTime = startTime;
}
void Animation::setTime(GLfloat time)
{
    this->time = time;
}


void Animation::nextCp()
{
    
    
    if (cp + 1 < ncpt)
    {
        cp++;
    }
    else if(reset)
    {
        cp = 0;
    }
    
}


