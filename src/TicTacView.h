/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TicTacView.h
 * Author: Mahyar
 *
 * Created on March 1, 2020, 12:40 PM
 */

#ifndef TICTACVIEW_H
#define TICTACVIEW_H

#include <iostream>
using namespace std;

#define ROWCOUNT 3
#define COLUMNCOUNT 3

class TicTacView {
public:
    TicTacView();
    virtual ~TicTacView();
    
    void renderGameScreen(char * boardStatus, bool drawHint = true);
    void prepareStartingBodyQuestion();
    void preparePlayerMoveQuestion();
    
    void announceWinner(char winnerID, string winnerName);
    void announceNoWinner();

    int getUserNextMove();
    
    
private:
    void showBoardMap(char * boardStatus);
    void drawBoardLine(char * boardStatus, int lastRowNum);
    void drawBoardCellRow(char * dataArray, int lastRowNum);
    void showGameBoard(char * boardStatus);
    void drawGameBoardHint(char * boardStatus);
    void drawBoard(char * boardDataArray); 
        
};

#endif /* TICTACVIEW_H */

