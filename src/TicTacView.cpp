/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   TicTacView.cpp
 * Author: Mahyar
 *
 * Created on March 1, 2020, 12:40 PM
 */


#include "TicTacView.h"
#include <conio.h>
//#include <stdio.h>

TicTacView::TicTacView() {
}

TicTacView::~TicTacView() {
}

/**
 * Draws a line of board
 * @param boardStatus
 * @param lastRowNum
 */
void TicTacView::drawBoardLine(char * boardStatus, int lastRowNum) {
    if (((lastRowNum + 1) % ROWCOUNT) == 0) return;
    string noDataLine = "";
    for (int j = 0; j < COLUMNCOUNT; j++) {
        noDataLine += "---";
        if (((j + 1) % COLUMNCOUNT) != 0)
            noDataLine += "|";
    }
    cout << noDataLine << "\n";
}

/**
 *
 * @param dataArray
 * @param lastRowNum
 */
void TicTacView::drawBoardCellRow(char * dataArray, int lastRowNum) {

    string boardRow = "";
    string s;

    for (int j = 0; j < COLUMNCOUNT; j++) {
        s = dataArray[lastRowNum * 3 + j];
        boardRow += " " + s + " ";
        if (((j + 1) % COLUMNCOUNT) != 0)
            boardRow += "|";
    }
    cout << boardRow << "\n";
}

void TicTacView::drawBoard(char * boardDataArray) {
    for (int i = 0; i < ROWCOUNT; i++) {
        drawBoardCellRow(boardDataArray, i);
        drawBoardLine(boardDataArray, i);
    }
}

/**
 *
 * @param boardStatus
 */
void TicTacView::showGameBoard(char * boardStatus) {
    cout << "============\n";
    cout << " Computer: X \n";
    cout << "  Player: O \n";
    cout << "============\n";
    cout << " Game Board \n";
    cout << "============\n";
    drawBoard(boardStatus);
    cout << "\n\n";
}

void TicTacView::drawGameBoardHint(char * boardStatus) {
    char boardHintData[9];
    int dataArraySize = ROWCOUNT * COLUMNCOUNT;

    cout << "\n\n";
    cout << "===============\n";
    cout << "Game Board Map \n";
    cout << "===============\n";

    for (int i = 0; i < dataArraySize; i++) {
        if (boardStatus[i] == ' ')
            boardHintData[i] = to_string(i + 1)[0];
        else
            boardHintData[i] = ' ';
    }

    drawBoard(boardHintData);
    cout << "\n\n";
}

/**
 *
 * @param char * boardStatus a copy of boardStatus from Model
 * @param bool drawHint true means hint should be drawn
 */
void TicTacView::renderGameScreen(char * boardStatus, bool drawHint) {
    system("cls"); /** System call */

    showGameBoard(boardStatus);
    if (drawHint)
        drawGameBoardHint(boardStatus);

}

void TicTacView::prepareStartingBodyQuestion() {
    cout << "May I start the game? (Y or N)";
}

void TicTacView::preparePlayerMoveQuestion() {
    cout << "Select a cell number from 1 to 9 for your next move -> ";
}

/**
 *
 * @return int selected CellIndex, which is equal to playerNextCellNumber - 1
 */
int TicTacView::getUserNextMove(){
    int playerNextCellNumber;
    cin >> playerNextCellNumber;
    return playerNextCellNumber - 1;
}

void TicTacView::announceWinner(char winnerID, string winnerName) {
    char noUseChar;
    cout << "\n*******************************\n";
    cout << "*** " << winnerName << " (" << winnerID << ") is winner! ***\n";
    cout << "*******************************\n\n";
    cout << "Press any key to end.\n";
    noUseChar = getch();
}

void TicTacView::announceNoWinner() {
    char noUseChar;
    cout << "\n ------------------------\n";
    cout << " Tie! No one is winner!\n";
    cout << " ------------------------\n";
    cout << "Press any key to end.\n";
    noUseChar = getch();
}
