//
// Created by fali on 02/08/2021.
//

#include "Combinations.h"
#include <cmath>
#include <cstring>

using namespace std;

Combinations::Combinations(int len, string charset, int init_index) {
    this->charset = charset;
    this->len = len;
    this->init_index = init_index;

    num_chars = charset.size();
    actual_char_count = new int[num_chars];
    current_combination = new int[len];
    iter = 0;
}

Combinations::~Combinations() {
    delete this->actual_char_count;
    delete this->current_combination;
}

void Combinations::init() {
    iter = 1;
    for (int i = 0; i < len; i++) {
        current_combination[i] = init_index;
    }
}

string Combinations::current_to_string() {
    string result;
    result.reserve(len);
    for (int i = 0; i < len; i++) {
        result += charset[current_combination[i]];
    }
    return result;
}

string Combinations::next() {
    if (iter == 0) {
        init();
        return current_to_string();
    }
    bool there_is_carriage;
    int current_pos = 0;

    do {
        if (current_combination[current_pos] == num_chars - 1) {
            current_combination[current_pos] = 0;
            current_pos++;
            there_is_carriage = true;
        } else {
            current_combination[current_pos]++;
            there_is_carriage = false;
        }
    } while (there_is_carriage && current_pos < len);

    iter++;

    return current_to_string();
}

bool Combinations::hasNext() {
    return iter < powl(num_chars, len);
}

