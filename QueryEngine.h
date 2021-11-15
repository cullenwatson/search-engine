

#ifndef INC_21F_SRCH_NGN_CULLENW_QUERYENGINE_H
#define INC_21F_SRCH_NGN_CULLENW_QUERYENGINE_H

#include<iostream>
#include "porter2_stemmer.h"
using namespace std;

class QueryEngine {
    string Word;
    // stem word after setting new word
    void stemWord();
public:
    // set word to query
    void changeWord(const string&);
    // get word to find in tree
    string getWord(){return Word;}

};


#endif //INC_21F_SRCH_NGN_CULLENW_QUERYENGINE_H
