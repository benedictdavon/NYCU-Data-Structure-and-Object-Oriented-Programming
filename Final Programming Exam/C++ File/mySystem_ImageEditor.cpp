//
// Prof. Sai-Keung WONG
// Email:	cswingo@nycu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2022/04/25
//
#include <iostream>
#include "mySystem_ImageEditor.h"

#define IMAGE_FILE_NAME "3d-flower-desktop.jpg"

#define IMAGE_MAX_HIERARCHY_DEPTH 8

using namespace std;

void drawDisk_TriangleFan(double x, double y, double r, int in_numSamples = 120)
{
    int numSamples = in_numSamples;
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x, 0.0, y);
    for (int i = 0; i < numSamples; ++i) {
        double da = 1.0 / (double)(numSamples - 1) * 3.141592654 * 2.0;

        double a = i * da;
        double x0 = x + r * cos(a);
        double y0 = y + r * sin(a);
        double x1 = x + r * cos(a + da);
        double y1 = y + r * sin(a + da);
        //glVertex3f( x, 0.0, y );


        glVertex3f(x0, 0.0, y0);

        //glVertex3f( x1, 0.0, y1 );


    }
    glEnd();
}

IMAGE_SYSTEM::IMAGE_SYSTEM()
{
    m_ImageHierarchy = 0;
    m_Image = new ns_opengl::Image;
    m_Image->readFile(IMAGE_FILE_NAME);

    int wImage, hImage;
    m_Image->getInfo(wImage, hImage);

    int cur_depth = 0;
    int start_x = 0;
    int start_y = 0;

    int w = wImage;
    int h = hImage;
    float sx = 2;
    float sy = 2;

    float radius = wImage / 2.0 * (sx + sy) * 0.5;

    m_ImageHierarchy = new IMAGE_NODE(
        cur_depth,
        start_x,
        start_y,
        w,
        h,
        sx,
        sy,
        radius
    );
    float r, g, b;
    computeAverageColor(start_x, start_y, w, h, r, g, b);

    m_ImageHierarchy->setColor(r, g, b);
    m_ImageHierarchy->computeDrawPosition(
        wImage, hImage
    );
    //
}


void IMAGE_SYSTEM::reset()
{
    m_ImageHierarchy->flg_explored = false;
}

void IMAGE_SYSTEM::handleKeyPressedEvent(unsigned char key)
{
    switch (key) {
    case ' ':
        break;
    case '.':
    case '<':
        break;
    case ',':
    case '>':
        break;
    case 'r':
        reset();
        break;
    case 'k':
    case 'K':
        break;
    case 'l':
    case 'L':
        break;
    case '6':
        explore_full();
        break;
    case '7':
        explore_left();
        break;
    case '8':
        explore_left();
        break;
    case '9':
        explore_lv();
        break;
    case '0':
        explore_temple();
        break;
    }
}

//
// Compute the node color.
// That is compute the average color of the block of the node
//
void IMAGE_SYSTEM::computeNodeColor(IMAGE_NODE* node)
{
    float r, g, b;
    computeAverageColor(node->start_x,
        node->start_y,
        node->w,
        node->h,
        r, g, b);
    node->setColor(r, g, b);
}



