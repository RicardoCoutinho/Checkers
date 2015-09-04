#include "Graph.h"

Graph::Graph(int rootid)
{
	setRootid(rootid);
    setRoot(NULL);
    nodeMap.clear();
}

int Graph::getRootid() {return rootid;}
Node* Graph::getRoot() {return root;}
void Graph::setRootid(int rootid) {this->rootid = rootid;}
void Graph::setRoot(Node* root) {this->root = root;}

Node* Graph::getNode(int ID)
{
    if (nodeMap.count(ID))
    {
        return nodeMap[ID];
    }
    
    return NULL;
}

Node* Graph::getNode(string ids)
{
    map<int,Node*>::iterator it, ite;
    it = nodeMap.begin();
    ite = nodeMap.end();
    
    for (; it != ite; it++)
    {
        if ( (it->second->getIds().compare(ids) == 0) )
        {
            return it->second;
        }
    }
    
    return NULL;
}

bool Graph::addNode(Node* node)
{
    if (this->nodeMap.find(node->getID()) == this->nodeMap.end())
    {
        this->nodeMap.insert(pair<int,Node*>(node->getID(),node));
        return true;
    }
    
    return false;
}

void Graph::init()
{
	if (root != NULL) 
	{
		root->generateGeometry(false);
	} 
	else 
	{
		exit(1);
	}

    if ( root->app == NULL )
    {
        cout << "Root does not have an appearance." ;
        exit(1);
    }
}

void Graph::draw() {
	root->draw();
}

void Graph::update(unsigned long millis)
{
	root->update(millis);
}

/*void Graph::run(Node* node)
{
    if (!node)
    {
        return;
    }

    vector<Node*>::iterator it, ite;
    it = node->nodes.begin();
    ite = node->nodes.end();
    
    glPushMatrix();
    
    node->apply();
    
    for (; it != ite; it++)
    { 
        run(*it);
    }
    
    glPopMatrix();
    
}*/