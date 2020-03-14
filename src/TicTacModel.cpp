/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TicTacModel.cpp
 * Author: Mahyar
 * 
 * Created on March 1, 2020, 11:57 AM
 */

#include "TicTacModel.h"

TicTacModel::TicTacModel() {

    humanUsedNearEdge = false;
    lastMoveIndex = NOTSTARTED;
    for (int i = 0; i < MAXCELLCOUNT; i++)
        moveSequence[i] = NOTSTARTED;
}

TicTacModel::~TicTacModel() {
}

/**
 * 
 * @param char * boardLayoutCopy is a copy of boardStatus from Model
 * @return char * a copy of boardStatus from Model
 */
char * TicTacModel::getBoardStatusCopy(char * boardLayoutCopy) {
    for (int i = 0; i < MAXCELLCOUNT; i++) 
        boardLayoutCopy[i] = boardLayout[i];
    
    return boardLayoutCopy;
}

/**
 * Checks the player movement to be valid
 * @param cellIndex
 * @return bool result of check process
 */
bool TicTacModel::isPlayerMoveValid(int cellIndex) {
    if (isCellIndexValid(cellIndex) && isCellEmpty(cellIndex))
        return true;
    else
        return false;
}

/**
 * Checks to find a cell is empty or not
 * @param CellIndex
 * @return bool result of check process
 */
bool TicTacModel::isCellEmpty(int CellIndex) {
    if (boardLayout[CellIndex] == ' ')
        return true;
    else
        return false;
}

/**
 * Check to fine whether cell Index is in valid range
 * @param cellIndex
 * @return bool result of check process
 */
bool TicTacModel::isCellIndexValid(int cellIndex) {
    if (cellIndex < STARTCELLINDEX || cellIndex > ENDCELLINDEX)
        return false;
    else
        return true;
}

/**
 * Check to find gaming board has at least one free cell or not
 * @return bool result of check process
 */
bool TicTacModel::isFull() {
    for (int i = 0; i < MAXCELLCOUNT; i++) {
        if (boardLayout[i] == ' ')
            return false;
    }
    return true;
}

/**
 * Sets boardLayout and moveSequence based of most recent move of a playes
 * @param cellIndex int cell index of most recent move
 * @param playerID char player ID (X or O)
 */
void TicTacModel::recordMove(int cellIndex, char playerID) {
    boardLayout[cellIndex] = playerID;
    moveSequence[++lastMoveIndex] = cellIndex;
}

/**
 * Check to find whether there is a winner or not
 * @return player ID of winner(X or O) or "T" when games come to a tie
 */
char TicTacModel::checkWinner() {

    if (boardLayout[0] == boardLayout[1] && boardLayout[0] == boardLayout[2] &&
            boardLayout[0] != NODATACHAR) return boardLayout[0];
    if (boardLayout[3] == boardLayout[4] && boardLayout[3] == boardLayout[5] &&
            boardLayout[3] != NODATACHAR) return boardLayout[3];
    if (boardLayout[6] == boardLayout[7] && boardLayout[6] == boardLayout[8] &&
            boardLayout[6] != NODATACHAR) return boardLayout[6];

    if (boardLayout[0] == boardLayout[3] && boardLayout[0] == boardLayout[6] &&
            boardLayout[0] != NODATACHAR) return boardLayout[0];
    if (boardLayout[1] == boardLayout[4] && boardLayout[1] == boardLayout[7] &&
            boardLayout[1] != NODATACHAR) return boardLayout[1];
    if (boardLayout[2] == boardLayout[5] && boardLayout[2] == boardLayout[8] &&
            boardLayout[2] != NODATACHAR) return boardLayout[2];

    if (boardLayout[0] == boardLayout[4] && boardLayout[0] == boardLayout[8] &&
            boardLayout[0] != NODATACHAR) return boardLayout[0];

    if (boardLayout[2] == boardLayout[4] && boardLayout[2] == boardLayout[6] &&
            boardLayout[2] != NODATACHAR) return boardLayout[2];

    if (isFull())
        return TIE;

    return NOBODY;
}

