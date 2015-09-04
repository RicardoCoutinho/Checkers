#ifndef _XMLSCENE_H_
#define _XMLSCENE_H_

#include "tinyxml.h"

#ifdef __APPLE__
#include "CGFscene.h"
#else
#include "CGF/CGFscene.h"
#endif

class XMLScene : public CGFscene
{
public:
	XMLScene(char *filename);
	~XMLScene();

	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);
	
protected:

	TiXmlDocument* doc;
	TiXmlElement* initElement; 
	TiXmlElement* matsElement;
	TiXmlElement* textsElement;
	TiXmlElement* leavesElement;
	TiXmlElement* nodesElement;
	TiXmlElement* graphElement;
};

#endif