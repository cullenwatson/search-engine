#include <fstream>
#include "DocumentParser.h"

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

