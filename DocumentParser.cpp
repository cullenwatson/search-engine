#include <fstream>
#include<iostream>
#include "DocumentParser.h"
using namespace std;

void DocumentParser::changeFile(string c){
    FileName = c;
    parseDoc();
}
void DocumentParser::parseDoc(){
    // read in file
    ifstream f(FileName);

    // wrap istream
    rapidjson::IStreamWrapper wrap(f);

    // get all the text from file
    char text[1000000];
    d.ParseStream(wrap);

}
string DocumentParser::getText(){
    return d["text"].GetString();
}
string DocumentParser::getFileName(){
    return FileName;
}
list<string> DocumentParser::getPersons(){
    list<string> persons;
    for (rapidjson::Value::ConstValueIterator itr = d["entities"].GetObject()["persons"].Begin(); itr != d["entities"].GetObject()["persons"].End(); ++itr){
        persons.emplace_back(itr->GetObject()["name"].GetString());
    }

   return persons;
}
list<string> DocumentParser::getOrgs(){
    list<string> orgs;
    for (rapidjson::Value::ConstValueIterator itr = d["entities"].GetObject()["organizations"].Begin(); itr != d["entities"].GetObject()["organizations"].End(); ++itr){
        orgs.emplace_back(itr->GetObject()["name"].GetString());
    }

    return orgs;
}


