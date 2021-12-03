#ifndef INC_21F_SRCH_NGN_CULLENW_DOCUMENTPARSER_H
#define INC_21F_SRCH_NGN_CULLENW_DOCUMENTPARSER_H

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include<vector>
#include<list>
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
    string getTextBlurb();

    // get file
    string getTitle();
    string getPublishDate();
    string getSite();


    // change file
    void changeFile(string);

    // get list of persons/orgs
    list<string> getPersons();
    list<string> getOrgs();


};

#endif //INC_21F_SRCH_NGN_CULLENW_DOCUMENTPARSER_H
