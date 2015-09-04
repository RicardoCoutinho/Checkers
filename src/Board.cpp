//
//  Board.cpp
//  CGFLib-1
//
//  Created by José Ricardo de Sousa Coutinho on 28/11/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#include "Board.h"

void Board::init()
{
    glutSetCursor(GLUT_CURSOR_INFO);
    
    menu = true;
    
    gamePhase = 1;
    playerTurn = 1;
    placementsLeft[PLAYER1-1] = 12;
    placementsLeft[PLAYER2-1] = 12;
    inGame[PLAYER1-1] = 0;
    inGame[PLAYER2-1] = 0;
    gameover = 0;
    
    possiblePlacements.clear();
    possibleMoves.clear();
    possibleCaptures.clear();
    plays.clear();
    
    for (int i=0; i<9; i++)
    {
        for (int j=0; j<9; j++)
        {
            //if( board[i][j] != NULL )
                //delete(board[i][j]);
            
            if ( is_valid_XY(i,j) )
                board[i][j] = new Piece(FREE,0,0);
            
        }
    }
    
    GLfloat _emissive[4] = {0,0,0,1};
    GLfloat _ambient[4] = {0,0,0,1};
    GLfloat _diffuse[4] = {0,0,0,1};
    GLfloat _specular[4] = {0,0,0,1};
    GLfloat _shininess = 0;
    
    app = new Appearance("boarder", _emissive, _ambient, _diffuse, _specular, _shininess);
    
    lastPicked = -1;
    
    actual_time = 0;
    start_time = 0;
    actual_play = 0;
    
    state = new Copy();
    state->init();
    undo_available = true;
    
    replay = false;
    itplay = plays.begin();
    
    glow = 1;
    glow_inc = 0.1;
    
    storePossible();
    
    setPlaceable();
    
    aniPiece = NULL;
    ani = NULL;
    
    playTime = 0;
    playTime0 = 0;
    
    start = false;
}

void Copy::init()
{
    gamePhase = 1;
    playerTurn = 1;
    placementsLeft[PLAYER1-1] = 12;
    placementsLeft[PLAYER2-1] = 12;
    inGame[PLAYER1-1] = 0;
    inGame[PLAYER2-1] = 0;
    gameover = 0;
    
    for (int i=0; i<9; i++)
    {
        for (int j=0; j<9; j++)
        {
                board[i][j] = NULL;
        }
    }
    
}


void Board::clear_picked()
{
    for (int i=0; i<9; i++)
    {
        for (int j=0; j<9; j++)
        {
            if ( is_valid_XY(i,j) )
            {
                board[i][j]->setPicked(0);
            }
        }
    }
}

void Board::clear_possible()
{
    for (int i=0; i<9; i++)
    {
        for (int j=0; j<9; j++)
        {
            if ( is_valid_XY(i,j) )
            {
                board[i][j]->setPossible(0);
            }
        }
    }
}

int Board::adversary(){ if (playerTurn == PLAYER1) return PLAYER2; else return PLAYER1; }

bool Board::place(int atX, int atY, int stackPlayer)
{
    if ( !is_valid_place(atX,atY) )
    {
        //cout << "Error @ Board :: place -> Invalid (atX,atY)" << endl;
        return 0;
    }
    
    if (!replay)
        state = copy();
    
    board[atX][atY] = new Piece(playerTurn,0,0);
        
    if (PLAYER1 == playerTurn)
    {
        board[atX][atY]->setP2Stack(0);
        board[atX][atY]->setP1Stack(stackPlayer);
    }
    else
    {
        board[atX][atY]->setP1Stack(0);
        board[atX][atY]->setP2Stack(stackPlayer);
    }
    
    inGame[ playerTurn-1 ]++;
    placementsLeft[ playerTurn-1 ] -= 1 + stackPlayer;
    
    //board[atX][atY]->print();
    
    return 1;
}

