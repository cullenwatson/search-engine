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

    set<string> intersect;
public:
    // add file to update tree
    void updateIndex(const string&);
    // output tree
    void output();


    // get results from tree
    void queryTreeWords(const string&, int count, const int&);
    void queryTreeNotWords(const string&);
    void queryHashPersons(const string&);
    void queryHashOrgs(const string&);

    // intersect
    void outputIntersect();

    // todo not query (set diff)
    void outputResults();
    // to do OR queries, union
    // to do AND queries, intersection

};



#endif //INC_21F_SRCH_NGN_CULLENW_FILEHANDLER_H
