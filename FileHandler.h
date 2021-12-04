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


    // get results from tree
    void queryTreeWords(const string&, int count, const int&);
    void queryTreeNotWords(const string&);
    void queryHashPersons(const string&);
    void queryHashOrgs(const string&);


    // output resulting set
    void outputResults();
    void getTop50Words();

    int getNumWords(){ return i.getNumWords();};
    int getTreeSize(){return i.getTreeSize();};
    int getNumUniquePersons(){return i.getUniquePersons();};
    int getNumUniqueOrgs(){return i.getUniqueOrgs();};
};



#endif //INC_21F_SRCH_NGN_CULLENW_FILEHANDLER_H
