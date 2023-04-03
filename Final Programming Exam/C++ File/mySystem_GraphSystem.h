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
//
// Add your own functions if necessary
//
#ifndef __MY_GRAPH_SYSTEM_H_
#define __MY_GRAPH_SYSTEM_H_
#include "../headers.h"
#include <string>
#include "../primitives/vector3d.h"
#include <vector>
#include "base_class.h"
#include "graph_basics.h"
#include "myBasicTools.h"

using std::vector;

class Param {
public:
    static int GRAPH_MAX_NUM_NODES;
    static int GRAPH_MAX_NUM_EDGES;
};



class GRAPH_SYSTEM : public BASE_SYSTEM {

protected:
    void drawNodes_Indirect() const;
    void drawEdges_Indirect() const;
    void drawSelectedNode_Indirect() const;
    //
    GRAPH_NODE* GRAPH_SYSTEM::findNearestNode(double x, double z, double& cur_distance2);
    void deleteNode(int nodeID);
    void deleteSelectedNode();
    //
    void createDefaultGraph();
    void createNet_Circular(int n, int num_layers);
    void createNet_Square(int n, int num_layers);
    void createNet_RadialCircular(int n);
    void createRandomGraph_DoubleCircles(int n);
    void createBoxGraph();
    void createSpiralGraph();
    void createVineGraph();
    void createSnakeGraph();
    //
    // Implement your own stuff
    //
public:
    double doubleCirclesNodes = 18;
    GRAPH_SYSTEM();
    void update();
    void stopAutoNodeDeletion();
    void reset();
    void askForInput();
    void clickAt(double x, double z);
    void handleKeyPressedEvent(unsigned char key);
    void handlePassiveMouseEvent(double x, double y);
    void draw() const;

    int addNode(float x, float y, float z, float r = 1.0);
    int addEdge(int nodeID_0, int nodeID_1);
    bool isSelectedNode() const;
    void getInfoOfSelectedPoint(double& r, vector3& p) const;
    //
    int getNumOfEdges() const;
    vector3 getNodePositionOfEdge(int edgeIndex, int nodeIndex) const;

    int getNumOfNodes() const;
    void getNodeInfo(int nodeIndex, double& r, vector3& p) const;
    int counter_columns = 0;
    int snake_length = 0;
protected:
    //
    // Implement your own stuff
    //
    vector<GRAPH_NODE> mNodesPool;
    vector<int> mActiveNodes;
    vector<GRAPH_EDGE> mEdgesPool;
    vector<int> mActiveEdges;
    int mCurNumOfNodes;
    int mCurNumOfEdges;
    //
    GRAPH_NODE* mSelectedNode;
    GRAPH_NODE* mPassiveSelectedNode;
    //
    bool mFlgAutoNodeDeletion;
};

#endif