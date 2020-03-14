/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TicTacController.h
 * Author: Mahyar
 *
 * Created on March 1, 2020, 7:43 PM
 */

#ifndef TICTACCONTROLLER_H
#define TICTACCONTROLLER_H

#include "TicTacModel.h"
#include "TicTacView.h"

#include <iostream>
#include <string>
#include <time.h>

using namespace std;

#define COMPUTERMOVE 1
#define HUMANMOVE 2
#define NOMOVE 3



class TicTacController {
public:
    TicTacController();
    virtual ~TicTacController();

    TicTacController(TicTacModel &ticTacModel, TicTacView &ticTacView);

//    void renderGameScreenC(bool drawHint);
    void initializePlayer();
    void startGame();
    
private:
    class TicTacModel ticTacModel;
    class TicTacView ticTacView;
    
    char humanID = 'O';
    char computerID = 'X';
    
    bool nextMoveIsByHuman = true ;

    void askWhoStarts();
    void askPlayerToMove();
    
    void calculateAndDoYourMove();
    int getUserNextMove();
    
    void askComputerToMove();
    
    void askPlayersSign();
          
};

#endif /* TICTACCONTROLLER_H */

