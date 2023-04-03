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
#include <iostream>
#include <time.h>
#include "mySystem_GraphSystem.h"
#include "myBasicTools.h"
#define PI 3.1415926

using namespace std;

const int MIN_NODES = 3;
const int MAX_NODES = 36;

int Param::GRAPH_MAX_NUM_NODES = 10000;
int Param::GRAPH_MAX_NUM_EDGES = 10000;

GRAPH_SYSTEM::GRAPH_SYSTEM()
{
    mFlgAutoNodeDeletion = false;
    createDefaultGraph();
    //
    // Implement your own stuff
    //
}

void GRAPH_SYSTEM::reset()
{
    stopAutoNodeDeletion();
    mPassiveSelectedNode = 0;
    mSelectedNode = 0;
    //
    // Implement your own stuff
    //
    mNodesPool.clear();
    mActiveNodes.clear();
    mEdgesPool.clear();
    mActiveEdges.clear();
    mCurNumOfNodes = 0;
    mCurNumOfEdges = 0;
}

void GRAPH_SYSTEM::createDefaultGraph()
{
    reset();
    //
    // Implement your own stuff
    //
    // Add 3 nodes for default node
    int v0 = addNode(0.0, 0.0, 0.0, 1.0);
    int v1 = addNode(0.0, 0.0, 10.0, 1.0);
    int v2 = addNode(10.0, 0.0, 0.0, 1.0);

    // Push to Active Node array
    mActiveNodes.push_back(v0);//0
    mActiveNodes.push_back(v1);//1
    mActiveNodes.push_back(v2);//2

    // Add edge that connects as default graph
    mActiveEdges.push_back(addEdge(0, 2));
    mActiveEdges.push_back(addEdge(1, 2));

}

void GRAPH_SYSTEM::createRandomGraph_DoubleCircles(int n)
{
    reset();

    float dx = 5.0;
    float dz = 5.0;
    float r = 15; // radius
    float d = 10; // layer distance
    float offset_x = 15.;
    float offset_z = 15.;
    //
    // Implement your own stuff
    //
    //Set angle for the nodes to create a whole circle
    float angle = 2 * PI / n;
    for (int i = 0; i < 2; i++) { //two circles
        for (int j = 0; j < n; j++) { //n nodes in a circle
            //set position x and z based on i and j
            float x = offset_x + (r + i * d) * cos(j * angle);
            float z = offset_z + (r + i * d) * sin(j * angle);
            //create node from that position
            int node = addNode(x, 0.0, z, 1.0);
            //put to active node array
            mActiveNodes.push_back(node);
        }
    }

    //notIntersect = prevents the edge from trespassing through center
    int notIntersect = 53 * (PI / 180) / angle;
    for (int i = 0; i < n; i++) {
        int index = i - notIntersect;
        index = index + int(getRandDouble(0, 2 * notIntersect));
        index = (index + n) % n + n;
        int edge = addEdge(i, index);
        mActiveEdges.push_back(edge);
    }
}

void GRAPH_SYSTEM::createNet_Circular(int n, int num_layers)
{
    reset();

    float dx = 5.0;
    float dz = 5.0;
    float r = 5; // radius
    float d = 5; // layer distance 
    float offset_x = 15.;
    float offset_z = 15.;
    //
    // Implement your own stuff
    //
    float angle = 2 * PI / n;
    for (int i = 0; i <= num_layers; i++) { //num_layers circles
        for (int j = 0; j < n; j++) { //n nodes per circle
            //determine value of position x and z
            //based on the layer and node number
            float x = offset_x + (r + i * d) * cos(j * angle);
            float z = offset_z + (r + i * d) * sin(j * angle);
            int node = addNode(x, 0.0, z, 1.0);
            mActiveNodes.push_back(node);
        }
    }

    for (int i = 0; i < num_layers; i++) {
        for (int j = 0; j < n - 1; j++) {
            int index = i * n + j;
            mActiveEdges.push_back(addEdge(index, index + 1));
            mActiveEdges.push_back(addEdge(index, index + n));
        }
        mActiveEdges.push_back(addEdge(i * n + n - 1, i * n));
        mActiveEdges.push_back(addEdge(i * n + n - 1, i * n + n - 1 + n));
    }
}
void GRAPH_SYSTEM::createNet_Square(int n, int num_layers)
{
    reset();

    float dx = 5.0;
    float dz = 5.0;
    float r = 5; // radius
    float d = 5; // layer distance 
    float offset_x = 5.;
    float offset_z = 5.;
    //
    // Implement your own stuff
    //
    for (int i = 0; i < num_layers; i++) {
        for (int j = 0; j < num_layers; j++) {
            float x = j * dx;
            float z = i * dz;
            int node = addNode(x, 0.0, z, 1.0);
            mActiveNodes.push_back(node);
        }
    }

    //put edges in all position based on nodes
    //to create the square we want
    for (int i = 0; i < num_layers; i++) {
        for (int j = 0; j < num_layers - 1; j++) {
            int index = i * num_layers + j;
            int edge = addEdge(index, index + 1);
            mActiveEdges.push_back(edge);
        }
    }
    for (int i = 0; i < num_layers - 1; i++) {
        for (int j = 0; j < num_layers; j++) {
            int index = i * num_layers + j;
            int edge = addEdge(index, index + num_layers);
            mActiveEdges.push_back(edge);
        }
    }

    //Delete node in the center
    //Edges adjacent to it are automatically deleted
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= n; j++) {
            int complete = (num_layers - n) / 2;
            deleteNode(complete * num_layers - 1 + complete + j + num_layers * i);
        }
    }
}

