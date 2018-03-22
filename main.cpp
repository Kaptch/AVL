#include <iostream>
#include "AVL.h"
#include <chrono>
#include <random>
#include <set>
#include "pairComp.h"
#include <sstream>
#include "priority_queue.h"

using namespace std::chrono;

int main() {
/* ///Correctness tests
    AVL_tree<int> testTree = AVL_tree<int>();
    testTree.insert(5);
    testTree.insert(6);
    testTree.insert(7);
    testTree.insert(4);

    testTree.erase(4);
    testTree.erase(3);
    testTree.erase(3);
    testTree.insert(8);
    testTree.insert(8);
    testTree.insert(9);

    std::cout << *testTree.upper_bound(5) << std::endl;
    std::cout << *testTree.lower_bound(5) << std::endl;

    std::for_each(testTree.begin(), testTree.end(), [](int i) { std::cout << i << " ";});
    std::cout << std::endl;

    std::ofstream myfile;

    testTree.printTree();
    testTree.write("test.txt");
    AVL_tree<int> testTree1 = AVL_tree<int>();
    testTree1.read("test.txt");
    testTree1.printTree();

    std::cout << std::endl;
    */
/*
    //Speed tests
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 10000);

    std::vector<int> testVals;
    for (int i = 0; i < 10000; ++i)
        testVals.push_back(dist(rng));

    std::vector<AVL_tree<int>::iterator> testFind1;
    AVL_tree<int> testPerfomance = AVL_tree<int>();
    auto start1 = std::chrono::steady_clock::now();
    std::for_each(testVals.begin(), testVals.end(), [&testPerfomance](int i) { testPerfomance.insert(i); });
    for (int i = 0; i < 10000; ++i) {
        testFind1.push_back(testPerfomance.find(testVals[i]));
        testPerfomance.erase(testVals[i]);
    }
    auto end1 = std::chrono::steady_clock::now();

    std::vector<std::set<int>::const_iterator> testFind2;
    std::set<int> testPerfomanceSet;
    auto start2 = std::chrono::steady_clock::now();
    std::for_each(testVals.begin(), testVals.end(), [&testPerfomanceSet](int i) { testPerfomanceSet.insert(i); });
    for (int i = 0; i < 10000; ++i) {
        testFind2.push_back(testPerfomanceSet.find(testVals[i]));
        testPerfomanceSet.erase(testVals[i]);
    }
    auto end2 = std::chrono::steady_clock::now();

    std::cout << "AVL: " << duration_cast<duration<double>>(end1 - start1).count() << std::endl;
    std::cout << "Set: " << duration_cast<duration<double>>(end2 - start2).count() << std::endl;
*/

    std::set<std::pair<std::string, int>, comparePair1> words;
    std::string word;
    std::ifstream lotr;
    lotr.open("test.txt");
    while (lotr >> word) {
        //std::cout << word << std::endl;
        auto it = find_if(words.begin(), words.end(),
                          [&](const std::pair<std::string, int> &val) -> bool {
                              //std::cout << val.first << " ||| " << word << " ||| " << val.first == word;
                              return val.first.compare(word) == 0;
                          });
        if (it != words.end()) {
            //std::cout << (*it).first << std::endl;
            std::string str = (*it).first;
            int i = (*it).second;
            ++i;
            words.erase(it);
            words.insert(std::make_pair(str, i));
        } else
            words.insert(std::make_pair(word, 1));
    }

    priority_queue_f<std::pair<std::string, int>, std::vector<std::pair<std::string, int>>, comparePair2> prQ(40);
    std::for_each(words.begin(), words.end(), [&prQ](std::pair<std::string, int> p) { prQ.add(p); });
    while (prQ.size() > 0) {
        auto temp = prQ.max();
        std::cout << temp.first << " : " << temp.second << std::endl;
    }

    return 0;
}