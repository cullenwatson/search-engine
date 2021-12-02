#include "FileHandler.h"
void FileHandler::updateIndex(const string&file){
    // parses doc
    doc.changeFile(file);


    i.addDoc(file,doc.getText());

    // add persons
    i.addPersons(file,doc.getPersons());
    // add orgs
    i.addOrgs(file,doc.getOrgs());

}
void FileHandler::output(){
    i.output();
}
void FileHandler::queryTree(const string& word){

    // update word
    q.changeWord(word);
    string query = q.getWord();

    // get docs
    i.getDocsFromTree(query);
}
void FileHandler::queryHashPersons(const string&person){
    i.getDocsFromHashPerson(person);
}
void FileHandler::queryHashOrgs(const string&person){
    i.getDocsFromHashOrgs(person);
}
