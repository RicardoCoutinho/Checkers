#include "YAFScene.h"

#include "Scale.h"
#include "Translate.h"
#include "Rotate.h"

#include "Sphere.h"
#include "Torus.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Cylinder.h"
#include "Plane.h"
#include "Patch.h"
#include "Waterline.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <unistd.h>
#else
#include <GL/glut.h>
#endif
#include <GL/glui.h>

#include <stdlib.h>
#include <sstream>

#define NUM_OBJS 24
#define NUM_ROWS 5
#define NUM_COLS 4

YAFScene::YAFScene(char *filename)
{
    
    interface = NULL;
	lastUpdate = Application::getTime();
	setUpdatePeriod(0);
    
    board = new Board();
    // game initializations
    board->init();
    
    menu = new Menu();
        
    globals = NULL;
    cameras = NULL;
    lighting = NULL;
    textures = NULL;
    appearances = NULL;
	animations = NULL;
    graph = NULL;
    
    firstCameraID = 30;
    nextCameraID = firstCameraID;
    
    firstNodeID = 60;
    nextNodeID = firstNodeID;

	// Leitura e Load do ficheiro *.yaf
	doc=new TiXmlDocument( filename );
	bool loadOkay = doc->LoadFile();

	if ( !loadOkay )
    {
		cout << "Could not load file " << filename << " , Error='" << doc->ErrorDesc() << "'. Exiting." << endl;
		exit( 1 );
	}

	TiXmlElement* yafElement= doc->FirstChildElement( "yaf" );

	if (yafElement == NULL)
    {
		cout << "Could not find <yaf> block element. Exiting." << endl;
		exit(1);
	}
    
    // Elementos principais 
	globalsElement = yafElement->FirstChildElement( "globals" );
	camerasElement = yafElement->FirstChildElement( "cameras" );
	lightingElement =  yafElement->FirstChildElement( "lighting" );
	texturesElement =  yafElement->FirstChildElement( "textures" );
	appearancesElement =  yafElement->FirstChildElement( "appearances" );
	animationsElement = yafElement->FirstChildElement("animations");
	graphElement =  yafElement->FirstChildElement( "graph" );
	
    // Elemento <globals>
	if (globalsElement == NULL)
    {
		cout << "Could not find <globals> block element. Exiting." << endl;
        exit(1);
    }
	else
    {
		cout << "Processing <globals>. ";
        globals = parseGlobals(
                               globalsElement->Attribute("background"),
                               globalsElement->Attribute("drawmode"),
                               globalsElement->Attribute("shading"),
                               globalsElement->Attribute("cullface"),
                               globalsElement->Attribute("cullorder")
                              );
        
        cout << globalsElement->Attribute("drawmode") << endl;
        
        if (!globals)
        {
            cout << "Incorrect <globals> block element. Exiting." << endl;
            exit(1);
        }
        
        cout << "Finished <globals>. " << endl;        
        globals->print();        
    }
    
    // Elemento <cameras>
	if (camerasElement == NULL)
    {
		cout << "Could not find <cameras> block element. Exiting." << endl;
        exit(1);
    }
	else
    {
		cout << "Processing <cameras>. ";
        
        cameras = parseCameras(camerasElement->Attribute("initial"));
        
        if (!cameras)
        {
            cout << "Incorrect <cameras> block element. Exiting." << endl;
            exit(1);
        }
        
        TiXmlElement* ce = camerasElement->FirstChildElement();
        
        if (ce == NULL)
        {
            cout << "Could not find at least one <perspective> or <ortho> child element. Exiting." << endl;
            exit(1);
        }
        else {            
            Camera * cam;            
            while (ce)
            {            
                if ( strcmp("perspective", ce->Value()) == 0 )
                {
                    cam = parsePerspective(
                                    nextCameraID,
                                    ce->Attribute("id"),
                                    ce->Attribute("pos"),
                                    ce->Attribute("near"),
                                    ce->Attribute("far"),
                                    ce->Attribute("angle"),
                                    ce->Attribute("target")
                                   );
                    
                    if (!cam)
                    {
                        cout << "Incorrect <camera> child. Exiting." << endl;
                        exit(1);
                    }
                    
                    nextCameraID++;
                    cameras->addCamera(cam);
                }
                else if ( strcmp("ortho", ce->Value()) == 0 )
                {
                    cam = parseOrtho(
                                     nextCameraID,
                                     ce->Attribute("id"),
                                     "0 0 0",
                                     ce->Attribute("near"),
                                     ce->Attribute("far"),
                                     ce->Attribute("left"),
                                     ce->Attribute("right"),
                                     ce->Attribute("top"),
                                     ce->Attribute("bottom")
                                    );                    
                    if (!cam)
                    {
                        cout << "Incorrect <camera> child. Exiting." << endl;
                        exit(1);
                    }
                    
                    nextCameraID++;
                    cameras->addCamera(cam);
                }
                else
                {
                    cout << "Child element is not: <perspective> or <ortho>. Exiting." << endl;
                    exit(1);
                }                                
                ce = ce->NextSiblingElement();
            }            
            cout << "Finished <cameras>. " << endl;
            cameras->print();            
        }
    }
    
    // Elemento <lighting>
	if (lightingElement == NULL)
    {
		cout << "Could not find <lighting> block element. Exiting." << endl;
        exit(1);
    }
	else
    {
		cout << "Processing <lighting>. ";
        
        lighting = parseLighting(
                                lightingElement->Attribute("doublesided"),
                                lightingElement->Attribute("local"),
                                lightingElement->Attribute("enabled"),
                                lightingElement->Attribute("ambient")
                               );
        
        if (!lighting)
        {
            cout << "Incorrect <lighting> block element. Exiting." << endl;
            exit(1);
        }
        
        TiXmlElement* le = lightingElement->FirstChildElement();
        
        if (le == NULL)
        {
            cout << "Could not find at least one <omni> or <spot> child element. Exiting." << endl;
            exit(1);
        }
        else {            
            Light* light;
            
            while (le)
            {
                if ( strcmp("omni", le->Value()) == 0 )
                {
                    light = parseOmni(
                                      le->Attribute("id"),
                                      le->Attribute("enabled"),
                                      le->Attribute("location"),
                                      le->Attribute("ambient"),
                                      le->Attribute("diffuse"),
                                      le->Attribute("specular")
                                      );                    
                    if (!light)
                    {
                        cout << "Incorrect <light> child. Exiting." << endl;
                        exit(1);
                    }                    
                    lighting->addLight(light);
                }
                else if ( strcmp("spot", le->Value()) == 0 )
                {                    
                    light = parseSpot(
                                      le->Attribute("id"),
                                      le->Attribute("enabled"),
                                      le->Attribute("location"),
                                      le->Attribute("ambient"),
                                      le->Attribute("diffuse"),
                                      le->Attribute("specular"),
                                      le->Attribute("angle"),
                                      le->Attribute("exponent"),
                                      le->Attribute("direction")
                                     );                    
                    if (!light)
                    {
                        cout << "Incorrect <light> child. Exiting." << endl;
                        exit(1);
                    }                    
                    lighting->addLight(light);
                }
                else
                {
                    cout << "Child element is not: <omni> or <spot>. Exiting." << endl;
                    exit(1);
                }                
                le = le->NextSiblingElement();
            }            
            cout << "Finished <lighting>. " << endl;
            lighting->print();            
        }        
    }    
    
    // Elemento <textures>
	if (texturesElement == NULL)
    {
		cout << "Could not find <textures> block element. Exiting." << endl;
        exit(1);
    }
	else
    {
		cout << "Processing <textures>. ";        
        textures = parseTextures();
        
        if (!textures)
        {
            cout << "Incorrect <textures> block element. Exiting." << endl;
            exit(1);
        }
        
        TiXmlElement* te = texturesElement->FirstChildElement();
        
        if (te == NULL)
        {
            cout << "No <texture> found. Finished <textures>." << endl << endl;
        }
        else {            
            Texture* tex;            
            while (te)
            {
                if ( strcmp("texture", te->Value()) == 0 )
                {
                    tex = parseTexture(
                                       te->Attribute("id"),
                                       te->Attribute("file")
                                      );                    
                    if (!tex)
                    {
                        cout << "Incorrect <texture> child. Exiting." << endl;
                        exit(1);
                    }                    
                    textures->addTexture(tex);                    
                }
                else
                {
                    cout << "Child element is not: <texture>. Exiting." << endl;
                    exit(1);
                }                
                te = te->NextSiblingElement();
            }            
            cout << "Finished <textures>. " << endl;
            textures->print();            
        }        
    }
    
    // Elemento <appearances>
	if (appearancesElement == NULL)
    {
		cout << "Could not find <appearances> block element. Exiting." << endl;
        exit(1);
    }
	else
    {
		cout << "Processing <appearances>. ";
        
        appearances = parseAppearances();
        
        if (!appearances)
        {
            cout << "Incorrect <appearances> block element. Exiting." << endl;
            exit(1);
        }
        
        TiXmlElement* ae = appearancesElement->FirstChildElement();
        
        if (ae == NULL)
        {
            cout << "No <appearance> found. Exiting.";
            exit(1);
        }
        else {            
            Appearance* app;            
            while (ae)
            {
                if ( strcmp("appearance", ae->Value()) == 0 )
                {                    
                    if (strcmp( ae->LastAttribute()->Name() , "texlength_t") == 0)
                    {                       
                        app = parseAppearanceAndTexture(
                                                        ae->Attribute("id"),
                                                        ae->Attribute("emissive"),
                                                        ae->Attribute("ambient"),
                                                        ae->Attribute("diffuse"),
                                                        ae->Attribute("specular"),
                                                        ae->Attribute("shininess"),
                                                        ae->Attribute("textureref"),
                                                        ae->Attribute("texlength_s"),
                                                        ae->Attribute("texlength_t")
                                                       );                                                                        
                        if (!app)
                        {
                            cout << "Incorrect <appearance> child. Exiting." << endl;
                            exit(1);
                        }
                        
                        app->setTexture( textures->getTexture( ae->Attribute("textureref") ) );                        
                        appearances->addAppearance(app);
                    }
                    else
                    {
                        app = parseAppearance(
                                              ae->Attribute("id"),
                                              ae->Attribute("emissive"),
                                              ae->Attribute("ambient"),
                                              ae->Attribute("diffuse"),
                                              ae->Attribute("specular"),
                                              ae->Attribute("shininess")
                                              );                        
                        if (!app)
                        {
                            cout << "Incorrect <appearance> child. Exiting." << endl;
                            exit(1);
                        }                        
                        appearances->addAppearance(app);
                    }
                }
                else
                {
                    cout << "Child element is not: <appearance>. Exiting." << endl;
                    exit(1);
                }                
                ae = ae->NextSiblingElement();
            }            
            cout << "Finished <appearances>. " << endl;
            appearances->print();            
        }        
    }

	// Elemento <animations>
	if (animationsElement == NULL)
    {
		cout << "Could not find <animations> block element. Exiting." << endl;
        exit(1);
    }
	else
    {
		cout << "Processing <animations>. ";        
        animations = parseAnimations();

        if (!animations)
        {
            cout << "Incorrect <animations> block element. Exiting." << endl;
            exit(1);
        }
        TiXmlElement* an = animationsElement->FirstChildElement();
        
        if (an == NULL)
        {
            cout << "No <animation> found. Finished <animations>." << endl << endl;
        }
        else {				
            Animation* anim = NULL; 
			LinearAnimation* la = NULL;

            while (an)
            {
                if ( strcmp("animation", an->Value()) == 0 )
                {
					string id = an->Attribute("id");
					string span = an->Attribute("span");
					string type = an->Attribute("type");
					vector <vector<GLfloat> > cp;
					TiXmlElement* anp = an->FirstChildElement();		
					while (anp)
					{
						if(strcmp("controlpoint", anp->Value()) == 0)
						{								
							string xx = anp->Attribute("xx");
							string yy = anp->Attribute("yy");
							string zz = anp->Attribute("zz");
							GLfloat _xx = atof(xx.c_str());;
							GLfloat _yy = atof(yy.c_str());
							GLfloat _zz = atof(zz.c_str());					

							vector <GLfloat> temp;							
							temp.push_back(_xx);
							temp.push_back(_yy);
							temp.push_back(_zz);
							cp.push_back(temp);
							if (!anp)
							{
								cout << "Incorrect <controlpoint> child. Exiting." << endl;
								exit(1);
							}     
						}
						else
						{
							cout << "Child element is not: <controlpoint>. Exiting." << endl;
							exit(1);
						} 
						anp = anp->NextSiblingElement(); 
					}
					if (type == "linear")
					{
						la = parseLinearAnimation(id,span, type,cp);
						animations->addAnimation(la);						
					}
					else 
					{
						anim = parseAnimation(id, span, type, cp);
						animations->addAnimation(anim);
					}				

                    if (!anim && !la)
                    {
                        cout << "Incorrect <animation> child. Exiting." << endl;
                        exit(1);
                    }                                        
                }
                else
                {
                    cout << "Child element is not: <animations>. Exiting." << endl;
                    exit(1);
                }                
                an = an->NextSiblingElement();
            }            
            cout << "Finished <animations>. " << endl;
            animations->print();            
        }        
    }
    
    // Elemento <graph>
	if (graphElement == NULL)
    {
		cout << "Could not find <graph> block element. Exiting." << endl;
        exit(1);
    }
	else
    {
		cout << "Processing <graph>. " << endl;
        graph = parseGraph(
                           firstNodeID,
                           graphElement->Attribute("rootid")
                           );
        if (!graph)
        {
            cout << "Incorrect <graph> block element. Exiting." << endl;
            exit(1);
        }
        
        nextNodeID++;
        
        TiXmlElement* ne = graphElement->FirstChildElement(); // <node> element
        TiXmlElement* nc; // <node> child element :: <transforms>, <appearanceref> , <children>        
        TiXmlElement* tc; // <transforms> child
        TiXmlElement* chc; // <children> child
        
        if (ne == NULL)
        {
            cout << "No <node> found. Exiting.";
            exit(1);
        }
        else {
            
            Node* node;
            Node* noderef;
            Appearance* appref;
			Animation* animref;
            Transform* transf;
            Primitive* prim;
            
            while (ne)
            {
                cout << "<node> . ";                
                if ( strcmp("node", ne->Value()) == 0 )
                {
                    //cout << "id: "<< ne->Attribute("id") << endl; // Show name
                    
                    node = graph->getNode( ne->Attribute("id") );					
                    
                    if (!node)
                    {
                        node = parseNode( nextNodeID, ne->Attribute("id"), ne->Attribute("displaylist") );
                        
                        if (!node)
                        {
                            cout << "Incorrect <node> block element. Exiting." << endl;
                            exit(1);
                        }                        
                        nextNodeID++;
                        graph->addNode(node);
                    }                    
                    
                    nc = ne->FirstChildElement();
                    
                    // Elemento <transforms>
                    if (nc == NULL || strcmp("transforms",nc->Value()) != 0 )
                    {
                        cout << "Could not find <transforms> block element. Exiting." << endl;
                        exit(1);
                    }
                    else
                    {
                        cout << "<transforms> . ";                        
                        tc = nc->FirstChildElement();                        
                        if (tc == NULL)
                        {
                            // cout << "empty . ";
                        }
                        else {                            
                            while (tc)
                            {
                                if ( strcmp("translate", tc->Value()) == 0 )
                                {
                                    transf = parseTranslate(
                                                            tc->Attribute("to")
                                                           );                                    
                                    if (!transf)
                                    {
                                        cout << "Incorrect <transform> child element. Exiting." << endl;
                                        exit(1);
                                    }                                    
                                    node->addTransformation(transf);
                                }
                                else if ( strcmp("rotate", tc->Value()) == 0 )
                                {
                                    transf = parseRotate(
                                                         tc->Attribute("axis"),
                                                         tc->Attribute("angle")
                                                         );                                    
                                    if (!transf)
                                    {
                                        cout << "Incorrect <transform> child element. Exiting." << endl;
                                        exit(1);
                                    }                                    
                                    node->addTransformation(transf);                                    
                                }
                                else if ( strcmp("scale", tc->Value()) == 0 )
                                {
                                    transf = parseScale(
                                                         tc->Attribute("factor")
                                                       );                                    
                                    if (!transf)
                                    {
                                        cout << "Incorrect <transform> child element. Exiting." << endl;
                                        exit(1);
                                    }                                    
                                    node->addTransformation(transf);                                    
                                }
                                else
                                {
                                    cout << "Child element is not: <translate> , <rotate> or <scale>. Exiting." << endl;
                                    exit(1);
                                }
                                
                                tc = tc->NextSiblingElement();
                            }
                                                        
                        }
                        
                    }
                    
                    nc = nc->NextSiblingElement();
                    
                    // Elemento <appearanceref>
                    if (nc == NULL || strcmp("appearanceref",nc->Value()) != 0 )
                    {
                        //cout << "empty . ";
                    }
                    else
                    {                        
                        cout << "<appearanceref> . ";
                        
                        appref = appearances->getAppearance( nc->Attribute("id") );
                                                
                        if (!appref)
                        {
                            cout << "Could not find <appearanceref> in <appearances>. Exiting." << endl;
                            exit(1);
                        }
                                                
                        node->app = appref;
                                               
                        nc = nc->NextSiblingElement();
                    }
                    
					// Elemento <animationref>
                    if (nc == NULL || strcmp("animationref",nc->Value()) != 0 )
                    {
                        //cout << "empty . ";
                    }
                    else
                    {                        
                        cout << "<animationref> . ";
                        
						animref = animations->getAnimation( nc->Attribute("id") );						
                                                
                        if (!animref)
                        {
                            cout << "Could not find <animationref> in <appearances>. Exiting." << endl;
                            exit(1);
                        }    						
                        node->anim = animref;                                               
                        nc = nc->NextSiblingElement();
                    }

                    // Elemento <children>
                    if (nc == NULL || strcmp("children",nc->Value()) != 0 )
                    {
                        cout << "Could not find <children> block element. Exiting." << endl;
                        exit(1);
                    }
                    else
                    {
                        cout << "<children> . ";
                        
                        chc = nc->FirstChildElement();
                        
                        if (chc == NULL)
                        {
                            cout << "No <rectangle> , <triangle> , <cylinder> , <sphere> , <torus>, <noderef> or <plane> found. Exiting.";
                            exit(1);
                        }
                        else {                            
                            while (chc)
                            {
                                if ( strcmp("rectangle", chc->Value()) == 0 )
                                {
                                    cout << "<rectangle> . ";
                                    
                                    prim = parseRectangle(
                                                          chc->Attribute("xy1"),
                                                          chc->Attribute("xy2")
                                                         );                                    
                                    if (!prim)
                                    {
                                        cout << "Incorrect primitive <rectangle> element. Exiting." << endl;
                                        exit(1);
                                    }
                                    
                                    node->addPrimitive(prim);                                    
                                }
                                else if ( strcmp("triangle", chc->Value()) == 0 )
                                {
                                    cout << "<triangle> . ";
                                    
                                    if (!prim)
                                    {
                                        cout << "Can only have one primitive element. Exiting." << endl;
                                        exit(1);
                                    }                                    
                                    prim = parseTriangle(
                                                         chc->Attribute("xyz1"),
                                                         chc->Attribute("xyz2"),
                                                         chc->Attribute("xyz3")
                                                        );                                    
                                    if (!prim)
                                    {
                                        cout << "Incorrect primitive <triangle> element. Exiting." << endl;
                                        exit(1);
                                    }
                                    
                                    node->addPrimitive(prim);                                    
                                }
                                else if ( strcmp("cylinder", chc->Value()) == 0 )
                                {
                                    cout << "<cylinder> . ";
                                    
                                    if (!prim)
                                    {
                                        cout << "Can only have one primitive element. Exiting." << endl;
                                        exit(1);
                                    }
                                    
                                    prim = parseCylinder(
                                                         chc->Attribute("base"),
                                                         chc->Attribute("top"),
                                                         chc->Attribute("height"),
                                                         chc->Attribute("slices"),
                                                         chc->Attribute("stacks")
                                                        );                                    
                                    if (!prim)
                                    {
                                        cout << "Incorrect primitive <cylinder> element. Exiting." << endl;
                                        exit(1);
                                    }
                                    
                                    node->addPrimitive(prim);                                    
                                }
                                else if ( strcmp("sphere", chc->Value()) == 0 )
                                {
                                    cout << "<sphere> . ";
                                    
                                    if (!prim)
                                    {
                                        cout << "Can only have one primitive element. Exiting." << endl;
                                        exit(1);
                                    }
                                    
                                    prim = parseSphere(
                                                       chc->Attribute("radius"),
                                                       chc->Attribute("slices"),
                                                       chc->Attribute("stacks")
                                                      );                                    
                                    if (!prim)
                                    {
                                        cout << "Incorrect primitive <sphere> element. Exiting." << endl;
                                        exit(1);
                                    }
                                    
                                    node->addPrimitive(prim);                                    
                                }
                                else if ( strcmp("torus", chc->Value()) == 0 )
                                {
                                    cout << "<torus> . ";
                                    
                                    if (!prim)
                                    {
                                        cout << "Can only have one primitive element. Exiting." << endl;
                                        exit(1);
                                    }
                                    
                                    prim = parseTorus(
                                                      chc->Attribute("inner"),
                                                      chc->Attribute("outer"),
                                                      chc->Attribute("slices"),
                                                      chc->Attribute("loops")
                                                     );                                    
                                    if (!prim)
                                    {
                                        cout << "Incorrect primitive <torus> element. Exiting." << endl;
                                        exit(1);
                                    }                                    
                                    node->addPrimitive(prim);                                    
                                }
                                else if ( strcmp("noderef", chc->Value()) == 0 )
                                {
                                    cout << "<noderef> . ";
                                    
                                    noderef = graph->getNode( chc->Attribute("id") );
                                    
                                    if (!noderef)
                                    {
                                        noderef = parseNode( nextNodeID , chc->Attribute("id"), chc->Attribute("displaylist") );
                                        
                                        if (!noderef)
                                        {
                                            cout << "Could not find create new <node> from <noderef> element. Exiting." << endl;
                                            exit(1);
                                        }
                                        
                                        nextNodeID++;
                                        graph->addNode(noderef);                                        
                                    }                                    
                                    node->addLinkTo(noderef);                                            
                                }
								// EXAME:ParserPlane
								else if ( strcmp("plane", chc->Value()) == 0 )
                                {
                                    cout << "<plane> . ";
                                    
                                    if (!prim)
                                    {
                                        cout << "Can only have one primitive element. Exiting." << endl;
                                        exit(1);
                                    }                                    
                                    prim = parsePlane( chc->Attribute("parts") );                                    
                                    if (!prim)
                                    {
                                        cout << "Incorrect primitive <plane> element. Exiting." << endl;
                                        exit(1);
                                    }                                    
                                    node->addPrimitive(prim);								
                                }		
								// EXAME:ParserPatch
								else if ( strcmp("patch", chc->Value()) == 0 )
                                {
									vector <vector<GLfloat> > cpt;
                                    cout << "<patch> . ";
                                    
                                    if (!prim)
                                    {
                                        cout << "Can only have one primitive element. Exiting." << endl;
                                        exit(1);
                                    } 									
									string order = chc->Attribute("order");
									string partsU = chc->Attribute("partsU");
									string partsV = chc->Attribute("partsV");
									string compute = chc->Attribute("compute");                                  
									TiXmlElement* cp = chc->FirstChildElement();									
									while (cp)
									{
										if (strcmp("controlpoint", cp->Value()) == 0)
										{
											string xx = cp->Attribute("x");
											string yy = cp->Attribute("y");
											string zz = cp->Attribute("z");
											GLfloat _xx = atof(xx.c_str());;
											GLfloat _yy = atof(yy.c_str());
											GLfloat _zz = atof(zz.c_str());					
											
											vector <GLfloat> temp;							
											temp.push_back(_xx);
											temp.push_back(_yy);
											temp.push_back(_zz);
											cpt.push_back(temp);											
											if (!cp)
											{
												cout << "Incorrect <controlpoint> child. Exiting." << endl;
												exit(1);
											}
										}
										else
										{
											cout << "Child element is not: <controlpoint>. Exiting." << endl;
											exit(1);
										} 
										cp = cp->NextSiblingElement();
									}
                                    if (!prim)
                                    {
                                        cout << "Incorrect primitive <patch> element. Exiting." << endl;
                                        exit(1);
                                    }  
									prim = parsePatch( order, partsU, partsV, compute, cpt);  										
                                    node->addPrimitive(prim);                                    									
                                }
								// EXAME:ParserWaterline
								else if ( strcmp("waterline", chc->Value()) == 0 )
                                {
                                    cout << "<waterline> . ";
                                    
                                    if (!prim)
                                    {
                                        cout << "Can only have one primitive element. Exiting." << endl;
                                        exit(1);
                                    }                                    
                                    prim = parseWaterline( chc->Attribute("heightmap"),
														   chc->Attribute("texturemap"),
														   chc->Attribute("fragmentshader"),
														   chc->Attribute("vertexshader") );     
                                    if (!prim)
                                    {
                                        cout << "Incorrect primitive <waterline> element. Exiting." << endl;
                                        exit(1);
                                    }                                    
                                    node->addPrimitive(prim);								
                                }
                                else
                                {
                                    cout << "Child element is not: <rectangle> , <triangle> , <cylinder> , <sphere> , <torus> , <noderef> or <plane> or <patch>. Exiting." << endl;
                                    exit(1);
                                }                                                                
                                chc = chc->NextSiblingElement();																
                            }                                   							
                        }                        
                        cout << endl;       						
                    }                    
                }
                else
                {
                    cout << "Child element is not: <node>. Exiting." << endl;
                    exit(1);
                }                
                ne = ne->NextSiblingElement();
            }
            
            // set root node and checks for appearanceref
            if (!graph->getRoot())
            {
                graph->setRoot( graph->getNode(graph->getRootid()) );
                
                /*
                if (graph->getRoot()->app == NULL)
                {
                    cout << "Found no appearance in root node. Exiting." << endl;
                    exit(1);
                }
                 */
            }            
            cout << "Finished <graph>. " << endl << endl;
        }        
    }
    
}