bool Board::move(int fromX, int fromY, int toX, int toY)
{
    if (!replay)
    {
        if (!is_valid_move(fromX, fromY, toX, toY) )
        {
            //cout << "Error @ Board :: move -> Invalid (fromX,fromY,toX,toY)" << endl;
            return 0;
        }
    
        if (!replay && state->playerTurn != playerTurn)
        {
            state = copy();
        }
        
    }
    board[fromX][fromY]->print();
    
    aniPiece = board[fromX][fromY]->copy();

    if (aniPiece != NULL)
    {
        cout << "Ani made";
        aniPiece->print();
        
        aniPiece->ani = true;
        aniPiece->end = false;
        
        aniPiece->a[0] = fromX*TILE_SIZE - OFFSET_X;
        aniPiece->a[1] = 0;
        aniPiece->a[2] = fromY*TILE_SIZE - OFFSET_Z;
    
        aniPiece->b[0] = toX*TILE_SIZE - OFFSET_X;
        aniPiece->b[1] = 0;
        aniPiece->b[2] = toY*TILE_SIZE - OFFSET_Z;
    
        aniPiece->inc[0] = (fromX < toX) ? 0.05 : -0.05;
        aniPiece->inc[1] = 0;
        aniPiece->inc[2] = (fromY < toY) ? 0.05 : -0.05;
    }
    
    board[toX][toY] = board[fromX][fromY];
    board[fromX][fromY] = new Piece(FREE,0,0);
    
    //board[toX][toY]->print();
    
    return 1;
}

bool Board::capture(int fromX, int fromY, int toX, int toY)
{
    int atX,atY;
    
    if (!replay)
    {
    
        if ( !is_valid_capture(fromX, fromY, toX, toY) )
        {
            //cout << "Error @ Board :: capture -> Invalid (fromX,fromY,toX,toY)" << endl;
            return 0;
        }
        
        state = copy();
    
    }
    
    board[fromX][fromY]->print();
    
    aniPiece = board[fromX][fromY]->copy();
    
    if (aniPiece != NULL)
    {
        cout << "Ani made";
        aniPiece->print();
        
        aniPiece->ani = true;
        aniPiece->end = false;
        
        aniPiece->a[0] = fromX*TILE_SIZE - OFFSET_X;
        aniPiece->a[1] = 0;
        aniPiece->a[2] = fromY*TILE_SIZE - OFFSET_Z;
        
        aniPiece->b[0] = toX*TILE_SIZE - OFFSET_X;
        aniPiece->b[1] = 0;
        aniPiece->b[2] = toY*TILE_SIZE - OFFSET_Z;
        
        aniPiece->inc[0] = (fromX < toX) ? 0.05 : -0.05;
        aniPiece->inc[1] = 0;
        aniPiece->inc[2] = (fromY < toY) ? 0.05 : -0.05;
    }
    
    
    atX = (toX-fromX>0)? toX-1 : toX+1 ;
    atY = (toY-fromY>0)? toY-1 : toY+1 ;
    
    inGame[ adversary()-1 ]--;
    
    Piece* player = board[fromX][fromY];
    Piece* captured = board[atX][atY];
    
    player->transferStacks(captured);
    liberate(atX, atY);
    
    if ( !is_empty_XY(atX, atY) )
        inGame[ playerTurn-1 ]++;
    
    board[toX][toY] = board[fromX][fromY];
    board[fromX][fromY] = new Piece(FREE,0,0);
    
    // board[toX][toY]->print();
    
    return 1;
}

void Board::liberate(int atX, int atY)
{
    Piece* lib = board[atX][atY];
    int player = lib->getPlayer();
    
    if (player == FREE) return ;
        
    if (
           ( player == PLAYER1 && lib->getP2Stack() == 0 )
            ||
           ( player == PLAYER2 && lib->getP1Stack() == 0 )
        )
    {
        delete board[atX][atY];
        board[atX][atY] = new Piece(FREE,0,0);
    }
    else
    {
        if (player == PLAYER1)
        {
            lib->setPlayer(PLAYER2);
            lib->setP1Stack(0);
            lib->setP2Stack(0);
        }
        else
        {
            lib->setPlayer(PLAYER1);
            lib->setP1Stack(0);
            lib->setP2Stack(0);
        }
    }
}