void GRAPH_SYSTEM::createNet_RadialCircular(int n) {

    reset();

    float offset_x = 15.0;
    float offset_z = 15.0;

    float r = 15; // radius
    //
    // Implement your own stuff
    //    
    int center = addNode(offset_x, 0.0, offset_z, 1.0);
    mActiveNodes.push_back(center);

    //Create nodes in a circle surround center node
    float angle = 2 * PI / n;
    for (int i = 0; i < n; i++) {
        float x = offset_x + r * cos(i * angle);
        float z = offset_z + r * sin(i * angle);
        int node = addNode(x, 0.0, z, 1.0);
        mActiveNodes.push_back(node);
    }

    //Create edge from center to each of node in a circle
    for (int i = 0; i < n; i++) {
        int edge = addEdge(0, i + 1);
        mActiveEdges.push_back(edge);
    }
}

void GRAPH_SYSTEM::createBoxGraph() {
    reset();

    int n1 = addNode(0.0, 0.0, 0.0, 1);
    int n2 = addNode(10.0, 0.0, 0.0, 1);
    int n3 = addNode(0.0, 0.0, 10.0, 1);
    int n4 = addNode(10.0, 0.0, 10.0, 1);

    mActiveNodes.push_back(n1);
    mActiveNodes.push_back(n2);
    mActiveNodes.push_back(n3);
    mActiveNodes.push_back(n4);

    mActiveEdges.push_back(addEdge(0, 1));
    mActiveEdges.push_back(addEdge(0, 2));
    mActiveEdges.push_back(addEdge(0, 3));
    mActiveEdges.push_back(addEdge(2, 3));
    mActiveEdges.push_back(addEdge(1, 3));
}

void GRAPH_SYSTEM::createSpiralGraph() {
    reset();

    int n = 5, m = 5;
    int boundary = n - 1;
    int xLeft = n - 1;
    int yLeft = m - 1;
    char dirr = 'r';
    int row = 0, col = 0;

    for (int i = 1; i < (m * n) + 1; i++)
    {
        float x = col * 5.0;
        float z = row * 5.0;
        int node = addNode(x, 0.0, z, 1.0);
        mActiveNodes.push_back(node);
        //printf("row: %d, col: %d, boundary: %d, xLeft: %d, yLeft: %d, i: %d\n", row, col, boundary, xLeft, yLeft, i);
        switch (dirr)
        {
        case 'r':
            col += 1;
            break;
        case 'l':
            col -= 1;
            break;
        case 'u':
            row -= 1;
            break;
        case 'd':
            row += 1;
            break;
        }

        if (i == boundary)
        {
            if (dirr == 'd' || dirr == 'u') {
                boundary += xLeft;
                xLeft -= 1;
            }
            else if (dirr == 'r' || dirr == 'l') {
                boundary += yLeft;
                yLeft -= 1;
            }

            switch (dirr)
            {

                // if right, rotate to down
            case 'r':
                dirr = 'd';
                break;

                // if down, rotate to left
            case 'd':
                dirr = 'l';
                break;

                // if left, rotate to up
            case 'l':
                dirr = 'u';
                break;

                // if up, rotate to right
            case 'u':
                dirr = 'r';
                break;
            }
        }
    }

    for (int i = 0; i < 24; i++) {
        int edge = addEdge(i, i + 1);
        mActiveEdges.push_back(edge);
    }

}
void GRAPH_SYSTEM::createVineGraph() {
    reset();
    cout << "counter col: " << counter_columns << endl;
    for (int i = 0; i <= counter_columns; i++) {
        for (int j = 0; j < 5; j++) {
            float x = i * 5.0;
            float z = j * 5.0;
            int node = addNode(x, 0.0, z, 1.0);
            mActiveNodes.push_back(node);
        }

        for (int j = 0; j < 4; j++) {
            int edge = addEdge(5*i+j, 5 * i + j + 1);
            mActiveEdges.push_back(edge);
        }
    }
}
void GRAPH_SYSTEM::createSnakeGraph() {
    reset();
    float x = 0.0;
    for (int i = 0; i <= snake_length; i++) {
        if ((i / 5) % 2 == 1)
            x = (4-(i%5)) * 5.0;
        else
            x = (i%5) * 5.0;
        float z = (i/5) * 5.0;
        int node = addNode(x, 0.0, z, 1.0);
        mActiveNodes.push_back(node);
    }

    for (int j = 0; j < snake_length; j++) {
        int edge = addEdge(j, j + 1);
        mActiveEdges.push_back(edge);
    }
}

