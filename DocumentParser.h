#ifndef INC_21F_SRCH_NGN_CULLENW_DOCUMENTPARSER_H
#define INC_21F_SRCH_NGN_CULLENW_DOCUMENTPARSER_H

#include "rapidjson/document.h"
using namespace std;

class DocumentParser {
private:
    string FileName;
    rapidjson::Document d;

    // run rapidjsn
    void parseDoc();
public:
    // get text
    string getText();

    // get file
    string getFileName();
    // change file
    void changeFile(string);
};

#endif //INC_21F_SRCH_NGN_CULLENW_DOCUMENTPARSER_H
