#include <iostream>
#include<filesystem>
#include "FileHandler.h"
#include "QueryEngine.h"
#include <sstream>
#include <algorithm>
#include<limits>
using namespace std;
namespace fs = std::filesystem;

FileHandler files;
void readInFiles(const string&);
void getSearch();
int main(int argc, char* argv[]) {
    // read in files and create avl tree
    char* path = "/home/cullenog/smalldataset";
    readInFiles(path);

    int option;
    // get search from user
    cout<<"1. Search Term\n";
    cin>>option;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    switch(option){
        case 1:
            getSearch();
    }



    return 0;
}
// loop over the files in the directory
void readInFiles(const string& path){
    for (const auto & entry : fs::recursive_directory_iterator(path)){
        if(!is_directory(entry)){
            string filename = entry.path().c_str();
            // update index
            files.updateIndex(filename);
        }
    }
}
void getSearch(){
    // search phrase
    string search;
    cout<<"Enter search phrase: ";
    getline(cin,search);



    // put search phrase into ss
    stringstream ss(search);
    string word;

    // var to show if the word is an identifier
    int option;
    int count=0;

    int check=1;

    // get every word in the phrase
    while(getline(ss,word,' ')){
        if(word=="AND"){
            // get next word
            getline(ss,word,' ');
            option = 0;
        }else if(word=="OR"){
            // get next word
            getline(ss,word,' ');
            option = 4;
            check = 2;
        }else if(word=="PERSON"){
            option = 1;
        }else if(word=="ORG"){
            option = 2;
        }else if(word=="NOT"){
            option = 3;
        }
        // search word
        else{
            // AND
            if(check==1)
                option = 0;
            // OR
            else {
                option = 4;
            }
        }

        switch(option){
            // AND
            case 0:{
                files.queryTreeWords(word, count, 1);
                break;
            }
            // OR
            case 4:{
                files.queryTreeWords(word, count, 2);
                break;
            }
            // get next word if it's an identifier
            case 1:{
                // can't use alone
                getline(ss,word,' ');
                files.queryHashPersons(word);
                break;
            }
            case 2:{
                getline(ss,word,' ');
                files.queryHashOrgs(word);
                break;
            }
            case 3:{
                getline(ss,word,' ');
                files.queryTreeNotWords(word);
                break;
            }
        }
        count++;
    }
    // output the result
    //files.outputIntersect();
    files.outputResults();

    // ask user if they want to search again
    char repeat;
    cout<<"Would you like to search again? (Y/N): ";
    cin>>repeat;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if(repeat=='y'||repeat=='Y'){
        cout << string(50, '\n');
        getSearch();
    }

}
