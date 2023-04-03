//********************************************
// Student Name			: Benedict Davon Martono
// Student ID			: 110550201
// Student Email Address: benedictdavon@gmail.com
//********************************************
//
// Prof. Sai-Keung Wong
// Email:	cswingo@nycu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2022/04/25
//
#include "mySystem_2048.h"
#include <iostream>

using namespace std;

static unsigned char specialKeys[] = {
    GLUT_KEY_UP,
    GLUT_KEY_DOWN,
    GLUT_KEY_LEFT,
    GLUT_KEY_RIGHT
};

int numSpecialKeys = sizeof(specialKeys) / sizeof(unsigned char);

MY_2048::MY_2048()
{
    mNX = 4;
    mNZ = 4;
    reset();

    mPositionX = 0;
    mPositionZ = 0;
    mFlgFocus = true;
    //
    flg_AutoPlay = false;
}

MY_2048::MY_2048(int nx, int nz)
{
    mPositionX = 0;
    mPositionZ = 0;
    mFlgFocus = true;
    //
    // Implement your own stuff
    //
    flg_AutoPlay = false;
    mNX = nx;
    mNZ = nz;
    reset();
}

void MY_2048::setDimension(int nx, int nz)
{
    mFlgFocus = true;

    //
    // Implement your own stuff
    //
    mNX = nx;
    mNZ = nz;
    reset();
}


void MY_2048::setFocus(bool flg)
{
    mFlgFocus = flg;
}

void MY_2048::setPosition(int x, int z)
{
    mPositionX = x;
    mPositionZ = z;
}

//
// Copy the m's previous board 
// to the object's mBoard.
//
void MY_2048::copyPrevious(const BASE_SYSTEM* m)
{
    for (int j = 0; j < mNZ; ++j) {
        for (int i = 0; i < mNX; ++i) {
            mBoard[j][i] = ((MY_2048*)m)->mPreviousBoard[j][i];
        }
    }
}

// Copy current board to prev board
void MY_2048::copyCurBoardtoPrev()
{
    for (int j = 0; j < mNZ; j++) {
        for (int i = 0; i < mNX; i++) {
            mPreviousBoard[j][i] = mBoard[j][i];
        }
    }
}

//
//reset the game board
//
void MY_2048::reset()
{
    mEvent = 0;
    ///////////////////////////////////////
    //
    // Implement your own stuff
    //
    for (int i = 0; i < mNX; i++) {
        for (int j = 0; j < mNZ; j++) {
            mBoard[i][j] = 0;
        }
    }

    flg_AutoPlay = false;
}

//
// show messages and ask for input (if any)
//
void MY_2048::askForInput()
{
    //
    // Implement your own stuff
    //
    cout << "MY_2048" << endl;
    cout << "Key usage: " << endl;
    cout << "1: Generate randomly the number 2 and 4 for all the cells" << endl;
    cout << "2: Generate randomly the numbers 2, 4, and 8 for all the cells" << endl;
    cout << "3: Generate randomly the numbers for all the cells" << endl;
    cout << "r: Clear all the cells" << endl;
    cout << endl;
    cout << "UP, DOWN, LEFT, RIGHT: move the numbers to the respective side" << endl;
}

//
// randomly generate a new number
//
void MY_2048::generateNumber()
{
    //
    // Implement your own stuff
    //
    int x, y;
    do {
        x = (int)getRandDouble(0, mNX);
        y = (int)getRandDouble(0, mNZ);
    } while (mBoard[y][x] != 0);

    int Pow = (int)getRandDouble(0, 11) + 1;
    mBoard[y][x] = pow(2.0, Pow);

}

void MY_2048::moveDown()
{
    //
    // Implement your own stuff
    //    
    for (int col = 0; col < mNZ; col++) {
        vector<int> notZero;
        notZero.clear();

        for (int row = 0; row < mNX; row++) {
            //If current element is exist then put to notZero
            if (mBoard[row][col] != 0)
                notZero.push_back(mBoard[row][col]);
        }

        for (int i = 0; i < notZero.size(); i++) {
            mBoard[i][col] = notZero[i];
        }
        for (int i = notZero.size(); i < mNX; i++) {
            mBoard[i][col] = 0;
        }
    }
}

