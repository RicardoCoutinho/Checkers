//
//  Piece.cpp
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 28/11/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#include "Piece.h"

Texture* Piece::white = NULL;
Texture* Piece::black = NULL;

PieceModel* Piece::piece_model = new PieceModel();

Piece::Piece(int player, int p1stack, int p2stack)
{
    angle = 0;
    pos = 0;
    dir = 1;
    
    this->player = player;
    this->p1stack = p1stack;
    this->p2stack = p2stack;
    this->picked = 0;
    this->possible = 0;
    
    end=false;
    ani=false;
    
}

int Piece::getPlayer() { return player; }
int Piece::getP1Stack() { return p1stack; }
int Piece::getP2Stack() { return p2stack; }

void Piece::setPlayer(int player) { this->player = player; }
void Piece::setP1Stack(int p1stack) { this->p1stack = p1stack; }
void Piece::setP2Stack(int p2stack) { this->p2stack = p2stack; }
void Piece::setPicked(GLint value) { this->picked = value; angle=0; pos=0; dir=1;}
void Piece::setPossible(GLint value) { this->possible = value; }

void Piece::incP1Stack(int inc) { this->p1stack += inc; }
void Piece::incP2Stack(int inc) { this->p2stack += inc; }

void Piece::transferStacks(Piece* captured)
{
    if (captured->getPlayer() == PLAYER1)
    {
        incP1Stack(captured->getP1Stack() + 1);
    }
    else
    {
        incP2Stack(captured->getP2Stack() + 1);
    }
}

void Piece::print()
{
    cout << "Player: " << player << " :: ";
    cout << "Stack: " << p1stack << " , " << p2stack << endl;
}

void Piece::draw()
{
    glPushMatrix();
    
    if (picked)
    {
        glTranslatef(0, pos, 0);
        pos += 0.03 * dir;
        if (pos>2) dir = -1;
        else if (pos<0) dir = 1;
        
        
        //glRotatef(angle, 1, 1, 1);
        //angle = (angle>360) ? 1 : angle+2 ;
    }
    
    if (ani && !end)
    {
        
        //cout << a[0] << "," << a[1] << "," << a[2] << endl;
        glTranslatef(a[0], a[1], a[2]);
        
        a[0] += inc[0];
        a[1] += inc[1];
        a[2] += inc[2];
        
        if ( (inc[0]>0 && a[0]>b[0]) || (inc[0]<0 && a[0]<b[0]) )
            end = true;
    }
    
    glPushMatrix();
    
    float base;
    
    if (player == PLAYER1 || player == PLAYER2)
    {
        base = 0 + picked;
        glTranslatef(0, base, 0);
    }
    
    glColor4f(1, 1, 1, 1);
    
    if (player == PLAYER1)
    {
        // paint bot black color
        //glColor4f(0, 0, 0, 0.9);
        
        glEnable(GL_TEXTURE_2D);
        
        black->apply();
        
        for (int i=0; i<p2stack; i++)
        {
            piece_model->draw();
            glTranslatef(0, PIECE_HEIGHT+0.1, 0);
        }
        
        // paint top white color
        //glColor4f(1, 1, 1, 0.9);
        
        white->apply();
        
        for (int i=0; i<p1stack+1; i++)
        {
            piece_model->draw();
            glTranslatef(0, PIECE_HEIGHT+0.1, 0);
        }
        
        glDisable(GL_TEXTURE_2D);
        
    }
    else if (player == PLAYER2)
    {
         glEnable(GL_TEXTURE_2D);
        
         for (int i=0; i<p1stack; i++)
         {
             // paint bot white color
             //glColor4f(1, 1, 1, 0.9);
             
             white->apply();
             
             piece_model->draw();
             glTranslatef(0, PIECE_HEIGHT+0.1, 0);
             
         }
        
         for (int i=0; i<p2stack+1; i++)
         {
             // paint top black color
             //glColor4f(0, 0, 0, 0.9);
             
             black->apply();
             
             piece_model->draw();
             glTranslatef(0, PIECE_HEIGHT+0.1, 0);
         }
        
        glDisable(GL_TEXTURE_2D);
        
    }
    
    glPopMatrix();
    
    glPopMatrix();

}

Piece* Piece::copy()
{
    Piece* copy = new Piece(player,p1stack,p2stack);
    
    copy->player = player;
    copy->p1stack = p1stack;
    copy->p2stack = p2stack;
    copy->picked = 0;
    copy->possible = 0;
    
    return copy;
}