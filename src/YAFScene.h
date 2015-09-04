#pragma once
#ifndef _YAFSCENE_H_
#define _YAFSCENE_H_

#include <iostream>
#include "tinyxml.h"

#include "Globals.h"
#include "Cameras.h"
#include "Lighting.h"
#include "Textures.h"
#include "Appearances.h"
#include "Animations.h"
#include "Graph.h"
#include "Waterline.h"
#include "Board.h"

#include "Menu.h"

#include "Application.h"
#include "Interface.h"

#ifdef __APPLE__
#include "CGFaxis.h"
#else
#include "CGF\CGFaxis.h"
#endif

using namespace std;

class YAFScene
{
    
friend class Application;
friend class Interface;
public:
	YAFScene(char *filename);
	~YAFScene();
    
    Menu* menu;
    
    Board* board;
    
    Globals* globals;
    Cameras* cameras;
    Lighting* lighting;
    Textures* textures;
   	Appearances* appearances;
	Animations* animations;
    Graph* graph;
    
    CGFaxis axis;
	CGFshader* waterline;
    
    //Camera* activeCamera;
    int camID;
    
    Interface* interface;
    
    unsigned long updatePeriod;
    unsigned long lastUpdate;
    
    // Parser of elements
    Globals* parseGlobals(string background, string drawmode, string shading, string cullface, string cullorder);
    Cameras* parseCameras(string initial);
    Camera* parseOrtho(int ID, string ids, string pos, string znear, string zfar, string left, string right, string top, string bottom);
    Camera* parsePerspective(int ID, string ids, string pos, string znear, string zfar, string angle, string target);
    Lighting* parseLighting(string doublesided, string local, string enabled, string ambient);
    Light* parseOmni(string ids, string enabled, string location, string ambient, string diffuse, string specular);
    Light* parseSpot(string ids, string enabled, string location, string ambient, string diffuse, string specular, string angle, string exponent, string direction);
    Textures* parseTextures();
    Texture* parseTexture(string ids, string file);
    Appearances* parseAppearances();
    Appearance* parseAppearance(string ids, string emissive, string ambient, string diffuse, string specular, string shininess);
    Appearance* parseAppearanceAndTexture(string ids, string emissive, string ambient, string diffuse, string specular, string shininess, string textureref, string texlength_s, string texlength_t);
	Animations* parseAnimations();
    Animation* parseAnimation(string ids, string span, string type, vector <vector<GLfloat> >  controlpoints);
	LinearAnimation* parseLinearAnimation(string ids, string span, string type, vector <vector<GLfloat> >  controlpoints);
    Graph* parseGraph(int rootid, string ids);
    Node* parseNode(int ID, string ids, bool displaylist);
    Transform* parseScale(string factor);
    Transform* parseTranslate(string to);
    Transform* parseRotate(string axis, string angle);
    Primitive* parseSphere(string radius, string slices, string stacks);
    Primitive* parseTorus(string inner, string outer, string slices, string loops);
    Primitive* parseTriangle(string xyz1, string xyz2, string xyz3);
    Primitive* parseRectangle(string xy1, string xy2);
    Primitive* parseCylinder(string base, string top, string height, string slices, string stacks);
	Primitive* parsePlane(string parts);
	Primitive* parsePatch(string order, string partsU, string partsV, string compute, vector <vector<GLfloat> >  controlpoints);
	Primitive* parseWaterline(string heightmap, string texturemap, string fragmentshader, string vertexshader);
            
    static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);
        
    void setUpdatePeriod(unsigned long millis);
    void checkUpdate();
    
    void setInterface(Interface* i);
    
	void animInit();
    void init();
    void display();
    void draw();
    void drawPicking();
    void text_draw();
    void timer_draw();
    void lastmove_draw();
    void gamedata_draw();
        
    string get_enum(int i, int j);

    void update();
    void update(unsigned long millis);
        
protected:
    
    int firstCameraID;
    int nextCameraID;
    
    int firstNodeID;
    int nextNodeID;

	TiXmlDocument* doc;
	TiXmlElement* globalsElement;
	TiXmlElement* camerasElement;
	TiXmlElement* lightingElement;
	TiXmlElement* texturesElement;
	TiXmlElement* appearancesElement;
	TiXmlElement* animationsElement;
    TiXmlElement* graphElement;    
};

#endif