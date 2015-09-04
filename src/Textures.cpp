//
//  Textures.cpp
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 01/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#include "Textures.h"

Textures::Textures()
{
    textureMap.clear();
}
Textures::~Textures()
{
    map<string,Texture*>::iterator it,ite;
    it = textureMap.begin();
    ite = textureMap.end();
    
    for (; it != ite; it++)
    {
        delete it->second;
    }
}


Texture* Textures::getTexture(string ids)
{
    if (textureMap.count(ids))
    {
        return textureMap[ids];
    }
    
    return NULL;
}
bool Textures::addTexture(Texture* texture)
{
    if (this->textureMap.find(texture->getIds()) == this->textureMap.end()) {
        this->textureMap.insert(pair<string,Texture*>(texture->getIds(),texture));
        return true;
    }
    
    return false;
}

void Textures::print() {
    map<string,Texture*>::iterator it,ite;
    it = textureMap.begin();
    ite = textureMap.end();
    
    cout << "--- Textures ---" << endl;
    for (; it != ite; it++)
    {
        it->second->print();
        cout << endl;
    }
}