#include <iostream>
#include<filesystem>
#include "FileHandler.h"
#include <sstream>
#include <algorithm>
#include<limits>
#include <sys/stat.h>
using namespace std;
namespace fs = std::filesystem;

FileHandler files;
bool parsed = false;

int readInFiles(const string&);
void getSearch();
int main(int argc, char* argv[]) {
    // read in files and create avl tree
    //string path = "/home/cullenog/smalldataset";
    string path;

    int option=0;
    int numOfFiles=0;
    do{
        // output menu system
        cout<<"\n  -----SEARCH ENGINE MENU-----\n";
        cout<<"        (1) Load Files\n";
        cout<<"        (2) Search Query\n";
        cout<<"        (3) Search Engine Stats\n";
        cout<<"  ENTER A MENU OPTION: ";
        cin>>option;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(option){
            // create index
            case 1:
                if(!parsed){
                    cout<<"\nEnter the path to the corpus: ";
                    getline(cin,path);
                    numOfFiles = readInFiles(path);
                }
                else{
                    cout<<"\nFiles already loaded!\n";
                }
                break;
           // output search results
            case 2:
                if(parsed)
                    getSearch();
                else
                    cout<<"\nNo data has been loaded!\n";
                break;
            case 3:
                cout<<"\n  -----SEARCH ENGINE STATISTICS-----\n";
                cout<<"  Total number of individual articles indexed: "<<numOfFiles<<endl;
                int avgNumWords;
                if(!parsed)
                    avgNumWords=0;
                else
                    avgNumWords = files.getNumWords() / numOfFiles;
                cout<<"  Average number of words indexed per article: "<<avgNumWords<<endl;
                cout<<"  Total number of unique words: "<<files.getTreeSize()<<endl;
                cout<<"  Total number of unique persons: "<<files.getNumUniquePersons()<<endl;
                cout<<"  Total number of unique organizations: "<<files.getNumUniqueOrgs()<<endl<<endl;
                break;

            case -1: break;
            default: option =0;
        }
    }while(option!=-1);

    return 0;
}
// loop over the files in the directory
int readInFiles(const string& path){
    int totalNumFiles=0;
    // check if path is valid
    struct stat info;
    if( stat( path.c_str(), &info ) != 0 ){
        cout<<"\nFolder not found\n";
        return 0;
    }else{
        cout<<"\nCreating index..."<<flush;
        for (const auto & entry : fs::recursive_directory_iterator(path)){
            if(!is_directory(entry)){
                string filename = entry.path().c_str();
                // update index
                files.updateIndex(filename);
                totalNumFiles++;
            }
        }
        cout<<" Complete!\n";
        parsed = true;
        return totalNumFiles;
    }
}
void getSearch(){
    // search phrase
    string search;
    cout<<"\nEnter search phrase: ";
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
    cout<<"Would you like to search again? (y/n): ";
    cin>>repeat;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if(repeat=='y'||repeat=='Y'){
        getSearch();
    }

}