//
// Explore a node if it is not explored.
// Go down the children if the node is explored.
//
void IMAGE_SYSTEM::exploreImageNode(IMAGE_NODE* node, double x, double y)
{
    if (!node) return;
    if (node->flg_explored) {
        // If the node has been explored, 
        // go to check its children
        for (int i = 0; i < 4; i++) {
            // Recursive function
            exploreImageNode(node->children[i], x, y);
        }
        return;
    }
    else {
        // The node is not explored yet.
        // Now, explore it.
        // Do the following steps:
        // Can we explore it? 
        // If the dimension is less than 1x1, return.
        // If the dimension is at least 2x2
        //
        // Divide the image block into four children
        // Compute the draw positions of each child.
        //


        if (node->w / 2 == 0 || node->h / 2 == 0) return;

        float dx = x - node->draw_x;
        float dy = y - node->draw_y;
        float d2 = dx * dx + dy * dy;
        float r2 = node->radius * node->radius;
        if (d2 > r2) return; //out of range

        node->flg_explored = true;

        int wImage, hImage;
        m_Image->getInfo(wImage, hImage);
        IMAGE_NODE* children[4];
        float radius = node->w / 2.0;
        // Example ( can be real )
        // Compute one child

        // compute children
        node->children[0] = new IMAGE_NODE
        (node->cur_depth + 1,
            node->start_x, node->start_y, //
            node->w / 2, node->h / 2,
            node->sx, node->sy,
            node->radius / 2);

        node->children[1] = new IMAGE_NODE
        (node->cur_depth + 1,
            node->start_x + node->w / 2, node->start_y, //
            node->w / 2, node->h / 2,
            node->sx, node->sy,
            node->radius / 2);

        node->children[2] = new IMAGE_NODE
        (node->cur_depth + 1,
            node->start_x, node->start_y + node->h / 2, //
            node->w / 2, node->h / 2,
            node->sx, node->sy,
            node->radius / 2);

        node->children[3] = new IMAGE_NODE
        (node->cur_depth + 1,
            node->start_x + node->w / 2, node->start_y + node->h / 2, //
            node->w / 2, node->h / 2,
            node->sx, node->sy,
            node->radius / 2);

        for (int i = 0; i < 4; i++) {
            int wImage, hImage;
            computeNodeColor(node->children[i]);
            m_Image->getInfo(wImage, hImage);
            node->children[i]->computeDrawPosition(wImage, hImage);
        }
    }

}

//
// call exploreImageNode(root, mouse_x, mouse_y)
//
void IMAGE_SYSTEM::handlePassiveMouseEvent(double x, double y)
{
    std::cout << "IMAGE_SYSTEM Mouse:" << x << "\t" << y << std::endl;
    exploreImageNode(m_ImageHierarchy, x, y);
}


void IMAGE_SYSTEM::explore_full() { 	// entry point
    explore_full(m_ImageHierarchy);	// pass the root node
}

void IMAGE_SYSTEM::explore_full(IMAGE_NODE* node) {
    if (!node) return;
    if (node->flg_explored) {
        for (int i = 0; i < 4; i++) {
            // Recursive function
            explore_full(node->children[i]);
        }
        return;
    }
    else {
        // set the node to be explored.
        if (node->w / 2 == 0 || node->h / 2 == 0) return;
        node->flg_explored = true;
        int wImage, hImage;
        m_Image->getInfo(wImage, hImage);
        IMAGE_NODE* children[4];
        float radius = node->w / 2.0;
        

        node->children[0] = new IMAGE_NODE
        (node->cur_depth + 1,
            node->start_x, node->start_y, //
            node->w / 2, node->h / 2,
            node->sx, node->sy,
            node->radius / 2);

        node->children[1] = new IMAGE_NODE
        (node->cur_depth + 1,
            node->start_x + node->w / 2, node->start_y, //
            node->w / 2, node->h / 2,
            node->sx, node->sy,
            node->radius / 2);

        node->children[2] = new IMAGE_NODE
        (node->cur_depth + 1,
            node->start_x, node->start_y + node->h / 2, //
            node->w / 2, node->h / 2,
            node->sx, node->sy,
            node->radius / 2);

        node->children[3] = new IMAGE_NODE
        (node->cur_depth + 1,
            node->start_x + node->w / 2, node->start_y + node->h / 2, //
            node->w / 2, node->h / 2,
            node->sx, node->sy,
            node->radius / 2);

        for (int i = 0; i < 4; i++) {
            int wImage, hImage;
            computeNodeColor(node->children[i]);
            m_Image->getInfo(wImage, hImage);
            node->children[i]->computeDrawPosition(wImage, hImage);
        }

        for (int i = 0; i < 4; i++) {
            explore_full(node->children[i]);
        }
    }
}

void IMAGE_SYSTEM::explore_left() {
    explore_left(m_ImageHierarchy);
}

