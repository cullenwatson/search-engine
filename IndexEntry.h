#ifndef INC_21F_SRCH_NGN_CULLENW_INDEXENTRY_H
#define INC_21F_SRCH_NGN_CULLENW_INDEXENTRY_H

#include <utility>
#include<vector>
#include <iostream>
#include<unordered_map>
using namespace std;

class IndexEntry{
private:

    string Word;
    unordered_map<string,int> DocNames;
public:
    // constructors
    IndexEntry(string word, const string& docName): Word(std::move(word)){
        DocNames[docName]=1;

    }
    // constructor ONLY for operator==
    explicit IndexEntry(string word): Word(std::move(word)){}

    // add doc to DocNames if word exists
    void addDocToIdxEntry(const string&);

    // operators to be able to add to tree
    bool operator< (const IndexEntry& s) const;
    bool operator> (const IndexEntry& s) const;
    bool operator== (const IndexEntry& s) const;

    friend std::ostream& operator<< (std::ostream&os, const IndexEntry&s){
        os << s.Word<<endl;
        for(const auto & docName : s.DocNames){
            os<<"     "<<docName.first<<" ("<<docName.second<<") "<<endl;
        }
        return os;
    }
};


#endif //INC_21F_SRCH_NGN_CULLENW_INDEXENTRY_H
