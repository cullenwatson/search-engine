#include <fstream>
#include "DocumentParser.h"

void DocumentParser::changeFile(string c){
    FileName = c;
    parseDoc();
}
void DocumentParser::parseDoc(){
    // read in file
    ifstream f(FileName);

    // get all the text from file
    char text[1000000];
    f.getline(text,1000000);

    // parse text
    d.Parse(text);

}
string DocumentParser::getText(){
    return d["text"].GetString();
}
string DocumentParser::getFileName(){
    return FileName;
}