// ------------

Globals* YAFScene::parseGlobals(string background, string drawmode, string shading, string cullface, string cullorder)
{    
    GLfloat _background[4];
    GLenum _drawmode;
    GLenum _shading;
    GLenum _cullface;
    GLenum _cullorder;
    
    // parse background
    sscanf(background.c_str(), "%f %f %f %f", &_background[0], &_background[1], &_background[2], &_background[3]);
    
    // parse drawmode
    if (drawmode == "point") {
        _drawmode = GL_POINT;
    }
    else if (drawmode == "line") {
        _drawmode = GL_LINE;
    }
    else if (drawmode == "fill") {
        _drawmode = GL_FILL;
    }
    else {
        return NULL;
    }
    
    // parse shading
    if (shading == "flat") {
        _shading = GL_FLAT;
    }
    else if (shading == "gouraud") {
        _shading = GL_SMOOTH;
    }
    else {
        return NULL;
    }
    
    // parse cullface
    if (cullface == "none") {
        _cullface = 0;
    }
    else if (cullface == "back") {
        _cullface = GL_BACK;
    }
    else if (cullface == "front") {
        _cullface = GL_FRONT;
    }
    else if (cullface == "both") {
        _cullface = GL_FRONT_AND_BACK;
    }
    else {
        return NULL;
    }
    
    // parse cullorder
    if (cullorder == "CW") {
        _cullorder = GL_CW;
    }
    else if (cullorder == "CCW") {
        _cullorder = GL_CCW;
    }
    else {
        return NULL;
    }
    
    Globals* g = new Globals( _background, _drawmode, _shading, _cullface, _cullorder );    
    return g;
}