void MY_2048::moveUp()
{
    //
    // Implement your own stuff
    //
    for (int col = 0; col < mNZ; col++) {
        vector<int> notZero;
        notZero.clear();

        //row start reversely from moveDown()
        for (int row = mNX - 1; row >= 0; row--) {
            //if current element is exist then push to notZero
            if (mBoard[row][col] != 0)
                notZero.push_back(mBoard[row][col]);
        }


        //paste merged value to mBoard
        for (int i = 0; i < notZero.size(); i++) {
            mBoard[mNX - 1 - i][col] = notZero[i];
        }
        //the rest
        for (int i = notZero.size(); i < mNX; i++) {
            mBoard[mNX - 1 - i][col] = 0;
        }
    }
}

void MY_2048::moveLeft()
{
    //
    // Implement your own stuff
    //
    for (int row = 0; row < mNX; row++) {
        vector<int> notZero;
        notZero.clear();

        for (int col = 0; col < mNZ; col++) {
            //if current index has value then put to notZero
            if (mBoard[row][col] != 0)
                notZero.push_back(mBoard[row][col]);
        }

        int stop = notZero.size();
        for (int i = 0; i < stop - 1; i++) {
            //if current element is the same as beside it (LEFT)
            //merge the cell, add the value
            if (notZero[i] == notZero[i + 1]) {
                notZero[i] += notZero[i];
                notZero.erase(notZero.begin() + i + 1);
                stop--;
            }
        }

        for (int i = 0; i < notZero.size(); i++) {
            //paste notZero array to mBoard
            mBoard[row][i] = notZero[i];
        }
        //the rest
        for (int i = notZero.size(); i < mNX; i++) {
            mBoard[row][i] = 0;
        }
    }
}

void MY_2048::moveRight()
{
    //
    // Implement your own stuff
    //
    for (int row = 0; row < mNZ; row++) {
        //create array of nonzero elements
        vector<int> notZero;
        notZero.clear();

        //opposite from moveLeft()
        for (int col = mNX - 1; col >= 0; col--) {
            //if current element exists
            //push to notZero
            if (mBoard[row][col] != 0)
                notZero.push_back(mBoard[row][col]);
        }

        for (int i = 0; i < notZero.size(); i++) {
            //copy notZero to board
            mBoard[row][mNX - 1 - i] = notZero[i];
        }
        //the rest
        for (int i = notZero.size(); i < mNX; i++) {
            mBoard[row][mNX - 1 - i] = 0;
        }
    }
}

void MY_2048::generateNumbers_All_2to4()
{
    //
    // Implement your own stuff
    //
    for (int i = 0; i < mNX; i++) {
        for (int j = 0; j < mNZ; j++) {
            //get random power, 1 or 2
            int Pow = (int)getRandDouble(0, 2) + 1;
            mBoard[i][j] = pow(2.0, Pow);
        }
    }
}

void MY_2048::generateNumbers_All_2to8()
{
    //
    // Implement your own stuff
    //
    for (int i = 0; i < mNX; i++) {
        for (int j = 0; j < mNZ; j++) {
            //get random power, 1 or 2
            int Pow = (int)getRandDouble(0, 3) + 1;
            mBoard[i][j] = pow(2.0, Pow);
        }
    }
}

void MY_2048::generateNumbers_All()
{
    //
    // Implement your own stuff
    //
    for (int i = 0; i < mNX; i++) {
        for (int j = 0; j < mNZ; j++) {
            int index = (int)getRandDouble(0, 3) + 1;
            mBoard[i][j] = pow(2.0, index);
        }
    }
}