// return node id
int GRAPH_SYSTEM::addNode(float x, float y, float z, float r)
{
    //
    // Implement your own stuff
    //  
   //Create new GRAPH_NODE object to be created
    GRAPH_NODE new_node;
    //Set that node's id as current pool size before being pushed.
    int newID = mNodesPool.size();
    //Set its position in the graph
    new_node.p = vector3(x, y, z);
    //Set its radius
    new_node.r = r;
    //set id as position of current pool size before being pushed
    new_node.id = newID;

    //set dynamic ID as current Active nodes before being pushed
    new_node.dynamicID = mActiveNodes.size();
    //do not set edgeID first
    new_node.edgeID.clear();

    //Add active nodes number
    mCurNumOfNodes++;
    //Push that node id to Nodes pool
    mNodesPool.push_back(new_node);

    return new_node.id;

}

// return edge id
int GRAPH_SYSTEM::addEdge(int nodeID_0, int nodeID_1)
{
    //
    // Implement your own stuff
    //  
    GRAPH_EDGE new_edge; //new edge object

    //Set edge id as current pool size before being pushed.
    int newID = mEdgesPool.size();
    new_edge.id = newID;

    //Set dynamic id as Active Edges array size before being pushed
    new_edge.dynamicID = mActiveEdges.size();

    //Set the id of connected nodes by that edge
    new_edge.nodeID[0] = nodeID_0;
    new_edge.nodeID[1] = nodeID_1;

    //Set theedge id to each of the node id in Nodes pool
    mNodesPool[nodeID_0].edgeID.push_back(new_edge.id);
    mNodesPool[nodeID_1].edgeID.push_back(new_edge.id);

    //Add the current active number of edges
    mCurNumOfEdges++;

    mEdgesPool.push_back(new_edge); //push ede to the pool

    return new_edge.id;
}

void GRAPH_SYSTEM::askForInput()
{
    //
    // Implement your own stuff
    // 
    cout << "GRAPH_SYSTEM" << endl;
    cout << "Key usage: " << endl;
    cout << "1: Create a default graph" << endl;
    cout << "2: Create a circular graph" << endl;
    cout << "3: Create a square graph" << endl;
    cout << "4: Create a radial circular graph" << endl;
    cout << "5: Create a random edge double circle graph" << endl;

    cout << "Delete: delete a node and all the edges attached at it" << endl;
    cout << "Spacebar: unselect the selected node" << endl;
    cout << endl;

    cout << "Use the mouse to select nodes and add edges" << endl;
    cout << "Click the left button to select/unselect or create an edge" << endl;
    cout << endl;

    cout << "A selected node is highlighted as red." << endl;
}

GRAPH_NODE* GRAPH_SYSTEM::findNearestNode(double x, double z, double& cur_distance2)
{
    GRAPH_NODE* n = 0;
    //
    // Implement your own stuff
    // 

    vector3 nearestNode = vector3(x, 0.0, z); //Set position of nearest node
    double minDis2 = 10; //set minimum distance

    //Search through all of current active nodes
    for (int i = 0; i < mCurNumOfNodes; i++) {
        //get position of node from Active node array of index i
        vector3 nodePosFromActive = mNodesPool[mActiveNodes[i]].p;
        //set distance of that node from mouse
        double Dis2 = computePointLineSegmentDistance2(nodePosFromActive, nearestNode, nearestNode);
        if (Dis2 < minDis2) {
            //if the distance is less than minimum distance
            cur_distance2 = Dis2;
            //set nearest node as that node.
            n = &mNodesPool[mActiveNodes[i]];
        }
    }

    return n;
}