void IMAGE_SYSTEM::explore_left(IMAGE_NODE* node){
    if (!node) return;
    if (node->flg_explored) {
        for (int i = 0; i < 4; i++) {
            // Recursive function
            explore_full(node->children[i]);
        }
        return;
    }
    else {
        if (node->w / 2 == 0 || node->h / 2 == 0) return;
        node->flg_explored = true;
        int wImage, hImage;
        m_Image->getInfo(wImage, hImage);
        IMAGE_NODE* children[4];
        float radius = node->w / 2.0;

        node->children[0] = new IMAGE_NODE
        (node->cur_depth + 1,
            node->start_x, node->start_y, //
            node->w / 2, node->h / 2,
            node->sx, node->sy,
            node->radius / 2);

        node->children[1] = new IMAGE_NODE
        (node->cur_depth + 1,
            node->start_x + node->w / 2, node->start_y, //
            node->w / 2, node->h / 2,
            node->sx, node->sy,
            node->radius / 2);

        node->children[2] = new IMAGE_NODE
        (node->cur_depth + 1,
            node->start_x, node->start_y + node->h / 2, //
            node->w / 2, node->h / 2,
            node->sx, node->sy,
            node->radius / 2);

        node->children[3] = new IMAGE_NODE
        (node->cur_depth + 1,
            node->start_x + node->w / 2, node->start_y + node->h / 2, //
            node->w / 2, node->h / 2,
            node->sx, node->sy,
            node->radius / 2);

        for (int i = 0; i < 4; i++) {
            int wImage, hImage;
            computeNodeColor(node->children[i]);
            m_Image->getInfo(wImage, hImage);
            node->children[i]->computeDrawPosition(wImage, hImage);
        }

        explore_full(node->children[0]);
        explore_full(node->children[2]);
    }
}

void IMAGE_SYSTEM::explore_right() {
    explore_left(m_ImageHierarchy);
}

void IMAGE_SYSTEM::explore_right(IMAGE_NODE* node) {
    if (!node) return;
    if (node->flg_explored) {
        for (int i = 0; i < 4; i++) {
            // Recursive function
            explore_full(node->children[i]);
        }
        return;
    }
    else {
        if (node->w / 2 == 0 || node->h / 2 == 0) return;
        node->flg_explored = true;
        int wImage, hImage;
        m_Image->getInfo(wImage, hImage);
        IMAGE_NODE* children[4];
        float radius = node->w / 2.0;

        node->children[0] = new IMAGE_NODE
        (node->cur_depth + 1,
            node->start_x, node->start_y, //
            node->w / 2, node->h / 2,
            node->sx, node->sy,
            node->radius / 2);

        node->children[1] = new IMAGE_NODE
        (node->cur_depth + 1,
            node->start_x + node->w / 2, node->start_y, //
            node->w / 2, node->h / 2,
            node->sx, node->sy,
            node->radius / 2);

        node->children[2] = new IMAGE_NODE
        (node->cur_depth + 1,
            node->start_x, node->start_y + node->h / 2, //
            node->w / 2, node->h / 2,
            node->sx, node->sy,
            node->radius / 2);

        node->children[3] = new IMAGE_NODE
        (node->cur_depth + 1,
            node->start_x + node->w / 2, node->start_y + node->h / 2, //
            node->w / 2, node->h / 2,
            node->sx, node->sy,
            node->radius / 2);

        for (int i = 0; i < 4; i++) {
            int wImage, hImage;
            computeNodeColor(node->children[i]);
            m_Image->getInfo(wImage, hImage);
            node->children[i]->computeDrawPosition(wImage, hImage);
        }

        explore_full(node->children[1]);
        explore_full(node->children[3]);
    }
}

void IMAGE_SYSTEM::explore_lv() {
    explore_lv(m_ImageHierarchy);
}

