//
// Created by kaptch on 3/26/18.
//

#ifndef TREE1_STRINGDATA_H
#define TREE1_STRINGDATA_H

#include <string>

class strData {
    std::string _str;
    int _i;
public:
    strData(const std::string &_s) : _str(_s), _i(1) {}

    strData &operator++() {
        ++_i;
        return *this;
    }

    const std::string &string() const { return _str; }

    int i() const { return _i; }
};

#endif //TREE1_STRINGDATA_H