bool Board::is_valid_XY(int x, int y)
{
    return ((x>-1 && x<9 && y>-1 && y<9) && ((x+1+y+1) % 2 == 0));
}

bool Board::is_empty_XY(int x, int y)
{
    return ( is_valid_XY(x,y) && board[x][y]->getPlayer() == 0 );
}

bool Board::is_player_XY(int x, int y)
{
    return ( is_valid_XY(x,y) && board[x][y]->getPlayer()==playerTurn );
}

bool Board::is_adversary_XY(int x, int y)
{
    return ( is_valid_XY(x,y) && !is_empty_XY(x,y) && board[x][y]->getPlayer()!=playerTurn );
}

bool Board::is_valid_place(int x, int y)
{
    return (
            is_valid_XY(x,y) && is_empty_XY(x,y) &&
            (!is_adversary_XY(x-1,y-1) || (
                                           is_adversary_XY(x-1,y-1) && (
                                                                        is_player_XY(x+1, y+1) || is_adversary_XY(x+1, y+1) || !is_valid_XY(x+1, y+1)
                                                                        )
                                           )) &&
             (!is_adversary_XY(x-1,y+1) || (
                                            is_adversary_XY(x-1,y+1) && (
                                                                         is_player_XY(x+1, y-1) || is_adversary_XY(x+1, y-1) || !is_valid_XY(x+1, y-1)
                                                                         )
                                            )) &&
              (!is_adversary_XY(x+1,y-1) || (
                                             is_adversary_XY(x+1,y-1) && (
                                                                          is_player_XY(x-1, y+1) || is_adversary_XY(x-1, y+1) || !is_valid_XY(x-1, y+1)
                                                                          )
                                             )) &&
               (!is_adversary_XY(x+1,y+1) || (
                                              is_adversary_XY(x+1,y+1) && (
                                                                           is_player_XY(x-1, y-1) || is_adversary_XY(x-1, y-1) || !is_valid_XY(x-1, y-1)
                                                                           )
                                              ))
            && possibleCaptures.empty()
            
            );
}

bool Board::is_valid_move(int fromX, int fromY, int toX, int toY)
{
    return (
            is_valid_XY(fromX,fromY) && is_player_XY(fromX,fromY) &&
            is_valid_XY(toX,toY) && is_empty_XY(toX,toY) &&
            abs(fromX-toX) == 1 && abs(fromY-toY) == 1
            
            && possibleCaptures.empty() && placementsLeft[playerTurn-1] == 0
            
            );
}

bool Board::is_valid_capture(int fromX, int fromY, int toX, int toY)
{
    int atX,atY;
    
    atX = (toX-fromX>0)? toX-1 : toX+1 ;
    atY = (toY-fromY>0)? toY-1 : toY+1 ;
    
    return (
            is_valid_XY(fromX,fromY) && is_player_XY(fromX,fromY) &&
            is_valid_XY(atX,atY) && is_adversary_XY(atX,atY) &&
            is_valid_XY(toX,toY) && is_empty_XY(toX,toY) &&
            abs(fromX-toX) == 2 && abs(fromY-toY) == 2
            );
}

void Board::storePossible()
{
    possiblePlacements.clear();
    possibleMoves.clear();
    possibleCaptures.clear();
    
    for (int x=0; x<9; x++)
    {
        for (int y=0; y<9; y++)
        {
            if ( gamePhase==1 && placementsLeft[playerTurn-1]>0 && is_valid_place(x,y) ) possiblePlacements.push_back( Placement(x,y) );
            
            if ( is_valid_move(x,y,x-1,y-1) ) possibleMoves.push_back( Move(x,y,x-1,y-1) );
            if ( is_valid_move(x,y,x-1,y+1) ) possibleMoves.push_back( Move(x,y,x-1,y+1) );
            if ( is_valid_move(x,y,x+1,y-1) ) possibleMoves.push_back( Move(x,y,x+1,y-1) );
            if ( is_valid_move(x,y,x+1,y+1) ) possibleMoves.push_back( Move(x,y,x+1,y+1) );
            
            if ( is_valid_capture(x,y,x-2,y-2) ) possibleCaptures.push_back( Move(x,y,x-2,y-2) );
            if ( is_valid_capture(x,y,x-2,y+2) ) possibleCaptures.push_back( Move(x,y,x-2,y+2) );
            if ( is_valid_capture(x,y,x+2,y-2) ) possibleCaptures.push_back( Move(x,y,x+2,y-2) );
            if ( is_valid_capture(x,y,x+2,y+2) ) possibleCaptures.push_back( Move(x,y,x+2,y+2) );
        }
    }
}

