#ifndef INC_21F_SRCH_NGN_CULLENW_INDEXENTRY_H
#define INC_21F_SRCH_NGN_CULLENW_INDEXENTRY_H

#include <utility>
#include<vector>
#include <iostream>
#include<set>
using namespace std;

class IndexEntry{
private:
    class Doc{
    public:
        string DocName;
        int Quantity;

        // constructor
        Doc(string doc): DocName(std::move(doc)), Quantity(1){}
        void increase(){ Quantity++;}

        bool operator== (const string& s) const{
            return DocName == s;
        }
    };
    string Word;
    vector<Doc> DocNames;
public:
    // constructors
    IndexEntry(string word, const string& docName): Word(std::move(word)){
        Doc temp(docName);
        DocNames.push_back(temp);
    }
    // constructor ONLY for operator==
    IndexEntry(string word): Word(std::move(word)){}

    // add doc to DocNames if word exists
    void addDocToIdxEntry(const string&);

    // operators to be able to add to tree
    bool operator< (const IndexEntry& s) const;
    bool operator> (const IndexEntry& s) const;
    bool operator== (const IndexEntry& s) const;

    friend std::ostream& operator<< (std::ostream&os, const IndexEntry&s){
        os << s.Word<<endl;
        for(const auto & docName : s.DocNames){
            os<<"     "<<docName.DocName<<" ("<<docName.Quantity<<") "<<endl;
        }
        return os;
    }
};


#endif //INC_21F_SRCH_NGN_CULLENW_INDEXENTRY_H