void IMAGE_SYSTEM::explore_lv(IMAGE_NODE* node) {
    if (!node) return;
    if (node->flg_explored) {
        for (int i = 0; i < 4; i++) {
            // Recursive function
            explore_full(node->children[i]);
        }
        return;
    }
    else {
        if (node->w / 2 == 0 || node->h / 2 == 0) return;
        if (node->cur_depth == 2) return;
        node->flg_explored = true;
        int wImage, hImage;
        m_Image->getInfo(wImage, hImage);
        IMAGE_NODE* children[4];
        float radius = node->w / 2.0;

        node->children[0] = new IMAGE_NODE
        (node->cur_depth + 1,
            node->start_x, node->start_y, //
            node->w / 2, node->h / 2,
            node->sx, node->sy,
            node->radius / 2);

        node->children[1] = new IMAGE_NODE
        (node->cur_depth + 1,
            node->start_x + node->w / 2, node->start_y, //
            node->w / 2, node->h / 2,
            node->sx, node->sy,
            node->radius / 2);

        node->children[2] = new IMAGE_NODE
        (node->cur_depth + 1,
            node->start_x, node->start_y + node->h / 2, //
            node->w / 2, node->h / 2,
            node->sx, node->sy,
            node->radius / 2);

        node->children[3] = new IMAGE_NODE
        (node->cur_depth + 1,
            node->start_x + node->w / 2, node->start_y + node->h / 2, //
            node->w / 2, node->h / 2,
            node->sx, node->sy,
            node->radius / 2);

        for (int i = 0; i < 4; i++) {
            int wImage, hImage;
            computeNodeColor(node->children[i]);
            m_Image->getInfo(wImage, hImage);
            node->children[i]->computeDrawPosition(wImage, hImage);
        }

        for (int i = 0; i < 4; i++){
            explore_lv(node->children[i]);
        }
    }
}

void IMAGE_SYSTEM::explore_temple() {
    explore_temple(m_ImageHierarchy);
}

void IMAGE_SYSTEM::explore_temple(IMAGE_NODE* node) {
    if (!node) return;
    if (node->flg_explored) {
        for (int i = 0; i < 4; i++) {
            // Recursive function
            explore_temple(node->children[i]);
        }
        return;
    }
    else {
        if (node->w / 2 == 0 || node->h / 2 == 0) return;
        if (node->cur_depth == 3) return;
        node->flg_explored = true;
        int wImage, hImage;
        m_Image->getInfo(wImage, hImage);
        IMAGE_NODE* children[4];
        float radius = node->w / 2.0;

        node->children[0] = new IMAGE_NODE
        (node->cur_depth + 1,
            node->start_x, node->start_y, //
            node->w / 2, node->h / 2,
            node->sx, node->sy,
            node->radius / 2);

        node->children[1] = new IMAGE_NODE
        (node->cur_depth + 1,
            node->start_x + node->w / 2, node->start_y, //
            node->w / 2, node->h / 2,
            node->sx, node->sy,
            node->radius / 2);

        node->children[2] = new IMAGE_NODE
        (node->cur_depth + 1,
            node->start_x, node->start_y + node->h / 2, //
            node->w / 2, node->h / 2,
            node->sx, node->sy,
            node->radius / 2);

        node->children[3] = new IMAGE_NODE
        (node->cur_depth + 1,
            node->start_x + node->w / 2, node->start_y + node->h / 2, //
            node->w / 2, node->h / 2,
            node->sx, node->sy,
            node->radius / 2);

        for (int i = 0; i < 4; i++) {
            int wImage, hImage;
            computeNodeColor(node->children[i]);
            m_Image->getInfo(wImage, hImage);
            node->children[i]->computeDrawPosition(wImage, hImage);
        }

        if (node->cur_depth == 1) {
            for (int i = 0; i < 4; i++) {
                if (node->children[i]->start_x >= 0 && node->children[i]->start_y <= 32)
                    explore_temple(node->children[i]);
                else if (node->children[i]->start_x >= 0 && node->children[i]->start_y > 64)
                    explore_temple(node->children[i]);
                /*
                else if (node->children[i]->start_x >= 0 && node->children[i]->start_y == 128-32)
                    explore_temple(node->children[i]);
                else if (node->children[i]->start_x == 32 && node->children[i]->start_y < 32)
                    explore_temple(node->children[i]);
                else if (node->children[i]->start_x > 128-32 && node->children[i]->start_y > 128-32)
                    explore_temple(node->children[i]);*/
            }
        }
        else {
            for (int i = 0; i < 4; i++) {
                explore_temple(node->children[i]);
            }
        }
    }
}