/**
 * 
 * @param userStarter
 */
void TicTacModel::setStarter(char userStarter) {

    if (userStarter == CONFIRM) {
        nextMove = COMPUTER;
        startingPlayer = COMPUTER;

    } else {
        nextMove = HUMAN;
        startingPlayer = HUMAN;
    }
}

/**
 * Determines who should do next move
 * @return bool (for "computer" true and for "human" false)
 */
bool TicTacModel::getNextMove() {
    return nextMove;
}

/**
 * Change player turn
 */
void TicTacModel::changeNextMove() {
    if (nextMove == COMPUTER) {
        nextMove = HUMAN;
    } else {
        nextMove = COMPUTER;
    }
}

void TicTacModel::setHumanID(char playerID) {
    humanID = playerID;
}

void TicTacModel::setComputerID(char playerID) {
    computerID = playerID;
}

char TicTacModel::getHumanID() {
    return humanID;
}

char TicTacModel::getComputerID() {
    return computerID;
}

string TicTacModel::getComputerPlayerName() {
return COMPUTERPLAYERNAME;
}

string TicTacModel::getHumanPlayerName() {
    return HUMANPLAYERNAME;
}


bool TicTacModel::isCorner(int cellIndex) {
    if (cellIndex != CENTER && cellIndex % 2 == 0)
        return true;
    else
        return false;
}

/**
 * Finds an empty corner place
 * @return int index of founded cell if there is any, otherwise returns NOTVALIDINDEX
 */
int TicTacModel::findAFreeCornerIndex(void) {
    for (int i = 0; i < CORNERCOUNT; i++) {
        if(isCellEmpty(cornerList[i]))
            return cornerList[i]; 
    }
    return NOTVALIDINDEX;
}


/**
 * Finds whether the last used place is an edge and is neighbor of previous one 
 * @param cornerCellIndex
 * @param unknownIndex
 * @return 
 */
bool TicTacModel::isNearEdge(int cornerCellIndex, int recentMoveIndex) {
    for (int i = 0; i < CORNERCOUNT * 2; i++) {
        if (neighbors[i].usedCornerindex == cornerCellIndex) {
            if (recentMoveIndex == neighbors[i].nearEdgeIndex) {
                setNextCornerIndex(neighbors[i].cornerIndexForNextUse);
                return true;
            }
        }
    }
    return false;
}

/**
 * Finds a random corner cell which has not been used
 * @return int playerCellIndex which is index of a corner cell
 */
int TicTacModel::findRandomCorner() {
    int playerCellIndex;
    do {
        playerCellIndex = (rand() % 4) * 2;
        if (playerCellIndex >= CENTER)
            playerCellIndex += 2;
    } while (!isCellEmpty(playerCellIndex));

    return playerCellIndex;
}

/**
 * returns opposite corner cell index
 * @param cellIndex is index of a corner cell
 * @return opposite corner cell index
 */
int TicTacModel::findOppositeCorner(int cellIndex) {
    
    return ENDCELLINDEX - cellIndex;
}

/**
 * Main logic of computer movement
 */
