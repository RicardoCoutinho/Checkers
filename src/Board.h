//
//  Board.h
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 28/11/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#ifndef __CGFLib_1__Board__
#define __CGFLib_1__Board__

#define OFFSET_X 8.6
#define OFFSET_Z 8.625

#include <stdio.h>
#include <time.h>

#include <iostream>
#include <vector>

#include "Piece.h"
#include "LinearAnimation.h"

class Placement{
public:
    int atX,atY;
    
    Placement(int atX, int atY)
    {
        this->atX = atX;
        this->atY = atY;
    }
    
    void print()
    {
        cout << "at:(" << atX << "," << atY << ")" << endl;
    }
};

class Move{
public:
    int fromX,fromY;
    int toX,toY;
    
    Move(int fromX, int fromY, int toX, int toY)
    {
        this->fromX = fromX;
        this->fromY = fromY;
        this->toX = toX;
        this->toY = toY;
    }
    
    void print()
    {
        cout << "from:(" << fromX << "," << fromY << ")" << " , to:(" << toX << "," << toY << ")" << endl;
    }
};

class Copy{
public:
    Piece* board[9][9];
    
    int gamePhase;
    int playerTurn;
    int placementsLeft[2];
    int inGame[2];
    
    int gameover;
    
    void init();
};

class Board{
public:
    Piece* board[9][9];
    
    int gamePhase;
    int playerTurn;
    int placementsLeft[2];
    int inGame[2];
    
    bool menu;
    
    Piece* aniPiece;
    LinearAnimation* ani;
    
    vector<Placement> possiblePlacements;
    vector<Move> possibleMoves;
    vector<Move> possibleCaptures;
    
    vector<Move> plays; // os placements ficam como (10,10,toX,toY) , se for o ultimo mete (10+stack,10,toX,toY)
    
    Appearance* app;
    
    GLfloat glow;
    GLfloat glow_inc;
    
    int gameover;
    int lastPicked;
    double start_time;
    double actual_time;
    
    bool start;
    double playTime0;
    double playTime;
    
    int actual_play;
    
    Copy* state;
    bool undo_available;
    
    bool replay;
    vector<Move>::iterator itplay;
    
    void init();
    
    void clear_picked();
    void clear_possible();
    void setPossible(int x, int y);
    void setPlaceable();
    
    int adversary();
    
    bool place(int atX, int atY, int stackPlayer);
    bool move(int fromX, int fromY, int toX, int toY);
    bool capture(int fromX, int fromY, int toX, int toY);
    void liberate(int aX, int aY);
    
    bool is_valid_XY(int x, int y);
    bool is_empty_XY(int x, int y);
    bool is_player_XY(int x, int y);
    bool is_adversary_XY(int x, int y);
    
    bool is_valid_place(int x, int y);
    bool is_valid_move(int fromX, int fromY, int toX, int toY);
    bool is_valid_capture(int fromX, int fromY, int toX, int toY);
    
    void storePossible();
    bool hasPossibleCaptures(int x, int y);
    
    void storeTime();
    
    void print();
    void print_possibleCaptures();
    void print_possibleMoves();
    
    bool isGameover();
    string getPlayerTurn();
    int end();

    void play(int selected);
    
    void draw();
    
    Copy* copy();
    void undo();
    
    void reset();
    void replayGame();
};

#endif /* defined(__CGFLib_1__Board__) */
