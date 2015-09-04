//
//  LinearAnimation.cpp
//  CGFLib-1
//

#include "LinearAnimation.h"

LinearAnimation::LinearAnimation(string ids, GLfloat span, string type, GLint ncpt, GLfloat** cpt)
    : Animation(ids, span, type, ncpt, cpt)
{
	setCp(0);
	setTime(0);
	angle = 0.0;
	setReset(false);
    end = false;
}

void LinearAnimation::init()
{
	//angle = atan2 (controlpointY,controlpointX) * 180 / M_PI;
	setStartTime((GLfloat) clock()/CLOCKS_PER_SEC );
	setReset(false);
}

void LinearAnimation::update()
{
	GLfloat animTime;
    
	if (getReset())
    {
		init();
	}
    else
	{		
        setTime( (GLfloat) clock()/CLOCKS_PER_SEC );
		animTime = getTime() - getStartTime();

		//angle = atan2 (controlpointY,controlpointX) * 180 / M_PI;
        setX(getCpt()[getCp() + 1][0] - getCpt()[getCp()][0]);
		setY(getCpt()[getCp() + 1][1] - getCpt()[getCp()][1]);
		setZ(getCpt()[getCp() + 1][2] - getCpt()[getCp()][2]);

		angle = atan2 (getXYZ()[1],getXYZ()[2]) * 180 / M_PI;

		setX(getCpt()[getCp()][0] + getXYZ()[0] * (animTime/ (getSpan()/ (float)(getNCpt() - 1)) ) );
		setX(getCpt()[getCp()][1] + getXYZ()[1] * (animTime/ (getSpan()/ (float)(getNCpt() - 1)) ) );
		setX(getCpt()[getCp()][2] + getXYZ()[2] * (animTime/ (getSpan()/ (float)(getNCpt() - 1)) ) );

		if (animTime >= (getSpan()/ (getNCpt() - 1)))
			if (getCp() < (getNCpt() - 2))
			{
				nextCp();
				setStartTime(getTime());
				
				/* Testes
				cout << endl << "CpCurrent: "<< cpCurrent << endl;
				cout << "Current 0: " << getCpt()[cpCurrent][0] << endl;
				cout << "Current 1: " << getCpt()[cpCurrent][1] << endl;
				cout << "Current 2: " << getCpt()[cpCurrent][2] << endl;
				cout << "CpX : " << controlpointX << endl;
				cout << "CpY : " << controlpointY << endl;
				cout << "CpZ : " << controlpointZ << endl;	
				cout << "Angle: " << angle << endl;*/
			}
	}		
}

void LinearAnimation::apply()
{	
	if (getCp() != getNCpt() - 2){
		update();
    }
    else
    {
        end = true;
    }
	
	glTranslatef(getXYZ()[0],getXYZ()[1],getXYZ()[2]);
	//glRotatef(angle,controlpointX,controlpointY,controlpointZ);
	//glRotatef(angle, (controlpointX*cos(angle) - controlpointY*sin(angle)),(controlpointX*sin(angle) - controlpointY*cos(angle)),controlpointZ );
}

void LinearAnimation::print()
{
	Animation::print();
}