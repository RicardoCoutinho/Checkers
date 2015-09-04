//
//  Camera.cpp
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 27/09/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#define CG_CGFcamera_AXIS_X 0
#define CG_CGFcamera_AXIS_Y 1
#define CG_CGFcamera_AXIS_Z 2

#include "Camera.h"

Camera::Camera(int ID, string ids, GLfloat* pos, GLfloat znear, GLfloat zfar) : Ref(ID,ids)
{
    setPos(pos);
    setZNear(znear);
    setZFar(zfar);
    
    rotation[0] = 0;
	rotation[1] = 0;
	rotation[2] = 0;
    
    setExamineMode();
}
Camera::~Camera() {}


GLfloat* Camera::getPos() {return pos;}
GLfloat Camera::getZNear() {return zNear;}
GLfloat Camera::getZFar() {return zFar;}
GLfloat* Camera::getRotation() {return rotation;}
CAMERA_MODE Camera::getMode() {return mode;}


void Camera::setPos(GLfloat* pos)
{
    this->pos[0] = pos[0];
    this->pos[1] = pos[1];
    this->pos[2] = pos[2];
}
void Camera::setPos(GLfloat x, GLfloat y, GLfloat z)
{
    this->pos[0] = x;
    this->pos[1] = y;
    this->pos[2] = z;
}
void Camera::setPosX(GLfloat x) {this->pos[0] = x;}
void Camera::setPosY(GLfloat y) {this->pos[1] = y;}
void Camera::setPosZ(GLfloat z) {this->pos[2] = z;}
void Camera::setZNear(GLfloat zNear) {this->zNear = zNear;}
void Camera::setZFar(GLfloat zFar) {this->zFar = zFar;}


bool Camera::operator() (Camera* a, Camera* b) {return (a->getIds().compare(b->getIds()));}


void Camera::print()
{
    cout << "- Camera - Base" << endl;
    cout << "| ID: " << getID() << endl;
    cout << "| ids: " << getIds() << endl;
    cout << "| near: " << getZNear() << endl;
    cout << "| far: " << getZFar() << endl;
}


void Camera::setExamineMode()
{
	mode=EXAMINE_MODE;
}

void Camera::setWalkMode()
{
	mode=WALK_MODE;
}


bool Camera::rotateTo(GLint axis, GLfloat angle, GLfloat increment)
{
	if (axis!=CG_CGFcamera_AXIS_X && axis!=CG_CGFcamera_AXIS_Y && axis!=CG_CGFcamera_AXIS_Z) return false;
    
	if(rotation[axis] < angle)
	{
		rotation[axis] += increment;
		return false;
	}
	return true;
}

bool Camera::setRotation(GLint axis, GLfloat angle)
{
	if (axis!=CG_CGFcamera_AXIS_X && axis!=CG_CGFcamera_AXIS_Y && axis!=CG_CGFcamera_AXIS_Z) return false;
	rotation[axis] = angle;
	return true;
}

bool Camera::rotate(GLint axis, GLfloat angle)
{
	if (axis!=CG_CGFcamera_AXIS_X && axis!=CG_CGFcamera_AXIS_Y && axis!=CG_CGFcamera_AXIS_Z) return false;
	rotation[axis] += angle;
	return true;
}

bool Camera::moveTo(GLint axis, GLfloat value, GLfloat increment)
{
	if (axis!=CG_CGFcamera_AXIS_X && axis!=CG_CGFcamera_AXIS_Y && axis!=CG_CGFcamera_AXIS_Z) return false;
    
	if(pos[axis] < value)
	{
		pos[axis] += increment;
		return false;
	}
	return true;
}

bool Camera::translate(GLint axis, GLfloat value)
{
	if (axis!=CG_CGFcamera_AXIS_X && axis!=CG_CGFcamera_AXIS_Y && axis!=CG_CGFcamera_AXIS_Z) return false;
	pos[axis] += value;
	return true;
}