void TicTacModel::doComputerMove() {

    int playerCellIndex;

    srand((unsigned) time(0));

    // Try to win
    playerCellIndex = findWinnerCellIndex(computerID);
    if (playerCellIndex != NOTVALIDINDEX) {
        recordMove(playerCellIndex, computerID);
        return;
    }

    // Prevent other party not to win
    playerCellIndex = findWinnerCellIndex(humanID);
    if (playerCellIndex != NOTVALIDINDEX) {
        recordMove(playerCellIndex, computerID);
        return;
    }

    if (startingPlayer == COMPUTER) {
        switch (lastMoveIndex) {
            case NOTSTARTED:
                // select a corner by random
                playerCellIndex = findRandomCorner();
                recordMove(playerCellIndex, computerID);
                return;

            case 1:
                // find human player first move type

                if (isCorner(moveSequence[lastMoveIndex])) {
                    playerCellIndex = findRandomCorner();
                    recordMove(playerCellIndex, computerID);
                    return;
                }

                // Check if human first move is at the center
                if (moveSequence[lastMoveIndex] == CENTER) {
                    playerCellIndex = findOppositeCorner(moveSequence[lastMoveIndex - 1]);
                    recordMove(playerCellIndex, computerID);
                    return;
                }

                if (isNearEdge(moveSequence[0], moveSequence[lastMoveIndex])) {
                    humanUsedNearEdge = true;
                    recordMove(CENTER, computerID);
                    return;
                }

                // It is far edge

                recordMove(CENTER, computerID);
                
                break;

            case 3:
                cout << " --> case 3 \n";
                int nextMoveIndex = getNextCornerIndex();
                if (nextMoveIndex != NOTVALIDINDEX){
                    recordMove(nextMoveIndex, computerID);
                }
                else{
                    int f = findAFreeCornerIndex();
                    cout << " ----> f = " << f << "\n";
                    recordMove(findAFreeCornerIndex(), computerID);
                }
                    
                break;

        }
    } else {
        // Code for the time that player started first should be placed here
    }
}

/**
 * Check if there is a n empty cell that can cause win.
 * @param playerID (X or O)
 * @return int index of winner cell (which is empty now)
 */
int TicTacModel::findWinnerCellIndex(char playerID) {

    int winnerCellIndex;

    //check Horizontal cells
    for (int i = 0; i < MAXCELLCOUNT; i += SIDECELLCOUNT) {
        winnerCellIndex = findWinnerCell(i, 1, playerID);
        if (winnerCellIndex != NOTVALIDINDEX) {
            return winnerCellIndex;
        }
    }

    //check Horizontal cells
    for (int i = 0; i < SIDECELLCOUNT; i++) {
        winnerCellIndex = findWinnerCell(i, 3, playerID);
        if (winnerCellIndex != NOTVALIDINDEX) {
            return winnerCellIndex;
        }
    }

    //check diagonal cells
    winnerCellIndex = findWinnerCell(0, 4, playerID);
    if (winnerCellIndex != NOTVALIDINDEX) {
        return winnerCellIndex;
    }
    winnerCellIndex = findWinnerCell(2, 2, playerID);
    if (winnerCellIndex != NOTVALIDINDEX) {
        return winnerCellIndex;
    }

    return NOTVALIDINDEX;
}

/**
 * Finds an empty cell which can be used to win in a three cells set
 *   (vertical or horizontal or diagonal)
 * @param start Starting cell index
 * @param increment is increment in cell index to find next cell index 
 *         (1 for row and 3 for column and ...) 
 * @param playerID
 * @return emptyCellIndex or NOTVALIDINDEX
 */
int TicTacModel::findWinnerCell(int start, int increment, char playerID) {

    int similarCellCount = 0;
    int emptyCellCount = 0;
    int emptyCellIndex = NOTVALIDINDEX;
    int index = start;

    for (int j = 0; j < SIDECELLCOUNT; j++) {
        if (boardLayout[index] == NODATACHAR) {
            emptyCellCount++;
            emptyCellIndex = index;
        } else {
            if (boardLayout[index] == playerID)
                similarCellCount++;
        }

        index += increment;
    }
    
    if (similarCellCount == 2 && emptyCellCount == 1)
        return emptyCellIndex;
    else
        return NOTVALIDINDEX;
}

void TicTacModel::setNextCornerIndex(int nextCornerIndex) {
    this->nextCornerIndex = nextCornerIndex;
}

int TicTacModel::getNextCornerIndex(void) {
    return nextCornerIndex;
}
