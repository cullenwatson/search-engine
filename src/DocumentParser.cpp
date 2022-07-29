#include <fstream>
#include<iostream>
#include "DocumentParser.h"
#include <sstream>
#include <algorithm>
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
string DocumentParser::getTextBlurb(){
    string temp = d["text"].GetString();
    string temp2, blurb;

    stringstream ss(temp);

    getline(ss,temp2,' ');
    blurb+=temp2;

    int i=0;
    while(getline(ss,temp2,' ')){
        // get 30 words
        temp2.erase(std::remove(temp2.begin(), temp2.end(), '\n'), temp2.end());
        if(i>32)
            break;
        if(i==16){
            blurb+="\n"+temp2;
            i++;
            continue;

        }
        blurb+=" "+temp2;
        i++;
    }
    return blurb+"...";
}
string DocumentParser::getTitle(){
    return d["title"].GetString();
}
string DocumentParser::getPublishDate(){
    return d["published"].GetString();
}
string DocumentParser::getSite(){
    return d["url"].GetString();
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