//
// compute mSelectedNode
//
void GRAPH_SYSTEM::clickAt(double x, double z)
{
    // Implement your own stuff
    GRAPH_NODE* n = 0;
    double cur_distance2 = 0;
    n = findNearestNode(x, z, cur_distance2);
    if (mSelectedNode != 0) {
        //if the node is on selected status before
        //set to deselect
        int edge = addEdge(mSelectedNode->id, n->id);
        mActiveEdges.push_back(edge);
        mSelectedNode = 0;
    }
    else if (cur_distance2 <= n->r * n->r)
        //if distance is radius times radius
        //and also not selected
        // then set as selected
        mSelectedNode = n;
}

void GRAPH_SYSTEM::deleteNode(int nodeID) {
    //
    // Implement your own stuff
    // 
    int node_dynamic_index;
    for (int i = 0; i < getNumOfNodes(); i++) {
        //search through the whole active node array
        //search for nodeID
        if (mActiveNodes[i] == nodeID) {
            //if value of array = nodeID has been found
            //set dynamic id as the index where that ID is found
            node_dynamic_index = i;
            break;
        }
    }

    for (int i = node_dynamic_index + 1; i < mCurNumOfNodes; i++) {
        //reduce the number of dynamic ID from pool
        //based on ActiveNode
        mNodesPool[mActiveNodes[i]].dynamicID--;
    }
    mActiveNodes.erase(mActiveNodes.begin() + node_dynamic_index);

    //reduce number of current active nodes
    mCurNumOfNodes--;

    //int stop = mNodesPool[node_ID].edgeID.size();
    for (int i = 0; i < mNodesPool[nodeID].edgeID.size(); i++) {
        //get edgeID from that node pool
        int edge_ID = mNodesPool[nodeID].edgeID[i];
        int edge_dynamic_index = 0;

        //if the nodeID is fit
        if (mEdgesPool[edge_ID].nodeID[0] == nodeID) {
            for (int j = 0; j < mNodesPool[mEdgesPool[edge_ID].nodeID[1]].edgeID.size(); j++) {
                if (mNodesPool[mEdgesPool[edge_ID].nodeID[1]].edgeID[j] == edge_ID) {
                    mNodesPool[mEdgesPool[edge_ID].nodeID[1]].edgeID.erase(mNodesPool[mEdgesPool[edge_ID].nodeID[1]].edgeID.begin() + j);
                    break;
                }
            }
        }
        else {
            for (int j = 0; j < mNodesPool[mEdgesPool[edge_ID].nodeID[0]].edgeID.size(); j++) {
                if (mNodesPool[mEdgesPool[edge_ID].nodeID[0]].edgeID[j] == edge_ID) {
                    mNodesPool[mEdgesPool[edge_ID].nodeID[0]].edgeID.erase(mNodesPool[mEdgesPool[edge_ID].nodeID[0]].edgeID.begin() + j);
                    break;
                }
            }
        }

        for (int j = 0; j < getNumOfEdges(); j++) {
            if (mActiveEdges[j] == edge_ID) {
                edge_dynamic_index = j;
                break;
            }
        }

        for (int j = edge_dynamic_index + 1; j < getNumOfEdges(); j++) {
            mEdgesPool[mActiveEdges[j]].dynamicID--;
        }

        mActiveEdges.erase(mActiveEdges.begin() + edge_dynamic_index);
        mCurNumOfEdges--;
    }
}

void GRAPH_SYSTEM::deleteSelectedNode() {
    //
    // Implement your own stuff
    // 
    if (mSelectedNode == 0) return;

    int node_ID = mSelectedNode->id;
    mSelectedNode = 0;
    mPassiveSelectedNode = 0;
    deleteNode(node_ID);
}

bool GRAPH_SYSTEM::isSelectedNode() const
{
    //
    // mSelectedNode != 0;
    //
    // Implement your own stuff
    // 

    if (mSelectedNode != 0)
        return true;
    return false;
}

void GRAPH_SYSTEM::getInfoOfSelectedPoint(double& r, vector3& p) const
{
    // r = mSelectedNode->r;
    // p = mSelectedNode->p;
    //
    // Implement your own stuff
    // 
    r = mSelectedNode->r;
    p = mSelectedNode->p;
}



