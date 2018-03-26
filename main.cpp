#include <iostream>
#include <chrono>
#include <random>
#include <set>
#include <sstream>
#include <map>
#include <locale>
#include <iterator>
#include <algorithm>

#include "AVL.h"
#include "csv.h"

#define SHOW(x) std::cout << # x " = " << x << '\n'

using namespace std::chrono;

int main() {

    //Correctness tests
    /*
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
    testTree.insert(10);
    testTree.erase(9);

    std::cout << *testTree.upper_bound(5) << std::endl;
    std::cout << *testTree.lower_bound(5) << std::endl;

    std::for_each(testTree.begin(), testTree.end(), [](int i) { std::cout << i << " ";});
    std::cout << std::endl;

    std::ofstream myfile;

    std::cout << std::endl;
    testTree.printTree();
    std::cout << std::endl;
    testTree.write("test.txt");
    AVL_tree<int> testTree1 = AVL_tree<int>();
    testTree1.read("test.txt");
    testTree1.printTree();

    std::cout << std::endl;
    */

    //Speed tests
    /*
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 10000);

    int Elems = 1000;

    std::vector<int> testVals;
    for (int i = 0; i < Elems; ++i)
        testVals.push_back(dist(rng));

    std::vector<AVL_tree<int>::iterator> testFind1;
    AVL_tree<int> testPerfomance = AVL_tree<int>();
    auto start1 = std::chrono::steady_clock::now();
    std::for_each(testVals.begin(), testVals.end(), [&testPerfomance](int i) { testPerfomance.insert(i); });
    //testPerfomance.printTree();
    //std::cout << testPerfomance.rootBalance();
    for (int i = 0; i < Elems; ++i) {
        testFind1.push_back(testPerfomance.find(testVals[i]));
        testPerfomance.erase(testVals[i]);
    }
    auto end1 = std::chrono::steady_clock::now();

    std::vector<std::set<int>::const_iterator> testFind2;
    std::set<int> testPerfomanceSet;
    auto start2 = std::chrono::steady_clock::now();
    std::for_each(testVals.begin(), testVals.end(), [&testPerfomanceSet](int i) { testPerfomanceSet.insert(i); });
    for (int i = 0; i < Elems; ++i) {
        testFind2.push_back(testPerfomanceSet.find(testVals[i]));
        testPerfomanceSet.erase(testVals[i]);
    }
    auto end2 = std::chrono::steady_clock::now();

    std::cout << "AVL: " << duration_cast<duration<double>>(end1 - start1).count() << std::endl;
    std::cout << "Set: " << duration_cast<duration<double>>(end2 - start2).count() << std::endl;
    */

    //---------------------------------------------------------//

    // TASK 1
    /*
    std::map<std::string, int, compareStr> words;
    std::string word;
    std::ifstream lotr;
    lotr.open("LOTR.txt");
    lotr >> word;
    while (lotr >> word) {
        auto it = words.find(word);
        if (it != words.end())
            ++words[word];
        else
            words.emplace(word, 1);
    }

    priority_queue_f<std::pair<std::string, int>, std::vector<std::pair<std::string, int>>, compareEnc> prQ(40);
    std::for_each(words.begin(), words.end(), [&prQ] (auto p) { prQ.push(p); });
    while (prQ.size() > 0) {
        auto temp = prQ.top();
        std::cout << temp.first << " : " << temp.second << std::endl;
        prQ.pop();
    }
    */

    //TASK 2
    /*
    std::locale loc;
    std::map<std::string, int, compareStr> words;
    std::string word;
    std::ifstream lotr;
    lotr.open("LOTR.txt");
    lotr >> word;
    while (lotr >> word) {
        if (!std::isupper(word[0],loc))
            continue;
        auto it = words.find(word);
        if (it != words.end())
            ++words[word];
        else
            words.emplace(word, 1);
    }

    priority_queue_f<std::pair<std::string, int>, std::vector<std::pair<std::string, int>>, compareEnc> prQ(20);
    std::for_each(words.begin(), words.end(), [&prQ] (auto p) { prQ.push(p); });
    while (prQ.size() > 0) {
        auto temp = prQ.top();
        std::cout << temp.first << " : " << temp.second << std::endl;
        prQ.pop();
    }
    */

    //TASK 3
    /*
    std::map<std::string, std::vector<std::string>, compareStr> words;
    std::string word;
    std::ifstream lotr;
    std::locale loc;
    lotr.open("LOTR.txt");
    lotr >> word;
    while (lotr >> word) {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        auto tmpWord = word;
        std::sort(tmpWord.begin(), tmpWord.end());
        //std::cout << tmpWord << " | " << word << " ";
        auto it = words.find(tmpWord);
        if (it != words.end()) {
            if (std::find((*it).second.begin(), (*it).second.end(), word) == (*it).second.end()) {
                (*it).second.push_back(word);
                //std::cout << word << " ";
            }
        }
        else {
                words.emplace(tmpWord, std::vector<std::string>(1, word));
                //std::cout << word << " ";
            }
    }

    priority_queue_f<std::pair<std::string, std::vector<std::string>>,
            std::vector<std::pair<std::string, std::vector<std::string>>>, compareAnagrams> prQ(2);
    std::for_each(words.begin(), words.end(), [&prQ] (auto p) { prQ.push(p); });
    while (prQ.size() > 0) {
        auto temp = prQ.top();
        std::copy(temp.second.begin(), temp.second.end(), std::ostream_iterator<std::string>(std::cout, ", "));
        std::cout << std::endl;
        prQ.pop();
    }
    */

    //TASK 4
    // \"([^\"\,]*)\,\s([^\"\,]*)\"
    // $1 & $2
    /*
    std::map<std::string, std::map<std::string, double>> salesByPublisher;
    io::CSVReader<16> in("Video_Games.csv");
    //Name,Platform,Year_of_Release,Genre,Publisher,NA_Sales,EU_Sales,JP_Sales,Other_Sales,Global_Sales,Critic_Score,Critic_Count,User_Score,User_Count,Developer,Rating
    in.read_header(io::ignore_missing_column, "Name", "Platform", "Year_of_Release", "Genre", "Publisher", "NA_Sales", "EU_Sales", "JP_Sales",
                    "Other_Sales", "Global_Sales", "Critic_Score", "Critic_Count", "User_Score", "User_Count", "Developer", "Rating");
    std::string Name, Platform, Year_of_Release, Genre, Publisher, Developer, Rating = "N/A";
    double NA_Sales, EU_Sales, JP_Sales, Other_Sales, Global_Sales, User_Score = 0;
    int Critic_Score, Critic_Count, User_Count = 0;
    while(in.read_row(Name, Platform, Year_of_Release, Genre, Publisher, NA_Sales, EU_Sales, JP_Sales, Other_Sales, Global_Sales, Critic_Score, Critic_Count, User_Score, User_Count, Developer, Rating)){
        auto it1 = salesByPublisher.find(Publisher);
        if (it1 != salesByPublisher.end()) {
            auto it2 = (*it1).second.find(Genre);
            if (it2 != (*it1).second.end())
                salesByPublisher[Publisher][Genre] += Global_Sales;
            else
                salesByPublisher[Publisher].emplace(Genre, Global_Sales);
        }
        else {
            salesByPublisher.emplace(Publisher, std::map<std::string, double>({{Genre, Global_Sales}}));
        }
    }

    std::for_each(salesByPublisher.begin(), salesByPublisher.end(), [](auto p) {
        std::cout << p.first << std::endl; std::for_each(p.second.begin(), p.second.end(), [] (auto t) {
            std::cout << "---" << t.first << ": " << t.second << std::endl; });});
    */

    //TASK 5
    /*
    std::map<std::string, std::map<std::string, double>> salesByYear;
    io::CSVReader<16> in("Video_Games.csv");
    //Name,Platform,Year_of_Release,Genre,Publisher,NA_Sales,EU_Sales,JP_Sales,Other_Sales,Global_Sales,Critic_Score,Critic_Count,User_Score,User_Count,Developer,Rating
    in.read_header(io::ignore_missing_column, "Name", "Platform", "Year_of_Release", "Genre", "Publisher", "NA_Sales", "EU_Sales", "JP_Sales",
                   "Other_Sales", "Global_Sales", "Critic_Score", "Critic_Count", "User_Score", "User_Count", "Developer", "Rating");
    std::string Name, Platform, Year_of_Release, Genre, Publisher, Developer, Rating = "N/A";
    double NA_Sales, EU_Sales, JP_Sales, Other_Sales, Global_Sales, User_Score = 0;
    int Critic_Score, Critic_Count, User_Count = 0;
    while(in.read_row(Name, Platform, Year_of_Release, Genre, Publisher, NA_Sales, EU_Sales, JP_Sales, Other_Sales, Global_Sales, Critic_Score, Critic_Count, User_Score, User_Count, Developer, Rating)){
        auto it1 = salesByYear.find(Year_of_Release);
        if (it1 != salesByYear.end()) {
            auto it2 = (*it1).second.find(Genre);
            if (it2 != (*it1).second.end())
                salesByYear[Year_of_Release][Genre] += Global_Sales;
            else
                salesByYear[Year_of_Release].emplace(Genre, Global_Sales);
        }
        else {
            salesByYear.emplace(Year_of_Release, std::map<std::string, double>({{Genre, Global_Sales}}));
        }
    }


    std::for_each(salesByYear.begin(), salesByYear.end(), [](auto p) { std::cout << p.first << std::endl;
                                                                       auto t = p.second.begin();
                                                                       for (auto it = p.second.begin(); it != p.second.end(); ++it)
                                                                              if ((*it).second > (*t).second)
                                                                                  t = it;
                                                                       std::cout << "---" << (*t).first << ": " << (*t).second << std::endl; });
    */

    //TASK 6
    /*
    std::map<std::string, std::map<std::string, double>> salesByPublisher;
    io::CSVReader<16> in("Video_Games.csv");
    //Name,Platform,Year_of_Release,Genre,Publisher,NA_Sales,EU_Sales,JP_Sales,Other_Sales,Global_Sales,Critic_Score,Critic_Count,User_Score,User_Count,Developer,Rating
    in.read_header(io::ignore_missing_column, "Name", "Platform", "Year_of_Release", "Genre", "Publisher", "NA_Sales", "EU_Sales", "JP_Sales",
                   "Other_Sales", "Global_Sales", "Critic_Score", "Critic_Count", "User_Score", "User_Count", "Developer", "Rating");
    std::string Name, Platform, Year_of_Release, Genre, Publisher, Developer, Rating = "N/A";
    double NA_Sales, EU_Sales, JP_Sales, Other_Sales, Global_Sales, User_Score = 0;
    int Critic_Score, Critic_Count, User_Count = 0;
    while(in.read_row(Name, Platform, Year_of_Release, Genre, Publisher, NA_Sales, EU_Sales, JP_Sales, Other_Sales, Global_Sales, Critic_Score, Critic_Count, User_Score, User_Count, Developer, Rating)){
        auto it1 = salesByPublisher.find(Publisher);
        if (it1 != salesByPublisher.end()) {
            auto it2 = (*it1).second.find(Developer);
            if (it2 != (*it1).second.end())
                salesByPublisher[Publisher][Developer] += Global_Sales;
            else
                salesByPublisher[Publisher].emplace(Developer, Global_Sales);
        }
        else {
            salesByPublisher.emplace(Publisher, std::map<std::string, double>({{Developer, Global_Sales}}));
        }
    }

    priority_queue_f<std::pair<std::string, double>, std::vector<std::pair<std::string, double>>, compareDevs> q(5);
    std::for_each(salesByPublisher.begin(), salesByPublisher.end(), [&q](auto p) {
        std::cout << p.first << std::endl;
        std::for_each(p.second.begin(), p.second.end(), [&q] (auto u) {
            q.push(u);
        });
        while (q.size() > 0) {
            auto y = q.top();
            std::cout << "---" << y.first << " : " << y.second << std::endl;
            q.pop();
        }
    });
    */
    return 0;
}