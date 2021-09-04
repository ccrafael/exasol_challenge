//
// Created by fali on 02/08/2021.
//

#ifndef EXASOL_COMBINATIONS_H
#define EXASOL_COMBINATIONS_H

#include <string>

using namespace std;

class Combinations {
private:
    string charset;
    int num_chars;
    int len;
    int * actual_char_count;
    int * current_combination;
    int init_index;

    unsigned long long iter;

    void init();
    string current_to_string();
    bool valid_combination();

public:
    Combinations(int len, string charset, int init_index);

    ~Combinations();

    string next();
    bool hasNext();


};
#endif //EXASOL_COMBINATIONS_H
