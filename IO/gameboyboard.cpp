#include "gameboyboard.h"

GameBoyBoard::GameBoyBoard() {
    initFilledBoard(MAIN_WIN, true, true, true, true);
    initDisplayBoard(MAIN_WIN, BLOCK_RED);
    initDisplayBoard(RIGHT_BOTTOM_WIN, BLOCK_RED);
    gameScore = 0;
    gameLevel = 1;
    showDisplayBoard(RIGHT_BOTTOM_WIN);
    showDisplayBoard(RIGHT_TOP_WIN);
    showDisplayBoard(MAIN_WIN);
}

void GameBoyBoard::initFilledBoard(int winNum, bool ls, bool rs, bool ts, bool bs) {
    switch(winNum) {
        case MAIN_WIN:
            for (int row = 0; row <= MAIN_GAME_BOARD_HEIGHT; row++) {
                for (int column = 0; column <= MAIN_GAME_BOARD_WIDTH; column++) {
                    mainFilledBoard[row][column] = false;
                    if (ls && column == 0) {
                        mainFilledBoard[row][column] = true;
                    }
                    if (rs && column == MAIN_GAME_BOARD_WIDTH) {
                        mainFilledBoard[row][column] = true;
                    }
                    if (ts && row == 0) {
                        mainFilledBoard[row][column] = true;
                    }
                    if (bs && row == MAIN_GAME_BOARD_HEIGHT) {
                        mainFilledBoard[row][column] = true;
                    }
                }
            }
            break;
        default:
            break;
    }
}


void GameBoyBoard::initDisplayBoard(int winNum, int type) {
    switch(winNum) {
        case MAIN_WIN:
            for (int row = 0; row <= MAIN_GAME_BOARD_HEIGHT; row++) {
                for (int column = 0; column <= MAIN_GAME_BOARD_WIDTH; column++) {
                    mainDisplayBoard[row][column] = type;
                }
            }
            break;
        case RIGHT_BOTTOM_WIN:
            for (int row = 0; row <= RIGHT_BOTTOM_GAME_BOARD_HEIGHT; row++) {
                for (int column = 0; column <= RIGHT_BOTTOM_GAME_BOARD_WIDTH; column++) {
                    rbDisplayBoard[row][column] = type;
                }
            }
            break;
        default:
            break;
    }   
}

void GameBoyBoard::showDisplayBoard(int winNum) {
    switch(winNum) {
        case MAIN_WIN:
            for (int row = 0; row < MAIN_GAME_BOARD_HEIGHT; row++) {
                for (int column = 1; column < MAIN_WIN_WIDTH; column++) {
                    int blockType = mainDisplayBoard[row][column];
                    //2*(column-1)+1
                   GameBoyIO::getInstance().drawBlock(winNum, row + 1, 2*column-1, blockType);
                }
            }
            break;
        case RIGHT_BOTTOM_WIN:
            GameBoyIO::getInstance().printWords(winNum, 1, 1, "Next Block:", A_BOLD);
            for (int row = 0; row < RIGHT_BOTTOM_GAME_BOARD_HEIGHT; row++) {
                for (int column = 0; column < RIGHT_BOTTOM_GAME_BOARD_WIDTH; column++) {
                    int blockType = rbDisplayBoard[row][column];
                    GameBoyIO::getInstance().drawBlock(winNum, row + 2, 2*column-1, blockType);
                }
            }
            break;
        case RIGHT_TOP_WIN:
            GameBoyIO::getInstance().printWords(winNum, 1, 2, "Score:");
            GameBoyIO::getInstance().printWords(winNum, 2, 2, intToStr(gameScore), A_BOLD);
            GameBoyIO::getInstance().printWords(winNum, 4, 2, "Level:");
            GameBoyIO::getInstance().printWords(winNum, 5, 2, intToStr(gameLevel), A_BOLD);
            break;
        default:
            break;
    }
    GameBoyIO::getInstance().refreshWin(winNum);
}

