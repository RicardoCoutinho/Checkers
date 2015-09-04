#ifndef __CGFLib_1__Graph__
#define __CGFLib_1__Graph__

#include <iostream>
#include <iomanip>
#include <map>
#include <stack>
#include <string>

#include "Node.h"

using namespace std;

class Graph{
private:
    map<int,Node*> nodeMap;
    
    int rootid;
    Node* root;
    
public:
    Graph();
	Graph(int);
	
    int getRootid();
    Node* getRoot();
        
    void setRootid(int);
    void setRoot(Node*);
    
    Node* getNode(int);
    Node* getNode(string);
    
    bool addNode(Node*);
    
    void init();
    void run(Node* next);
	void draw();
	void update(unsigned long millis);
};

#endif /* defined(__CGFLib_1__Ref__) */