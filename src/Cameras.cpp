//
//  Cameras.cpp
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 27/09/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#include "Cameras.h"

Cameras::Cameras(string initial)
{
    setInitial(initial);
    cameraMap.clear();
}

string Cameras::getInitial() {return initial;}

Camera* Cameras::getCamera(string ids)
{
    if (cameraMap.count(ids))
    {
        return cameraMap[ids];
    }
    
    return NULL;
}
Camera* Cameras::getCamera(int ID)
{    
    map<string,Camera*>::iterator it, ite;
    it = cameraMap.begin();
    ite = cameraMap.end();
    
    for (; it != ite; it++)
    {
        if ( (it->second->getID() == ID) )
        {
            return it->second;            
        }
    }
    
    return NULL;
}

map<string,Camera*> Cameras::getCameras() {return cameraMap;}

void Cameras::setInitial(string ids) {this->initial = ids;}

bool Cameras::addCamera(Camera* camera)
{    
    if (this->cameraMap.find(camera->getIds()) == this->cameraMap.end()) {
        this->cameraMap.insert(pair<string,Camera*>(camera->getIds(),camera));
        return true;
    }
    
    return false;
}

void Cameras::print() {
    map<string,Camera*>::iterator it,ite;
    it = cameraMap.begin();
    ite = cameraMap.end();
    
    cout << "--- Cameras ---" << endl;
    for (; it != ite; it++) {
        it->second->print();
        cout << endl;
    }
}