Cameras* YAFScene::parseCameras(string initial)
{
    Cameras* c = new Cameras(initial);
    return c;
}

Camera* YAFScene::parseOrtho(int ID, string ids, string pos, string znear, string zfar, string left, string right, string top, string bottom)
{
    GLfloat _pos[3];
    GLfloat _znear;
    GLfloat _zfar;
    GLfloat _left;
    GLfloat _right;
    GLfloat _top;
    GLfloat _bottom;
    
    sscanf(pos.c_str(), "%f %f %f", &_pos[0], &_pos[1], &_pos[2]);

    _znear = atof(znear.c_str());    
    _zfar = atof(zfar.c_str());    
    _left = atof(left.c_str());    
    _right = atof(right.c_str());    
    _top = atof(top.c_str());    
    _bottom = atof(bottom.c_str());
    
    Camera* c = new Ortho(ID, ids, _pos, _znear, _zfar, _left, _right, _top, _bottom );    
    return c;
}

Camera* YAFScene::parsePerspective(int ID, string ids, string pos, string znear, string zfar, string angle, string target)
{
    GLfloat _pos[3];
    GLfloat _znear;
    GLfloat _zfar;
    GLfloat _angle;
    GLfloat _target[3];
    
    sscanf(pos.c_str(), "%f %f %f", &_pos[0], &_pos[1], &_pos[2]);
    
    _znear = atof(znear.c_str());    
    _zfar = atof(zfar.c_str());    
    _angle = atof(angle.c_str());
    
    sscanf(target.c_str(), "%f %f %f", &_target[0], &_target[1], &_target[2]);
        
    Camera* c = new Perspective( ID , ids, _pos, _znear, _zfar, _angle, _target );    
    return c;
}

