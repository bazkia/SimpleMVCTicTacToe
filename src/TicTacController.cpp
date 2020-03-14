/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TicTacController.cpp
 * Author: Mahyar
 * 
 * Created on March 1, 2020, 7:43 PM
 */

#include "TicTacController.h"

TicTacController::TicTacController() {
}

TicTacController::~TicTacController() {
}

TicTacController::TicTacController(TicTacModel &ticTacModel, TicTacView &ticTacView) {
    this->ticTacModel = ticTacModel;
    this->ticTacView = ticTacView;
}

/**
 * Asks to determine who plays first
 * and with which sign (X or O)
 */
void TicTacController::initializePlayer() {
    askWhoStarts();
    askPlayersSign();
}


/**
 * Asks user to find who is starting 
 * This function will be developed in future. 
 * Now computer starts first
 */
void TicTacController::askWhoStarts() {
    string playerSelection = "";

    ticTacView.prepareStartingBodyQuestion();
    playerSelection = "Y";
    
    ticTacModel.setStarter((char)toupper(playerSelection[0]));
}

/**
 * Asks user to find who is starting 
 * This function will be developed in future. 
 * Now computer starts sign is "X"
 */
void TicTacController::askPlayersSign() {
    ticTacModel.setHumanID('O');
    ticTacModel.setComputerID('X');
}

/**
 * Main process of the game
 */
void TicTacController::startGame() {
    char winner = NOBODY;
    string winnerName;
    char boardLayoutCopy[MAXCELLCOUNT];

    while (winner == NOBODY) {
        if (ticTacModel.getNextMove() == HUMAN){   
            //Human turn
            askPlayerToMove();
            ticTacModel.changeNextMove();
        } else {
            askComputerToMove();
            ticTacModel.changeNextMove();
        }
        winner = ticTacModel.checkWinner();
    }

    //boardLayoutCopy
    ticTacView.renderGameScreen(ticTacModel.getBoardStatusCopy(boardLayoutCopy), false);

    if(winner == TIE){
        ticTacView.announceNoWinner();
        return;
    }
    
    if(winner == ticTacModel.getComputerID()){
        ticTacView.announceWinner(ticTacModel.getComputerID(), 
                                    ticTacModel.getComputerPlayerName());
        return;
    }
    
    ticTacView.announceWinner(ticTacModel.getHumanID(), 
                                    ticTacModel.getHumanPlayerName());
}

/**
 * Render screen and prepare question and find user answer
 */
void TicTacController::askPlayerToMove() {
    int playerNextCellIndex = 0;
    char boardLayoutCopy[MAXCELLCOUNT];
    
    do {
        ticTacView.renderGameScreen(ticTacModel.getBoardStatusCopy(boardLayoutCopy));
        ticTacView.preparePlayerMoveQuestion();

        playerNextCellIndex = ticTacView.getUserNextMove();

    } while (!ticTacModel.isPlayerMoveValid(playerNextCellIndex));

    ticTacModel.recordMove(playerNextCellIndex, humanID);
}

/**
 * Calls Model to run main logic of computer moves. 
 */
void TicTacController::askComputerToMove() {
    
    ticTacModel.doComputerMove();
//    int playerCellIndex;
//
//    do {
//        srand(time(0));
//        playerCellIndex = rand() % 10;
//    } while (!ticTacModel.isPlayerMoveValid(playerCellIndex));
//    ticTacModel.recordMove(playerCellIndex, computerID);
}

//int TicTacController::getUserNextMove(){
//    int playerNextCellNumber;
//    cin >> playerNextCellNumber;
//    return playerNextCellNumber - 1;
//}