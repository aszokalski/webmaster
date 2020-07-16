//
// Created by Adam Szokalski on 20/11/2019.
//

#include "source/source.h"


source::Source::Source() {
    raw = {END_OF_TEXT};
    i = 0;
}

source::Source::Source(std::string s) {
    if(s.size() == 0){
        raw = {END_OF_TEXT};
    } else{
        raw = std::move(s) + END_OF_TEXT;
    }
    i = 0;
}

int source::Source::pos() {
    return i;
}

char source::Source::curr() {
    return raw[i];
}

char source::Source::peek() {
    if(auto ch = curr(); ch == END_OF_TEXT) {
        return ch;
    }

    return raw[i+1];
}

void source::Source::bump() {
    if( i < (raw.size() - 1)){
        ++i;
    }
}

void source::Source::pos(int p) {
    i = p;
}

std::string source::Source::getRaw() {
    return raw;
}