Lighting* YAFScene::parseLighting(string doublesided, string local, string enabled, string ambient)
{
    bool _doublesided;
    bool _local;
    bool _enabled;
    GLfloat _ambient[4];
    
    if (doublesided == "true") {
        _doublesided = true;
    }
    else if (doublesided == "false") {
        _doublesided = false;
    }
    else {
        return NULL;
    }
    
    if (local == "true") {
        _local = true;
    }
    else if (local == "false") {
        _local = false;
    }
    else {
        return NULL;
    }
    
    if (enabled == "true") {
        _enabled = true;
    }
    else if (enabled == "false") {
        _enabled = false;
    }
    else {
        return NULL;
    }
    
    sscanf(ambient.c_str(), "%f %f %f %f", &_ambient[0], &_ambient[1], &_ambient[2], &_ambient[3]);
    
	Lighting* l = new Lighting( _doublesided, _local, _enabled, _ambient );    
    return l;    
}

Light* YAFScene::parseOmni(string ids, string enabled, string location, string ambient, string diffuse, string specular)
{
    bool _enabled;
    GLfloat _location[4];
    GLfloat _ambient[4];
    GLfloat _diffuse[4];
    GLfloat _specular[4];
    
    if (enabled == "true") {
        _enabled = true;
    }
    else if (enabled == "false") {
        _enabled = false;
    }
    else {
        return NULL;
    }
    
    sscanf(location.c_str(), "%f %f %f", &_location[0], &_location[1], &_location[2]);
    _location[3] = 1;
    
    sscanf(ambient.c_str(), "%f %f %f %f", &_ambient[0], &_ambient[1], &_ambient[2], &_ambient[3]);    
    sscanf(diffuse.c_str(), "%f %f %f %f", &_diffuse[0], &_diffuse[1], &_diffuse[2], &_diffuse[3]);        
    sscanf(specular.c_str(), "%f %f %f %f", &_specular[0], &_specular[1], &_specular[2], &_specular[3]);
    
    Light* l = new Omni( ids, _enabled, _location, _ambient, _diffuse, _specular );
    
    return l;    
}

