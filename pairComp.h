//
// Created by kaptch on 3/22/18.
//

#ifndef TREE1_PAIRCOMP_H
#define TREE1_PAIRCOMP_H

typedef std::pair<std::string, int> pair_t;

struct comparePair1 {
    bool operator()(const pair_t &a, const pair_t &b) {
        return (a.first.compare(b.first)) < 0;
    }
};

struct comparePair2 {
    bool operator()(const pair_t &a, const pair_t &b) {
        return (a.second < b.second);
    }
};

#endif //TREE1_PAIRCOMP_H
