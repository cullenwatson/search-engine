#ifndef INC_21F_SRCH_NGN_CULLENW_FILEHANDLER_H
#define INC_21F_SRCH_NGN_CULLENW_FILEHANDLER_H

#include "IndexHandler.h"
#include "DocumentParser.h"

#include "Tree.h"
#include "DocumentParser.h"
#include"IndexHandler.h"
#include "QueryEngine.h"

class FileHandler {
    IndexHandler i;
    DocumentParser doc;
    QueryEngine q;
public:
    // add file to update tree
    void updateIndex(const string&);
    // output tree
    void output();
    // get results from tree
    void queryTree(const string&);

    // to do OR queries, do multiple query trees and unioning
    // to do AND queries, do multiple querry trees and intersection
    // to do NOT queries, do multiple querry trees and set difference

};



#endif //INC_21F_SRCH_NGN_CULLENW_FILEHANDLER_H
