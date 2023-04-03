#include <iostream>
#include <fstream>
#include <string>
#include "BST.h"
#include "Node.h"

using namespace std;

int main() {
    /*  Do not modify the content in "int main ()". */

    int file_number = 2;
    int index = 1;

    // If you want to just test2.txt
    // You can set file_number = 1, index = 2

    while (file_number--) {
        fstream file;
        string filename = "test" + to_string(index) + ".txt";
        cout << filename << endl;
        file.open(filename, ios::in);
        int cmd_num;
        file >> cmd_num;
        BST bst;
        while (cmd_num--) {
            string cmd;
            int value;
            file >> cmd;
            if (cmd == "ins") {
                int NodeValue;
                file >> NodeValue;
                bst.insert(new Node(NodeValue));
            }
            else if (cmd == "ino") {
                cout << "Inorder_traversal: ";
                bst.InOrder_traversal(bst.getRoot());
                cout << endl;
            }
            else if (cmd == "pre") {
                cout << "Preorder_traversal: ";
                bst.PreOrder_traversal(bst.getRoot());
                cout << endl;
            }
            else if (cmd == "pos") {
                cout << "Postorder_traversal: ";
                bst.PostOrder_traversal(bst.getRoot());
                cout << endl;
            }
            else if (cmd == "lev") {
                cout << "Levelorder_traversal: ";
                bst.LevelOrder_traversal(bst.getRoot());
                cout << endl;
            }
            else if (cmd == "hei") {
                cout << "Tree's height is : " << bst.ComputeHeight(bst.getRoot());
                cout << endl;
            }
            else break;

        }
        index++;
        file.close();
    }

    system("pause");
    return 0;

}