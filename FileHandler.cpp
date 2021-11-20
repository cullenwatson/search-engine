#include "FileHandler.h"
void FileHandler::updateIndex(const string&file){
    // parses doc
    doc.changeFile(file);

    i.addDoc(file,doc.getText());
}
void FileHandler::output(){
    i.output();
}
void FileHandler::queryTree(const string& word){

    q.changeWord(word);
    string query = q.getWord();
    i.getDocsFromTree(query);
}