void Board::storeTime()
{
    if (gameover!=0)
    {
        return;
    }
    
    time_t timer;
    struct tm y2k;
    double seconds;
    
    y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
    y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;
    
    time(&timer);  /* get current time; same as: timer = time(NULL)  */
    
    seconds = difftime(timer,mktime(&y2k));
    
    //printf ("%.f seconds since January 1, 2000 in the current timezone", seconds);
    
    if (start_time == 0)
    {
        start_time = seconds;
        actual_time = start_time;
    }
    else
    {
        actual_time = seconds - start_time;
        
        playTime = actual_time - playTime0;
    }
}

void Board::setPossible(int x, int y)
{
    
    vector<Move>::iterator it,ite;
    
    bool hascaptures = false;
    
    it=possibleCaptures.begin();
    ite=possibleCaptures.end();
    
    for (; it!=ite; it++)
    {
        if (it->fromX == x && it->fromY == y)
        {
            hascaptures = true;
            board[it->toX][it->toY]->possible = 1;
        }
    }
    
    if (hascaptures){
        return;
    }
    
    
    it=possibleMoves.begin();
    ite=possibleMoves.end();
    
    for (; it!=ite; it++)
    {
        if (it->fromX == x && it->fromY == y)
        {
            board[it->toX][it->toY]->possible = 1;
        }
    }
    
}

void Board::setPlaceable()
{
    if (possibleCaptures.size() > 0)
    {
        vector<Move>::iterator it,ite;
        
        it=possibleCaptures.begin();
        ite=possibleCaptures.end();
        
        for (; it!=ite; it++)
        {
            board[it->fromX][it->fromY]->possible = 1;
        }
    }
    else if (possiblePlacements.size() > 0)
    {
        vector<Placement>::iterator itp,itpe;
        
        itp=possiblePlacements.begin();
        itpe=possiblePlacements.end();
        
        for (; itp!=itpe; itp++)
        {
            board[itp->atX][itp->atY]->possible = 1;
        }
    }
    else if (possibleMoves.size() > 0)
    {
        vector<Move>::iterator it,ite;
        
        it=possibleMoves.begin();
        ite=possibleMoves.end();
        
        for (; it!=ite; it++)
        {
            board[it->fromX][it->fromY]->possible = 1;
        }
    }
    
}

string Board::getPlayerTurn()
{
    if (playerTurn == PLAYER1) return "1";
    else return "2";
}

void Board::print()
{
    //cout << "   A B C D E F G H I " << endl;
    cout << "   0 1 2 3 4 5 6 7 8 " << endl;
    
    for (int i=0; i<9; i++)
    {
        //cout << " " << i+1;
        cout << " " << i;
        
        for (int j=0; j<9; j++)
        {
            cout << " ";

            if (board[j][i] != NULL)
                cout << board[j][i]->getPlayer();
            else
                cout << " ";
        }
        cout << endl;
    }
}

void Board::print_possibleCaptures()
{
    vector<Move>::iterator it,ite;
    
    it = possibleCaptures.begin();
    ite = possibleCaptures.end();
    
    cout << "Possible Captures" << endl;
    
    for (; it!=ite; it++)
        it->print();
}

void Board::print_possibleMoves()
{
    vector<Move>::iterator it,ite;
    
    it = possibleMoves.begin();
    ite = possibleMoves.end();
    
    cout << "Possible Moves" << endl;
    
    for (; it!=ite; it++)
        it->print();
}

bool Board::isGameover()
{
    return (gameover==0);
}