void MY_2048::handleKeyPressedEvent(unsigned char key)
{
    switch (key) {
    case 'r':
    case 'R':
        reset();
        break;
    case '1':
        generateNumbers_All_2to4();
        break;
    case '2':
        generateNumbers_All_2to8();
        break;
    case '3':
        generateNumbers_All();
        break;
    case '6':
        generate_random();
        break;
    case '7':
        generate_pyramid();
        break;
    case 'M':
    case 'm':
        sort_num_col();
        colKey++;
        break;
    case 'N':
    case 'n':
        sort_num_row();
        rowKey++;
        break;
    case 'a':
    case 'A':
        //flg_AutoPlay
        //for one step
        break;
    case ' ':
        // toggle to auto-play
        flg_AutoPlay = !flg_AutoPlay;
        break;
    }
}

void MY_2048::performAction(unsigned char key) {
    bool flgDone = false;

    switch (key) {
    case GLUT_KEY_UP:
        copyCurBoardtoPrev();
        flgDone = true;
        moveUp();
        mEvent = GLUT_KEY_UP;
        break;
    case GLUT_KEY_DOWN:
        copyCurBoardtoPrev();
        flgDone = true;
        moveDown();
        mEvent = GLUT_KEY_DOWN;
        break;
    case GLUT_KEY_LEFT:
        copyCurBoardtoPrev();
        flgDone = true;
        moveLeft();
        mEvent = GLUT_KEY_LEFT;
        break;
    case GLUT_KEY_RIGHT:
        copyCurBoardtoPrev();
        flgDone = true;
        moveRight();
        mEvent = GLUT_KEY_RIGHT;
        break;
    }

    if (flgDone) {
        generateNumber();
    }
}

void MY_2048::handleSpecialKeyPressedEvent(unsigned char key)
{
    //
    // It takes a long time to show a message!
    //
    cout << "MY_2048::handleSpecialKeyPressedEvent:" << key << endl;
    performAction(key);
}

bool MY_2048::isAutoPlay() const
{
    return flg_AutoPlay;
}

void MY_2048::copy2(const int src[][MAX_2048_NX], int target[][MAX_2048_NX])
{
    for (int j = 0; j < mNZ; j++) {
        for (int i = 0; i < mNX; i++) {
            target[j][i] = src[j][i];
        }
    }
}

void MY_2048::copy(const int src[][MAX_2048_NX])
{
    for (int j = 0; j < mNZ; j++) {
        for (int i = 0; i < mNX; i++) {
            mPreviousBoard[j][i] = src[j][i];
        }
    }
}


void MY_2048::play_random()
{
    int actionIndex = rand() % numSpecialKeys;
    int numForwardMoves = 3;
    handleSpecialKeyPressedEvent(specialKeys[actionIndex]);
    //play_Auto(numForwardMoves, specialKeys[actionIndex]);
}

double MY_2048::computeScore() const
{
    /* Power func to compute score is important, so the score of merged tiles is bigger than a pair of
   unmerged tiles of the one-level lower number. The system of power and best score is up to us
   the implementer.*/
    double score = 0;

    double largest_score = 0.0;
    for (int i = 0; i < mNZ; i++) {
        for (int j = 0; j < mNX; j++) {
            double s = mBoard[i][j];
            score += s * pow(s, 0.35);
        }
    }
    return score;

}

double MY_2048::perform_action_recursive(int numSteps, unsigned char action_key, int board[][MAX_2048_NX])
{
    double tScore = 0.0;
    //If level has reached maximum
    if (numSteps <= 0) {
        tScore = computeScore();
        return tScore;
    }

    //otherwise
    copy2(board, mBoard);
    performAction(action_key);
    //double tScore = computeScore();

    int initBoard[MAX_2048_NZ][MAX_2048_NX];
    copy2(mBoard, initBoard);
    double rate = 0.85;
    double score = 0.0;
    //Calculate score _ perform recursive for remaining level
    for (int i = 0; i < numSpecialKeys; i++) {
        score = score * pow(rate, numSteps) + perform_action_recursive(numSteps - 1, specialKeys[i], initBoard);
    }
    return score;
}

double MY_2048::play_Auto(int numForwardMoves, unsigned char actionIndex)
{
    //numForwardMoves = maximum level
    double score = 0.0;
    int initBoard[MAX_2048_NZ][MAX_2048_NX];
    copy2(mBoard, initBoard);

    double fScore = perform_action_recursive(numForwardMoves, actionIndex, initBoard);
    copy2(initBoard, mBoard);
    score = fScore;
    return score;
}


