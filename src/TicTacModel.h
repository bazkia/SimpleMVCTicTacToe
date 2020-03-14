/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TicTacModel.h
 * Author: Mahyar
 *
 * Created on March 1, 2020, 11:57 AM
 */

#ifndef TICTACMODEL_H
#define TICTACMODEL_H

#include <ctime>
#include <iostream>
using namespace std;


/*
 // Good Idea
namespace my_project {
  class Constants {
  public:
    static const double PI = 3.14159;
  }
}

// Bad Idea
#define PI 3.14159;
 * 
 * https://gist.github.com/lefticus/10191322
 
 */

#define MAXCELLCOUNT 9
#define SIDECELLCOUNT 3
#define STARTCELLINDEX 0
#define ENDCELLINDEX MAXCELLCOUNT - 1
#define NOTVALIDINDEX -1
#define CORNERCOUNT 4
#define CORNERINDEX 0


#define NODATACHAR ' '
#define NOBODY 'N'
#define TIE 'T'


#define CENTER 4

#define CONFIRM 'Y'

#define COMPUTER true
#define HUMAN false

#define COMPUTERPLAYERNAME "Computer"
#define HUMANPLAYERNAME "Humman player"



#define STARTINGPLAYER
#define NOTSTARTED -1

struct cornerEdgeNeighbor{
    int usedCornerindex;
    int nearEdgeIndex;
    int cornerIndexForNextUse;
};

class TicTacModel {
public:
    TicTacModel();

    virtual ~TicTacModel();
    char * getBoardStatusCopy(char * boardLayoutCopy);


    bool isPlayerMoveValid(int cellNumber);


    bool isFull();
    char getBoardStatus(int index);
    void recordMove(int cellIndex, char playerID);
    char checkWinner();
    void startGame();
    
    void setStarter(char userStarter);
    bool getNextMove();
    void changeNextMove();
    
    void doComputerMove();
    void setHumanID(char playerID);
    void setComputerID(char playerID);
    
    char getHumanID();
    char getComputerID();
    
    string getComputerPlayerName();
    string getHumanPlayerName();

    
    
    
private:
    char boardLayout[MAXCELLCOUNT] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    int cornerList[CORNERCOUNT] = {0, 2, 6, 8};

    cornerEdgeNeighbor neighbors[CORNERCOUNT * 2] = {
    {0, 1, 6}, 
    {0, 3, 2}, 
    {2, 1, 8}, 
    {2, 5, 0}, 
    {6, 3, 8}, 
    {6, 7, 0}, 
    {8, 5, 6}, 
    {8, 7, 2}};
    
    int moveSequence[9]; /// moveSequence is list of players movements
    int lastMoveIndex = -1;
    
    bool nextMove;
    bool startingPlayer;
    
    char humanID;
    char computerID;
    
    bool humanUsedNearEdge;
    
    int nextCornerIndex = NOTVALIDINDEX;
    
    bool isCellIndexValid(int index);
    bool isCellEmpty(int cellNumber);
        
    bool isCorner(int cellNumber);
    bool isNearEdge(int cornerCellIndex, int unknownIndex);
    
    int findRandomCorner();
    int findOppositeCorner(int cellIndex);
    
    int findWinnerCellIndex(char playerID);
//    bool findReadyToWinCell(char );
    int findWinnerCell(int start, int increment, char playerID);
    
    void setNextCornerIndex(int nextCornerIndex);
    int getNextCornerIndex(void);
    
    int findAFreeCornerIndex(void);

//    bool checkIsCorner()
    
};



#endif /* TICTACMODEL_H */