int Board::end()
{
    if (placementsLeft[playerTurn-1]>0 && placementsLeft[adversary()-1]>0) return 0;
    if (inGame[PLAYER1-1] == 0) return PLAYER2;
    if (inGame[PLAYER2-1] == 0) return PLAYER1;
    
    return ( possiblePlacements.empty() && possibleMoves.empty() && possibleCaptures.empty() ) ?  (-1) : (0) ;
}

bool Board::hasPossibleCaptures(int x, int y)
{
    vector<Move>::iterator it,ite;
    it = possibleCaptures.begin();
    ite = possibleCaptures.end();
    
    for (; it!=ite; it++)
    {
        if (it->fromX == x && it->fromY == y)
        {
            return true;
        }
    }
    
    return false;
}

void Board::play(int selected)
{
    if (!start)
    {
        start_time = 0;
        start = true;
    }
    
    int fromX,fromY,toX,toY;
    fromX=fromY=toX=toY=-1;
    
    bool iscapture,isplace,ismove;
    iscapture=isplace=ismove=false;
    
    clear_picked();
    clear_possible();
    
    if (lastPicked == -1)
    {
        fromX = selected / 9;
        fromY = selected % 9;
        
        if (is_valid_place(fromX, fromY))
        {
            isplace = true;
            lastPicked = -1;
        }
        else if (is_player_XY(fromX, fromY) && board[fromX][fromY]->player == playerTurn)
        {
            board[fromX][fromY]->setPicked(1);
            storePossible();
            setPossible(fromX, fromY);
            lastPicked = selected;
        }
        
    }
    else
    {
        fromX = lastPicked / 9;
        fromY = lastPicked % 9;
        
        toX = selected / 9;
        toY = selected % 9;
        
        if ( is_valid_capture(fromX, fromY, toX, toY) )
        {
            iscapture = true;
        }
        else if ( is_valid_move(fromX, fromY, toX, toY) )
        {
            ismove = true;
        }
        
        lastPicked = -1;
    }
    
    // fills vectors with possible moves
    storePossible();
    
    // player
    if ( iscapture && !possibleCaptures.empty() )
    {
        capture(fromX,fromY,toX,toY);
        plays.push_back( Move(fromX,fromY,toX,toY) );
        
        storePossible();
        
        if ( possibleCaptures.empty() || !hasPossibleCaptures(toX, toY) )
        {
            playerTurn = adversary();
        }
        
        undo_available = true;
        playTime0 = actual_time;
    }
    else
    {
        if ( isplace && !possiblePlacements.empty() )
        {
            if ( placementsLeft[ adversary()-1 ] == 0)
            {
                place(fromX,fromY, placementsLeft[ playerTurn-1 ]-1 );
                plays.push_back( Move(10+placementsLeft[ playerTurn-1 ],10+playerTurn,fromX,fromY) );
                gamePhase = 2;
            }
            else
            {
                place(fromX,fromY,0);
                plays.push_back( Move(10+1,10+playerTurn,fromX,fromY) );
            }
            
            undo_available = true;
            playerTurn = adversary();
            playTime0 = actual_time;
        }
        else if ( ismove && !possibleMoves.empty() )
        {
            
            move(fromX,fromY,toX,toY);
            plays.push_back( Move(fromX,fromY,toX,toY) );
            
            undo_available = true;
            playerTurn = adversary();
            playTime0 = actual_time;
        }
    }
    
    storePossible();
    
    setPlaceable();
    
    gameover = end();
}

