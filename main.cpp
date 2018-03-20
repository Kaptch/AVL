#include <iostream>
#include "tree.h"
#include <string>

int main() {

    AVL_tree<int> testTree = AVL_tree<int>();
    auto testIt1 = testTree.insert(5);
    auto testIt2 = testTree.insert(6);
    auto testIt3 = testTree.insert(7);
    auto testIt4 = testTree.insert(4);
    return 0;
}