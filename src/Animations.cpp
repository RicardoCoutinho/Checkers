//
//  Animations.cpp
//  CGFLib-1

#include "Animations.h"

Animations::Animations()
{
    AnimationMap.clear();
}

Animations::~Animations()
{
    map<string,Animation*>::iterator it,ite;
    it = AnimationMap.begin();
    ite = AnimationMap.end();
    
    for (; it != ite; it++)
    {
        delete it->second;
    }
}

map<string,Animation*> Animations::getAnimations()
{
	return AnimationMap;
}

Animation* Animations::getAnimation(string ids)
{
    if (AnimationMap.count(ids))
    {
        return AnimationMap[ids];
    }        
    return NULL;
}

bool Animations::addAnimation(Animation* animation)
{
    if (this->AnimationMap.find(animation->getIds()) == this->AnimationMap.end())
    {
        this->AnimationMap.insert(pair<string,Animation*>(animation->getIds(),animation));
        return true;
    }
    
    return false;
}

void Animations::print()
{
    map<string,Animation*>::iterator it,ite;
    it = AnimationMap.begin();
    ite = AnimationMap.end();
    
    cout << "--- Animations ---" << endl;
    for (; it != ite; it++)
    {
        it->second->print();
        cout << endl;
    }
}