//
// The update( ) function is called every frame.
//
// Design an algorithm to automatically perform
// one step.
//
void MY_2048::update()
{
    //
    // It takes a long time to show a message!
    //
    cout << "MY_2048::update( )" << endl;
    cout << "MY_2048::flg_AutoPlay:\t" << flg_AutoPlay << endl;

    if (!flg_AutoPlay) return;

    //
    // Implement your own stuff
    //
    int score[4];
    for (int i = 0; i < numSpecialKeys; i++) {
        score[i] = play_Auto(7, specialKeys[i]);
    }
    int best_score = score[0];
    int action_index = 0;
    for (int i = 1; i < numSpecialKeys; i++) {
        if (score[i] > best_score) {
            best_score = score[i];
            action_index = i;
        }
    }
    performAction(specialKeys[action_index]);
}

void MY_2048::generate_random() {
    reset();
    int Pow;
    int x = 0, y = 0;

    for (int i = 0; i < 32; i++) {
        do {
            x = (int)getRandDouble(0, mNX);
            y = (int)getRandDouble(0, mNZ);
        } while (mBoard[y][x] != 0);

        Pow = (int)getRandDouble(0, 11) + 1;
        mBoard[y][x] = pow(2.0, Pow);
    }
   
}

void MY_2048::generate_pyramid() {
    reset();

    int Pow = 0;
    for (int y = 0; y < mNZ; y++) {
        for (int x = 0; x <= y; x++) {
            Pow = (int)getRandDouble(0, 11) + 1;
            mBoard[mNZ-1-y][mNX-1-x] = pow(2.0, Pow);
        }
    }
}

void MY_2048::sort_num_col() {
    vector<int> num;
    for (int i = 0; i < mNX; i++) {
        num.clear();
        for (int j = 0; j < mNZ; j++) {
            if (mBoard[j][i] != 0) {
                num.push_back(mBoard[j][i]);
            } 
        }

        if (colKey % 2 == 0) {
            int index = 0, key = 0;
            for (int i = 1; i < num.size(); i++) {
                key = num[i];
                index = i - 1;

                while (index >= 0 && num[index] > key) {
                    num[index + 1] = num[index];
                    index--;
                }

                num[index + 1] = key;
            }
        } else {
            int index = 0, key = 0;
            for (int i = 1; i < num.size(); i++) {
                key = num[i];
                index = i - 1;

                while (index >= 0 && num[index] < key) {
                    num[index + 1] = num[index];
                    index--;
                }

                num[index + 1] = key;
            }
        }

        int index = 0;
        for (int j = mNZ-1; j >= 0; j--) {
            if (mBoard[j][i] != 0) {
                mBoard[j][i] = num[index];
                index++;
            }
        }
    }
}
void MY_2048::sort_num_row() {
    vector<int> num;
    for (int i = 0; i < mNZ; i++) {
        num.clear();
        for (int j = 0; j < mNX; j++) {
            if (mBoard[i][j] != 0) {
                num.push_back(mBoard[i][j]);
            }
        }

        if (rowKey % 2 == 0) {
            int index = 0, key = 0;
            for (int i = 1; i < num.size(); i++) {
                key = num[i];
                index = i - 1;

                while (index >= 0 && num[index] > key) {
                    num[index + 1] = num[index];
                    index--;
                }

                num[index + 1] = key;
            }
        }
        else {
            int index = 0, key = 0;
            for (int i = 1; i < num.size(); i++) {
                key = num[i];
                index = i - 1;

                while (index >= 0 && num[index] < key) {
                    num[index + 1] = num[index];
                    index--;
                }

                num[index + 1] = key;
            }
        }

        int index = 0;
        for (int j = mNX - 1; j >= 0; j--) {
            if (mBoard[i][j] != 0) {
                mBoard[i][j] = num[index];
                index++;
            }
        }
    }
}