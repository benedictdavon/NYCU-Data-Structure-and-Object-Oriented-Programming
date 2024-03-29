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
// Add your own functions if necessary
//
#ifndef __MY_2048_SYSTEM_H_
#define __MY_2048_SYSTEM_H_
#include "../headers.h"
#include <string>
#include "../primitives/vector3d.h"
#include <vector>
#include "base_class.h"
#include "graph_basics.h"
#include "myBasicTools.h"

using std::vector;

#define MAX_2048_NX 10
#define MAX_2048_NZ 10

class MY_2048 : public BASE_SYSTEM {
protected:
    void draw_GridCell(int ix, int iz) const;
    void draw_GridCells() const;
    void draw_Board() const;
    void draw_Event() const;

    void reset();
    void generateNumber();
    void moveDown();
    void moveUp();
    void moveLeft();
    void moveRight();

    void generateNumbers_All();
    void generateNumbers_All_2to4();
    void generateNumbers_All_2to8();
    void generate_random();
    void generate_pyramid();
    void sort_num_col();
    void sort_num_row();
    void performAction(unsigned char key);

    //
    // Implement your own stuff
    //
public:
    MY_2048();
    MY_2048(int nx, int nz);
    void setDimension(int nx, int nz);
    void draw() const;
    void askForInput();
    void handleKeyPressedEvent(unsigned char key);
    void handleSpecialKeyPressedEvent(unsigned char key);
    void setPosition(int x, int z);
    void setFocus(bool flg);
    //
    void update();

    bool isAutoPlay() const;
    //
    void copyPrevious(const BASE_SYSTEM* m);
    //
    MY_2048& operator=(const MY_2048& m);
    int colKey = 0;
    int rowKey = 0;
protected:
    ///////////////////////////////////////////
    bool mFlgFocus;
    int mPositionX, mPositionZ;
    unsigned char mEvent;
    ///////////////////////////////////////////
    int mNX, mNZ;
    int mBoard[MAX_2048_NZ][MAX_2048_NX];
    //
    int mPreviousBoard[MAX_2048_NZ][MAX_2048_NX];
    //
    bool flg_AutoPlay;
    //
    //
    // Implement your own stuff
    //
    double computeScore() const;
    void copyCurBoardtoPrev();
    void copy2(const int src[][MAX_2048_NX], int target[][MAX_2048_NX]);
    void copy(const int src[][MAX_2048_NX]);
    void play_random();
    double perform_action_recursive(int level, unsigned char action, int board[][MAX_2048_NX]);
    double play_Auto(int numForwardMoves, unsigned char actionIndex);
};

#endif