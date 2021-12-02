#ifndef INC_21F_SRCH_NGN_CULLENW_INDEXHANDLER_H
#define INC_21F_SRCH_NGN_CULLENW_INDEXHANDLER_H

#include "Tree.h"
#include"IndexEntry.h"
#include <vector>
#include "HashTable.h"
#include<list>
#include <set>
class IndexHandler {
private:
    Tree<IndexEntry> TreeIndex;
    HashTable<string, string> hashTablePersons;
    HashTable<string, string> hashTableOrgs;

public:
    // add words to tree
    void addDoc(const string&, const string&);

    //output
    void output();
    // find in tree


    // add persons
    void addPersons(const string&,list<string>);
    void addOrgs(const string&,list<string>);

    // get sets
    set<string>* getDocsFromTree(const string&);
    set<string>* getDocsFromHashPerson(const string&word);
    set<string>* getDocsFromHashOrgs(const string&word);
};

#endif //INC_21F_SRCH_NGN_CULLENW_INDEXHANDLER_H
