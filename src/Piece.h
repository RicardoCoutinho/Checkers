//
//  Piece.h
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 28/11/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#ifndef __CGFLib_1__Piece__
#define __CGFLib_1__Piece__

#define FREE 0
#define PLAYER1 1
#define PLAYER2 2

#include <iostream>
#include "PieceModel.h"
#include "TileModel.h"
#include "Texture.h"

using namespace std;

class Piece{
    
    static PieceModel* piece_model;

public:
    
    static Texture* white;
    static Texture* black;
    
    GLint angle;
    GLfloat pos;
    GLint dir;
    
    bool end;
    bool ani;
    GLfloat a[3];
    GLfloat b[3];
    GLfloat inc[3];
    
    int player;
    int p1stack;
    int p2stack;
    
    int picked;
    int possible;
    
    Piece(int player, int p1stack, int p2stack);
    
    int getPlayer();
    int getP1Stack();
    int getP2Stack();
    
    void setPlayer(int player);
    void setP1Stack(int p1stack);
    void setP2Stack(int p2stack);
    void setPicked(GLint value);
    void setPossible(GLint value);
    
    void incP1Stack(int inc);
    void incP2Stack(int inc);
    
    void transferStacks(Piece* captured);
            
    void print();
    void draw();
    
    Piece* copy();
};

#endif /* defined(__CGFLib_1__Piece__) */