Light* YAFScene::parseSpot(string ids, string enabled, string location, string ambient, string diffuse, string specular, string angle, string exponent, string direction)
{
    bool _enabled;
    GLfloat _location[4];
    GLfloat _ambient[4];
    GLfloat _diffuse[4];
    GLfloat _specular[4];
    GLfloat _angle;
    GLfloat _exponent;
    GLfloat _direction[3];
    
    // parse enabled
    if (enabled == "true") {
        _enabled = true;
    }
    else if (enabled == "false") {
        _enabled = false;
    }
    else {
        return NULL;
    }
    
    sscanf(location.c_str(), "%f %f %f", &_location[0], &_location[1], &_location[2]);
    _location[3] = 1;
    
    sscanf(ambient.c_str(), "%f %f %f %f", &_ambient[0], &_ambient[1], &_ambient[2], &_ambient[3]);    
    sscanf(diffuse.c_str(), "%f %f %f %f", &_diffuse[0], &_diffuse[1], &_diffuse[2], &_diffuse[3]);    
    sscanf(specular.c_str(), "%f %f %f %f", &_specular[0], &_specular[1], &_specular[2], &_specular[3]);
    
    _angle = atof(angle.c_str());    
    _exponent = atof(exponent.c_str());
    
    sscanf(direction.c_str(), "%f %f %f", &_direction[0], &_direction[1], &_direction[2]);
    
    Light* l = new Spot( ids, _enabled, _location, _ambient, _diffuse, _specular, _angle, _exponent, _direction );    
    return l;
}

Textures* YAFScene::parseTextures()
{
    Textures* t = new Textures();
    return t;
}

Texture* YAFScene::parseTexture(string ids, string file)
{
    Texture* t = new Texture(ids,file);
    return t;
}

Appearances* YAFScene::parseAppearances()
{
    Appearances* a = new Appearances();
    return a;
}

Appearance* YAFScene::parseAppearance(string ids, string emissive, string ambient, string diffuse, string specular, string shininess)
{
    GLfloat _emissive[4];
    GLfloat _ambient[4];
    GLfloat _diffuse[4];
    GLfloat _specular[4];
    GLfloat _shininess;
    
    sscanf(emissive.c_str(), "%f %f %f %f", &_emissive[0], &_emissive[1], &_emissive[2], &_emissive[3]);    
    sscanf(ambient.c_str(), "%f %f %f %f", &_ambient[0], &_ambient[1], &_ambient[2], &_ambient[3]);    
    sscanf(diffuse.c_str(), "%f %f %f %f", &_diffuse[0], &_diffuse[1], &_diffuse[2], &_diffuse[3]);    
    sscanf(specular.c_str(), "%f %f %f %f", &_specular[0], &_specular[1], &_specular[2], &_specular[3]);
    
    _shininess = atof(shininess.c_str());
    
    Appearance* a = new Appearance( ids, _emissive, _ambient, _diffuse, _specular, _shininess);    
    return a;
}

