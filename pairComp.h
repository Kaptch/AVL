//
// Created by kaptch on 3/22/18.
//

#ifndef TREE1_PAIRCOMP_H
#define TREE1_PAIRCOMP_H

struct compareStr {
    bool operator()(const std::string &a, const std::string &b) {
        return (a.compare(b)) < 0;
    }
};

struct compareEnc {
    bool operator()(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) {
        return (a.second < b.second);
    }
};

struct compareAnagrams {
    bool operator()(const std::pair<std::string, std::vector<std::string>> &a,
                    const std::pair<std::string, std::vector<std::string>> &b) {
        return (a.second.size() < b.second.size());
    }
};

struct compareDevs {
    bool operator()(const std::pair<std::string, double> &a, const std::pair<std::string, double> &b) {
        return (a.second < b.second);
    }
};

#endif //TREE1_PAIRCOMP_H
