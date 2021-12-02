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
    wordSet = i.getDocsFromTree(query);
}
void FileHandler::queryHashPersons(const string&person){
    persons = i.getDocsFromHashPerson(person);
}
void FileHandler::queryHashOrgs(const string&person){
    orgs = i.getDocsFromHashOrgs(person);
}
void FileHandler::intersectSets(){
    if(persons!=nullptr && orgs!=nullptr && wordSet!=nullptr){
        set<string> temp;
        // intersect first 2 sets
        set_intersection(persons->begin(),persons->end(),orgs->begin(),orgs->end(),inserter(temp,temp.begin()));
        // intersect last set
        set_intersection(temp.begin(),temp.end(),wordSet->begin(),wordSet->end(),inserter(intersect,intersect.begin()));

    }

}
void FileHandler::outputIntersect(){
    cout<<"INTERSECTION\n";
    if(intersect.size()==0)
        cout<<"No results found\n";
    else{
        for(const auto& e: intersect){
            cout<<"     "<<e<<endl;
        }
    }

}