Appearance* YAFScene::parseAppearanceAndTexture(string ids, string emissive, string ambient, string diffuse, string specular, string shininess, string textureref, string texlength_s, string texlength_t)
{
    GLfloat _emissive[4];
    GLfloat _ambient[4];
    GLfloat _diffuse[4];
    GLfloat _specular[4];
    GLfloat _shininess;
    GLenum _texlength_s;
    GLenum _texlength_t;
    
    sscanf(emissive.c_str(), "%f %f %f %f", &_emissive[0], &_emissive[1], &_emissive[2], &_emissive[3]);    
    sscanf(ambient.c_str(), "%f %f %f %f", &_ambient[0], &_ambient[1], &_ambient[2], &_ambient[3]);    
    sscanf(diffuse.c_str(), "%f %f %f %f", &_diffuse[0], &_diffuse[1], &_diffuse[2], &_diffuse[3]);    
    sscanf(specular.c_str(), "%f %f %f %f", &_specular[0], &_specular[1], &_specular[2], &_specular[3]);
    
    _shininess = atof(shininess.c_str());    
    _texlength_s = atoi(texlength_s.c_str());
    
    if ( _texlength_s != 0 && _texlength_s != 1 )
    {
        return NULL;
    }
    
    _texlength_t = atoi(texlength_t.c_str());
    
    if ( _texlength_t != 0 && _texlength_t != 1 )
    {
        return NULL;
    }
    
    Appearance* a = new Appearance( ids, _emissive, _ambient, _diffuse, _specular, _shininess, textureref, _texlength_s, _texlength_t );    
    return a;
}

// EXAME:ParserAnimation e LinearAnimation
Animations* YAFScene::parseAnimations()
{
    Animations* a = new Animations();
    return a;
}

Animation* YAFScene::parseAnimation(string ids, string span, string type, vector <vector<GLfloat> > controlpoints)
{
	GLfloat _span;
    
	_span = atof(span.c_str());
    
    GLint ncpt = controlpoints.size();
    GLfloat** cpt = (GLfloat**) malloc(ncpt * sizeof(GLfloat*));

    if (cpt == NULL)
    {
        cout << "Error :: YAFScene :: parseAnimation :: failed to allocate array of array";
        exit(0);
    }
    
    vector< vector<GLfloat> > :: iterator it,ite;
    it = controlpoints.begin();
    ite = controlpoints.end();
    
    for (int i=0; it != ite; it++, i++)
    {
        cpt[i] = (GLfloat*) malloc(3 * sizeof(GLfloat));
        
        if (cpt[i] == NULL)
        {
            cout << "Error :: YAFScene :: parseAnimation :: failed to allocate array";
            exit(0);
        }
        
        cpt[i][0] = it->at(0);
        cpt[i][1] = it->at(1);
        cpt[i][2] = it->at(2);
    }
    

    Animation* a = new Animation(ids,_span,type,ncpt,cpt);
    return a;
}

LinearAnimation* YAFScene::parseLinearAnimation(string ids, string span, string type, vector <vector<GLfloat> > controlpoints)
{
	GLfloat _span;

	_span = atof(span.c_str());
    
    GLint ncpt = controlpoints.size();
    GLfloat** cpt = (GLfloat**) malloc(ncpt * sizeof(GLfloat*));
    
    if (cpt == NULL)
    {
        cout << "Error :: YAFScene :: parseAnimation :: failed to allocate array of array";
        exit(0);
    }
    
    vector< vector<GLfloat> > :: iterator it,ite;
    it = controlpoints.begin();
    ite = controlpoints.end();
    
    for (int i=0; it != ite; it++, i++)
    {
        cpt[i] = (GLfloat*) malloc(3 * sizeof(GLfloat));
        
        if (cpt[i] == NULL)
        {
            cout << "Error :: YAFScene :: parseAnimation :: failed to allocate array";
            exit(0);
        }
        
        cpt[i][0] = it->at(0);
        cpt[i][1] = it->at(1);
        cpt[i][2] = it->at(2);
    }
    

    LinearAnimation* a = new LinearAnimation(ids,_span,type,ncpt,cpt);
    return a;
}						

Graph* YAFScene::parseGraph(int rootid, string ids)
{
    Graph* g = new Graph(rootid);
    Node* n = new Node(rootid,ids);
    
    g->addNode(n);
    
    return g;
}

// EXAME:Parserdisplaylist
Node* YAFScene::parseNode(int ID, string ids, bool displaylist)
{
    Node* n = new Node(ID,ids, displaylist);
    return n;
}

Transform* YAFScene::parseScale(string factor)
{
    GLfloat _factor[3];
    
    sscanf(factor.c_str(), "%f %f %f", &_factor[0], &_factor[1], &_factor[2]);
    
    Transform* t = new Scale(_factor);    
    return t;
}

Transform* YAFScene::parseTranslate(string to)
{
    GLfloat _to[3];
    
    sscanf(to.c_str(), "%f %f %f", &_to[0], &_to[1], &_to[2]);
    
    Transform* t = new Translate(_to);
    return t;
}

Transform* YAFScene::parseRotate(string axis, string angle)
{
    GLint _axis[3] = {0,0,0};
    GLfloat _angle;
    
    if (axis.compare("x") == 0)
    {
        _axis[0] = 1;
    }
    else if (axis.compare("y") == 0)
    {
        _axis[1] = 1;
    }
    else if (axis.compare("z") == 0)
    {
        _axis[2] = 1;
    }
    else
    {
        return NULL;
    }
    
    _angle = atof(angle.c_str());
    
    Transform* t = new Rotate(_axis, _angle);    
    return t;
}

Primitive* YAFScene::parseSphere(string radius, string slices, string stacks)
{
    GLfloat _radius;
    GLint _slices;
    GLint _stacks;
    
    _radius = atof(radius.c_str());    
    _slices = atof(slices.c_str());    
    _stacks = atof(stacks.c_str());
    
    Primitive* p = new Sphere(_radius, _slices, _stacks);    
    return p;
}

Primitive* YAFScene::parseTorus(string inner, string outer, string slices, string loops)
{
    GLfloat _inner;
    GLfloat _outer;
    GLint _slices;
    GLint _loops;
    
    _inner = atof(inner.c_str());    
    _outer = atof(outer.c_str());    
    _slices = atof(slices.c_str());    
    _loops = atof(loops.c_str());
    
    Primitive* p = new Torus(_inner, _outer, _slices, _loops);
    return p;
}

Primitive* YAFScene::parseTriangle(string xyz1, string xyz2, string xyz3)
{
    GLfloat _xyz1[3];
    GLfloat _xyz2[3];
    GLfloat _xyz3[3];
    
    sscanf(xyz1.c_str(), "%f %f %f", &_xyz1[0], &_xyz1[1], &_xyz1[2]);    
    sscanf(xyz2.c_str(), "%f %f %f", &_xyz2[0], &_xyz2[1], &_xyz2[2]);    
    sscanf(xyz3.c_str(), "%f %f %f", &_xyz3[0], &_xyz3[1], &_xyz3[2]);
    
    Primitive* p = new Triangle(_xyz1, _xyz2, _xyz3);    
    return p;
}