void GRAPH_SYSTEM::handleKeyPressedEvent(unsigned char key)
{
    if (key != '8')
        counter_columns = 0;
    if (key != '9')
        snake_length = 0;
    switch (key) {
    case 127: // delete
        mFlgAutoNodeDeletion = false;
        deleteSelectedNode();
        break;
    case '1':
        mFlgAutoNodeDeletion = false;
        createDefaultGraph();
        mSelectedNode = 0;
        break;
    case '2':
        mFlgAutoNodeDeletion = false;
        createNet_Circular(12, 3);
        mSelectedNode = 0;
        break;
    case '3':
        mFlgAutoNodeDeletion = false;
        createNet_Square(3, 11); // you can modify this
        mSelectedNode = 0;

        break;
    case '4':
        mFlgAutoNodeDeletion = false;
        createNet_RadialCircular(24);
        mSelectedNode = 0;

        break;
    case '5':
        mFlgAutoNodeDeletion = false;
        createRandomGraph_DoubleCircles(doubleCirclesNodes);
        mSelectedNode = 0;
        break;
    case '6':
        mFlgAutoNodeDeletion = false;
        createBoxGraph();
        mSelectedNode = 0;
        break;
    case '7':
        mFlgAutoNodeDeletion = false;
        createSpiralGraph();
        mSelectedNode = 0;
        break;
    case '8':
        mFlgAutoNodeDeletion = false;
        createVineGraph();
        counter_columns++;
        mSelectedNode = 0;
        break;
    case '9':
        mFlgAutoNodeDeletion = false;
        createSnakeGraph();
        snake_length++;
        mSelectedNode = 0;
        break;
    case '<':
        mFlgAutoNodeDeletion = false;
        if (doubleCirclesNodes - 1 < MIN_NODES)
            return;
        doubleCirclesNodes--;
        createRandomGraph_DoubleCircles(doubleCirclesNodes);
        mSelectedNode = 0;
        break;
    case '>':
        mFlgAutoNodeDeletion = false;
        if (doubleCirclesNodes + 1 > MAX_NODES)
            return;
        doubleCirclesNodes++;
        createRandomGraph_DoubleCircles(doubleCirclesNodes);
        mSelectedNode = 0;
        break;
    case ' ':
        mFlgAutoNodeDeletion = false;
        mSelectedNode = 0;
        break;
    case 'g':
        mFlgAutoNodeDeletion = !mFlgAutoNodeDeletion;
        break;
    }
}

void GRAPH_SYSTEM::handlePassiveMouseEvent(double x, double z)
{
    double cur_d2;
    GRAPH_NODE* n = findNearestNode(x, z, cur_d2);
    if (n == 0) return;
    if (cur_d2 > n->r * n->r) {
        mPassiveSelectedNode = 0;
        return;
    }
    mPassiveSelectedNode = n;
}

//
// get the number of nodes
//
int GRAPH_SYSTEM::getNumOfNodes() const
{
    //
    // Implement your own stuff
    // 
    return mCurNumOfNodes;
}

void GRAPH_SYSTEM::getNodeInfo(int nodeIndex, double& r, vector3& p) const
{
    //
    // Implement your own stuff
    // 
    r = mNodesPool[mActiveNodes[nodeIndex]].r;
    p = mNodesPool[mActiveNodes[nodeIndex]].p;
}

//
// return the number of edges
//
int GRAPH_SYSTEM::getNumOfEdges() const
{
    //
    // Implement your own stuff
    // 
    return mCurNumOfEdges;
}

//
// an edge should have two nodes: index 0 and index 1
// return the position of node with nodeIndex
//
vector3 GRAPH_SYSTEM::getNodePositionOfEdge(int edgeIndex, int nodeIndex) const
{
    vector3 p;
    //
    // Implement your own stuff
    // 

    int idOfNode = mEdgesPool[mActiveEdges[edgeIndex]].nodeID[nodeIndex];
    p = mNodesPool[idOfNode].p;

    return p;
}

void GRAPH_SYSTEM::stopAutoNodeDeletion()
{
    mFlgAutoNodeDeletion = false;
}

//
// For every frame, update( ) function is called.
// 
//
void GRAPH_SYSTEM::update()
{
    if (!mFlgAutoNodeDeletion) {

        return;
    }
    mSelectedNode = 0;
    mPassiveSelectedNode = 0;

    Sleep(250);
    //
    //
    // Implement your own stuff
    // 
    if (mActiveNodes.size() == 0) {
        stopAutoNodeDeletion();
        return;
    }

    deleteNode(mActiveNodes[0]);

}