#ifndef INC_21F_SRCH_NGN_CULLENW_INDEXHANDLER_H
#define INC_21F_SRCH_NGN_CULLENW_INDEXHANDLER_H

#include "Tree.h"
#include"IndexEntry.h"
#include <vector>

class IndexHandler {
private:
    Tree<IndexEntry> TreeIndex;

public:
    // add words to tree
    void addDoc(const string&, const string&);
    //output
    void output();
    // find in tree
    void getDocsFromTree(const string&);
};

#endif //INC_21F_SRCH_NGN_CULLENW_INDEXHANDLER_H