Primitive* YAFScene::parseRectangle(string xy1, string xy2)
{
    GLfloat _xy1[2];
    GLfloat _xy2[2];
        
    sscanf(xy1.c_str(), "%f %f", &_xy1[0], &_xy1[1]); 
    sscanf(xy2.c_str(), "%f %f", &_xy2[0], &_xy2[1]);
        
    Primitive* p = new Rectangle(_xy1, _xy2);    
    return p;
}

Primitive* YAFScene::parseCylinder(string base, string top, string height, string slices, string stacks)
{
    GLfloat _base;
    GLfloat _top;
    GLfloat _height;
    GLint _slices;
    GLint _stacks;
    
    _base = atof(base.c_str());    
    _top = atof(top.c_str());    
    _height = atof(height.c_str());    
    _slices = atoi(slices.c_str());    
    _stacks = atoi(stacks.c_str());
    
    Primitive* p = new Cylinder(_base, _top, _height, _slices, _stacks);    
    return p;
}

// EXAME:ParserPlane
Primitive* YAFScene::parsePlane(string parts)
{
	GLint _parts;
	_parts = atoi(parts.c_str());
	Primitive* p = new Plane(_parts);
	return p;
}

// EXAME:ParserPatch
Primitive* YAFScene::parsePatch(string order, string partsU, string partsV, string compute, vector <vector<GLfloat> >  controlpoints)
{
	GLint _order;
	GLint _partsU;
	GLint _partsV;

	_order = atoi(order.c_str());
	_partsU = atoi(order.c_str());
	_partsV = atoi(order.c_str());

	Primitive* p = new Patch(_order, _partsU, _partsV, compute, controlpoints);
	return p;
}

// EXAME:ParserWaterline
Primitive* YAFScene::parseWaterline(string heightmap, string texturemap, string fragmentshader, string vertexshader)
{
	Primitive* p = new Waterline(heightmap, texturemap, fragmentshader, vertexshader);
	return p;
}
YAFScene::~YAFScene()
{
	
}

//-------------------------------------------------------

TiXmlElement* YAFScene::findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val)
// Searches within descendants of a parent for a node that has an attribute _attr_ (e.g. an id) with the value _val_
// A more elaborate version of this would rely on XPath expressions
{
	TiXmlElement *child=parent->FirstChildElement();
	int found=0;

	while (child && !found)
		if (child->Attribute(attr) && strcmp(child->Attribute(attr),val)==0)
			found=1;
		else
			child=child->NextSiblingElement();

	return child;
}


void YAFScene::setUpdatePeriod(unsigned long millis)
{
	updatePeriod = millis;
}

void YAFScene::checkUpdate()
{
	if (updatePeriod>0)
	{
		unsigned long currTime=Application::getTime();
		if (currTime-lastUpdate>=updatePeriod)
		{
			update(currTime);
			lastUpdate=currTime;
			/// TODO: Handle possible drifts
		}
	}
}

void YAFScene::setInterface(Interface* i)
{
	interface=i;
}

void YAFScene::animInit()
{
	for(map<string,Animation*>::iterator it = animations->getAnimations().begin();it!=animations->getAnimations().end();++it)
	{
		(*it).second->init();
	}
}

void YAFScene::init()
{
    globals->init();
    camID = cameras->getCamera( cameras->getInitial() )->getID();
    lighting->init();
    graph->init();
    
    board->init();
    
    board->board[0][0]->white = textures->getTexture("white");
    board->board[0][0]->black = textures->getTexture("black");
    
    setUpdatePeriod(30);
}

void YAFScene::display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	draw();
    
	glutSwapBuffers();
}

// desenha o que queremos que seja visivel
void YAFScene::draw()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    
    cameras->getCamera(camID)->applyView();
    lighting->run();
    
	//axis.draw();
	graph->draw();
    
    board->draw();
    
    if (!board->menu)
    {
        if (camID<30 || camID>33) {
            camID = 30;
        }
        
        text_draw();
        timer_draw();
        lastmove_draw();
        gamedata_draw();
    }
    else
    {
        camID = 34;
        menu->draw();
    }
}

// desenha os picks invisiveis
void YAFScene::drawPicking()
{
    //glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    
    cameras->getCamera(camID)->applyView();
    
    board->draw();
    
    if (board->menu)
        menu->draw();
}

void YAFScene::text_draw()
{
    string text;
    
    if (board->replay)
    {
        text = "REPLAY MODE !";
    }
    else
    {    
        switch (board->gameover)
        {
            case -1:
                text = "It's a TIE!";
                break;
            case 0:
                text = "Turn: Player " + board->getPlayerTurn() + " - " +
                (
                 (board->possibleCaptures.size() > 0) ? "capture" : (board->possiblePlacements.size() > 0) ? "place" : "move") ;
                break;
            case 1:
                text = "Player 1 WON !";
                break;
            case 2:
                text = "Player 2 WON !";
                break;
                
            default:
                break;
        }
    }
    
    int len = text.length();
    
    glPushMatrix();
    
    switch (camID)
    {
        case 30:
            break;
            
        case 31:
            glRotatef(180, 0, 1, 0);
            
            break;
            
        case 32:
            glRotatef(90, 0, 1, 0);
            break;
            
        case 33:
            glRotatef(-90, 0, 1, 0);
            break;
            
        default:
            break;
    }
    
    glTranslatef(-9, 1, -10);
    glRotatef(-45, 1, 0, 0);
    glScalef(0.01, 0.01, 0.01);
    
    glLineWidth(1.3);
    
    for (int i=0; i<len; i++)
    {
        glColor3f(1, 1, 0);
        
        glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
    }
    
    glPopMatrix();
}

