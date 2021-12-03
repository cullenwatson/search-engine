#include "FileHandler.h"
void FileHandler::output(){
    i.output();
}
void FileHandler::updateIndex(const string&file){
    // parses doc
    doc.changeFile(file);


    i.addDoc(file,doc.getText());

    // add persons
    i.addPersons(file,doc.getPersons());
    // add orgs
    i.addOrgs(file,doc.getOrgs());

}
void FileHandler::queryTreeWords(const string& word, int count, const int& type){

    // update word
    q.changeWord(word);
    string query = q.getWord();

    // get docs for word
    set<string>* temp = i.getDocsFromTree(query);

    // check if this is the first word being searched
    if(count!=0){
        // check if set is empty
        if(temp==nullptr){
            // clear intersect if AND search
            if(type==1){
                intersect.clear();
            }
            return;
        }
        // AND
        if(type==1){
            // copy intersect set and clear to be able to form new intersect
            set<string> temp2 = intersect;
            intersect.clear();

            // get intersection of old and new set
            set_intersection(temp->begin(),temp->end(),temp2.begin(),
                             temp2.end(),inserter(intersect,intersect.begin()));
        } // OR
        else if(type==2){
            // insert all elements into main set
            for(const auto& e: *temp){
                intersect.insert(e);

            }
        }

    }
    // first word being searched
    else{
        // assign set to intersect
        if(temp!=nullptr){
            intersect = *temp;
        }
    }


}// todo clear sets to do multiple searchs and reset p/o/w
void FileHandler::queryTreeNotWords(const string& word) {

    // update word
    q.changeWord(word);
    string query = q.getWord();

    // get docs
    set<string> *temp = i.getDocsFromTree(query);

    // check if set is empty
    if (temp == nullptr) {
        return;
    } else {
        // copy intersect set and clear old
        set<string> temp2 = intersect;
        intersect.clear();

        // remove docs with word (order matters)
        set_difference(temp2.begin(), temp2.end(), temp->begin(),
                       temp->end(), inserter(intersect, intersect.begin()));
    }
}
void FileHandler::queryHashPersons(const string&person){
    // get set
    set<string>* temp = i.getDocsFromHashPerson(person);

    // check if set is empty
    if(temp==nullptr){
        intersect.clear();
    }else{
        // copy intersect set and clear old
        set<string> temp2 = intersect;
        intersect.clear();

        // intersect
        set_intersection(temp->begin(),temp->end(),temp2.begin(),
                         temp2.end(),inserter(intersect,intersect.begin()));
    }
}
void FileHandler::queryHashOrgs(const string&person){
    // get set
    set<string>* temp = i.getDocsFromHashOrgs(person);

    // check if set is empty
    if(temp==nullptr){
        intersect.clear();
    }else{
        // copy intersect set and clear old
        set<string> temp2 = intersect;
        intersect.clear();
        // intersect
        set_intersection(temp->begin(),temp->end(),temp2.begin(),
                         temp2.end(),inserter(intersect,intersect.begin()));
    }
}
void FileHandler::outputResults(){
    int i=1;
    if(intersect.size()==0){
        cout<<"\nNo search results found\n\n";
    }else{
        cout<<endl;
        for(const auto& e: intersect){
            if(i>15)
                break;
            doc.changeFile(e);
            cout<<i<<". "<<doc.getSite()<<endl;
            char esc_char = 27;
            cout<<esc_char<<"[1m"<<doc.getTitle()<<esc_char<<"[0m"<<endl;
            cout<<doc.getPublishDate().substr(0,10)<<" — ";
            cout<<doc.getTextBlurb()<<endl<<endl;;

            i++;
        }
        intersect.clear();
    }

}