void Board::draw()
{
    app->apply();
    glColor4f(0, 0, 0,1);
    
    glow += glow_inc;
    if (glow > 0.60)
    {
        glow = 0.60;
        glow_inc = -0.010;
    }
    else if (glow < 0.1)
    {
        glow = 0.1;
        glow_inc = 0.01;
    }
    
    if (aniPiece != NULL && aniPiece->ani && !(aniPiece->end))
    {        
        glPushMatrix();
        aniPiece->draw();
        glPopMatrix();
    }
    
    for (int i=0; i<9; i++)
    {
        for (int j=0; j<9; j++)
        {
            if ( is_valid_XY(i,j) )
            {
                glPushMatrix();
                
                glTranslatef(i*TILE_SIZE - OFFSET_X, 0, j*TILE_SIZE - OFFSET_Z);
                glLoadName(i*9+j);
                
                glColor4f(0,0,0,1);
                
                if (board[i][j]->picked == 1)
                {
                    glColor4f(1,1,0,1);
                }
                else if (board[i][j]->possible == 1)
                {
                    glColor4f(0,0.6,0,glow);
                }
                else
                {
                    glColor4f(0,0,0,0);
                }
                
                glPushMatrix();
                glDisable(GL_LIGHTING);
                glTranslatef(0, 0.01, 0);
                glBegin(GL_QUADS);
                glVertex3f(0, 0, 0);
                glVertex3f(0, 0, TILE_SIZE);
                glVertex3f(TILE_SIZE, 0, TILE_SIZE);
                glVertex3f(TILE_SIZE, 0, 0);
                glEnd();
                glEnable(GL_LIGHTING);
                glPopMatrix();
                
                board[i][j]->draw();

                glPopMatrix();
            }
        }
    }
    
}


Copy* Board::copy()
{
    Copy* copy = new Copy();
   
    for (int i=0; i<9; i++)
    {
        for (int j=0; j<9; j++)
        {
            if (board[i][j] != NULL)
                copy->board[i][j] = board[i][j]->copy();
        }
    }
    
    copy->gamePhase = gamePhase;
    copy->playerTurn = playerTurn;
    copy->placementsLeft[0] = placementsLeft[0]; copy->placementsLeft[1] = placementsLeft[1];
    copy->inGame[0] = inGame[0]; copy->inGame[1] = inGame[1];
    copy->gameover = gameover;

    return copy;
}

void Board::undo()
{
    if (!undo_available)
    {
        return;
    }
    else
    {
        undo_available = false;
    }
    
    for (int i=0; i<9; i++)
    {
        for (int j=0; j<9; j++)
        {
            board[i][j] = state->board[i][j];
        }
    }
    
    gamePhase = state->gamePhase;
    playerTurn = state->playerTurn;
    placementsLeft[0] = state->placementsLeft[0]; placementsLeft[1] = state->placementsLeft[1];
    inGame[0] = state->inGame[0]; inGame[1] = state->inGame[1];
    gameover = state->gameover;
    lastPicked = -1;
    
    plays.pop_back();
    
    storePossible();
    
    setPlaceable();
    
    playTime0 = actual_time;
}

void Board::reset()
{
    gamePhase = 1;
    playerTurn = PLAYER1;
    placementsLeft[PLAYER1-1] = 12;
    placementsLeft[PLAYER2-1] = 12;
    inGame[PLAYER1-1] = 0;
    inGame[PLAYER2-1] = 0;
    gameover = 0;
    
    for (int i=0; i<9; i++)
    {
        for (int j=0; j<9; j++)
        {
            
            if ( is_valid_XY(i,j) )
                board[i][j] = new Piece(FREE,0,0);
            
        }
    }

    lastPicked = -1;
    
    actual_time = 0;
    start_time = 0;
}

void Board::replayGame()
{
    if (replay)
    {
        
        int divi = ((int) (actual_time)) - actual_play;
        
        if (itplay!=plays.end() && divi > 1)
        {
            //cout << "Time: " << divi << " , " << actual_time << " , " << actual_play << endl;
            
            actual_play++;
            
            if (itplay->fromY > 10)
            {
                int stack = itplay->fromX - 10;
                int player = itplay->fromY-10;
                
                //cout << "Player " << player << endl;
                
                if (stack==0) stack = 1;
                
                playerTurn = player;
                place(itplay->toX,itplay->toY,stack-1);
            }
            else if (abs(itplay->fromX - itplay->toX) == 1)
            {
                move(itplay->fromX, itplay->fromY, itplay->toX, itplay->toY);
            }
            else
            {
                capture(itplay->fromX, itplay->fromY, itplay->toX, itplay->toY);
            }
            
            itplay++;
            
        }
    }
    
}