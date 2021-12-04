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
int avgNumWords=0;
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
        cout<<"\nSearch Engine Menu\n";
        cout<<"  1. Load Data Files\n";
        cout<<"  2. Execute Query\n";
        cout<<"  3. Show Stats\n";
        cout<<"  4. Save Index to Persistence File\n";
        cout<<"  5. Clear Index\n";
        cout<<"  Enter an option: ";
        cin>>option;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(option){

            // create index
            case 1:
                if(!parsed){
                    cout<<"\nChoose Where To Load Data From";
                    cout<<"\n  1. Load from filepath";
                    cout<<"\n  2. Load from corpus (persistence index)";
                    cout<<"\n  Enter an option: ";


                    int choice;
                    cin>>choice;

                    if(choice==1){
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout<<"  Enter path to the dataset: ";
                        getline(cin,path);
                        numOfFiles = readInFiles(path);
                    }
                    else{
                        cout<<"\nLoading index..."<<flush;
                        files.loadOrgsIndex();
                        files.loadPersonIndex();
                        files.loadWordsIndex();
                        cout<<" Complete!\n";
                        parsed = true;
                        numOfFiles = 306242;
                        avgNumWords = 269;
                        files.setNumFiles(306242);
                    }

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
                cout<<"\nSearch Engine Statistics\n";
                cout<<"  Total number of individual articles indexed: "<<numOfFiles<<endl;
                cout<<"  Average number of words indexed per article: "<<avgNumWords<<endl;
                cout<<"  Total number of unique words: "<<files.getTreeSize()<<endl;
                cout<<"  Total number of unique persons: "<<files.getNumUniquePersons()<<endl;
                cout<<"  Total number of unique organizations: "<<files.getNumUniqueOrgs()<<endl;
                cout<<"  50 most frequent words: "<<endl;
                files.getTop50Words();
                break;
            case 4:
                if(!parsed){
                    cout<<"\nNo data has been loaded!\n";
                }else{
                    cout<<"\nSaving index to persistence file... "<<flush;
                    files.saveOrgIndex();
                    files.savePersonIndex();
                    files.saveWordIndex();
                    cout<<" Complete!"<<endl;

                }
                break;
            case 5:if(!parsed){
                    cout<<"\nNo data has been loaded!\n";
                }else{
                    cout<<"\nClearing index..."<<flush;
                    files.clear();
                    cout<<" Complete!\n";

                    // reset vars
                    parsed= false;
                    avgNumWords = 0;
                    numOfFiles = 0;
                }

                break;
            default: option =-1;
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
        files.setNumFiles(0);
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
        cout<<"Complete!\n";
        parsed = true;
        files.setNumFiles(totalNumFiles);
        avgNumWords = files.getNumWords() / totalNumFiles;
        return totalNumFiles;
    }
}
void getSearch(){
    // search phrase
    string search;
    cout<<"\nEnter search query: ";
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
            files.setMainWord(word);
            option = 0;
        }else if(word=="OR"){
            // get next word
            getline(ss,word,' ');
            files.setMainWord(word);

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
            if(count==0)
                files.setMainWord(word);
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