void YAFScene::timer_draw()
{
    if (!board->start)
    {
        return;
    }
    
    board->storeTime();
    
    if (board->replay)
    {
        board->replayGame();
        return;
    }
    
    double t = board->actual_time;
    
    int h = (int)t / 3600;
    int m = ((int)t % 3600) / 60;
    int s = ((int)t % 3600) % 60;
    
    int sp = 15 - ((int) board->playTime );
    
    if (sp < 0)
    {
        board->gameover = board->adversary();
        return;
    }
    
    stringstream ss;
    
    stringstream splay;
    
    splay << "Time left: " << sp << "s";
    
    ss << "Time: ";
    if (h > 0) {
        ss << h << "h ";
    }
    if (m > 0) {
        ss << m << "m ";
    }
    if (s > 0) {
        ss << s << "s ";
    }
    string text = ss.str();
    int len = text.length();
    
    string tplay = splay.str();
    int lplay = tplay.length();
    
    glPushMatrix();
    
    switch (camID)
    {
        case 30:
            break;
            
        case 31:
            glRotatef(180, 0, 1, 0);
            
            break;
            
        case 32:
            glRotatef(90, 0, 1, 0);
            break;
            
        case 33:
            glRotatef(-90, 0, 1, 0);
            break;
            
        default:
            break;
    }
    
    
    
    glPushMatrix();
    
    glTranslatef(-3, 7, -10);
    glRotatef(-45, 1, 0, 0);
    glScalef(0.005, 0.005, 0.005);
    
    glLineWidth(1);
    
    
    for (int i=0; i<len; i++)
    {
        glColor3f(0.8, 0.8, 0.8);
        
        glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
    }
    glPopMatrix();
    
    glPushMatrix();
    
    glTranslatef(-3.2, 5, -10);
    glRotatef(-45, 1, 0, 0);
    glScalef(0.005, 0.005, 0.005);
    
    glLineWidth(1);
    
    for (int i=0; i<lplay; i++)
    {
        if (sp <= 5)
        {
            glColor3f(1, 0, 0);
        }
        else if (sp <= 10)
        {
            glColor3f(1, 1, 0);
        }
        else
        {
            glColor3f(0.8, 0.8, 0.8);
        }
        
        glutStrokeCharacter(GLUT_STROKE_ROMAN, tplay[i]);
    }
    
    glPopMatrix();
    
    glPopMatrix();
}

void YAFScene::lastmove_draw()
{
    
    if (board->replay)
    {
        return;
    }
    
    if (board->plays.size() == 0)
    {
        return;
    }
    
    glPushMatrix();
    
    switch (camID)
    {
        case 30:
            break;
            
        case 31:
            glRotatef(180, 0, 1, 0);
            
            break;
            
        case 32:
            glRotatef(90, 0, 1, 0);
            break;
            
        case 33:
            glRotatef(-90, 0, 1, 0);
            break;
            
        default:
            break;
    }
    
    stringstream ss;
    string text;
    
    int repeat = board->plays.size();
    
    vector<Move>::iterator it, ite;
    it = board->plays.end();
    ite = board->plays.begin();
    
    int len,i=0;
    
    glTranslatef(6.5, 7, -10);
    
    do {
        ss.clear();//clear any bits set
        ss.str(std::string());
        
        it--;
        
        if (it+1 == board->plays.end())
        {
            ss << "Last: ";
        }
        
        if (it->fromX > 10)
        {
            ss << "  ";
        }
        else
        {
            
            ss << get_enum(it->fromX, it->fromY) << "-";
        }
        
        ss << get_enum(it->toX, it->toY);
        
        if (it+1 == board->plays.end() && board->undo_available)
        {
            ss << " (click U key to Undo)";
        }
        
        text = ss.str();
        
        len = text.length();
        
        glPushMatrix();
        
        if (it+1 == board->plays.end())
        {
            glTranslatef(-2, -i*1.2, 0);
        }
        else
        {
            glTranslatef(0+i*0.15, -i*1.2, 0);
        }
        glRotatef(-45, 1, 0, 0);
        glScalef(0.005, 0.005, 0.005);
        
        glLineWidth(1);
        
        for (int i=0; i<len; i++)
        {
            glColor3f(0.8, 0.8, 0.8);
            
            glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
        }
        
        glPopMatrix();
        i++;
        
    } while (i<repeat && i<3);
    
    glPopMatrix();
    
}

string YAFScene::get_enum(int i, int j)
{
    string a,b;
    
    switch (i)
    {
        case 0: a = "A";
            break;
        case 1: a = "B";
            break;
        case 2: a = "C";
            break;
        case 3: a = "D";
            break;
        case 4: a = "E";
            break;
        case 5: a = "F";
            break;
        case 6: a = "G";
            break;
        case 7: a = "H";
            break;
        case 8: a = "I";
            break;
            
        default:
            break;
    }
    
    switch (j)
    {
        case 0: b = "9";
            break;
        case 1: b = "8";
            break;
        case 2: b = "7";
            break;
        case 3: b = "6";
            break;
        case 4: b = "5";
            break;
        case 5: b = "4";
            break;
        case 6: b = "3";
            break;
        case 7: b = "2";
            break;
        case 8: b = "1";
            break;
            
        default:
            break;
    }
    
    string r = a+b;
    
    return r;
}

void YAFScene::gamedata_draw()
{
    
    if (board->replay)
    {
        return;
    }
    
    glPushMatrix();
    
    switch (camID)
    {
        case 30:
            break;
            
        case 31:
            glRotatef(180, 0, 1, 0);
            
            break;
            
        case 32:
            glRotatef(90, 0, 1, 0);
            break;
            
        case 33:
            glRotatef(-90, 0, 1, 0);
            break;
            
        default:
            break;
    }
    
    stringstream p1p,p2p,p3p,p4p;
    string t1,t2,t3,t4;
    int i1,i2,i3,i4;
    
    p1p << "Player 1 :: Placements left: " << board->placementsLeft[0];
    p2p << "            Pieces in game: " << board->inGame[0];
    p3p << "Player 2 :: Placements left: " << board->placementsLeft[1];
    p4p << "            Pieces in game: " << board->inGame[1];

    t1 = p1p.str();
    t2 = p2p.str();
    t3 = p3p.str();
    t4 = p4p.str();
    
    i1 = t1.length();
    i2 = t2.length();
    i3 = t3.length();
    i4 = t4.length();
    
    glTranslatef(-16, 7, -10);
    
    glLineWidth(1);
    
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glRotatef(-45, 1, 0, 0);
    glScalef(0.005, 0.005, 0.005);
    for (int i=0; i<i1; i++)
    {
        glColor3f(0.8, 0.8, 0.8);
        glutStrokeCharacter(GLUT_STROKE_ROMAN, t1[i]);
        
    }
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-2.5, -1, 0);
    glRotatef(-45, 1, 0, 0);
    glScalef(0.005, 0.005, 0.005);
    for (int i=0; i<i2; i++)
    {
        glColor3f(0.8, 0.8, 0.8);
        glutStrokeCharacter(GLUT_STROKE_ROMAN, t2[i]);
        
    }
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-0.75, -2.5, 0);
    glRotatef(-45, 1, 0, 0);
    glScalef(0.005, 0.005, 0.005);
    for (int i=0; i<i3; i++)
    {
        glColor3f(0.8, 0.8, 0.8);
        glutStrokeCharacter(GLUT_STROKE_ROMAN, t3[i]);
        
    }
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-3.1, -3.5, 0);
    glRotatef(-45, 1, 0, 0);
    glScalef(0.005, 0.005, 0.005);
    for (int i=0; i<i4; i++)
    {
        glColor3f(0.8, 0.8, 0.8);
        glutStrokeCharacter(GLUT_STROKE_ROMAN, t4[i]);
        
    }
    glPopMatrix();
    
    glPopMatrix();
    
}

void YAFScene::update()
{}

void YAFScene::update(unsigned long millis)
{
	graph->update(millis);
}