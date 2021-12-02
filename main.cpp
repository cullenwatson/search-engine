#include <iostream>
#include<filesystem>
#include "FileHandler.h"
#include "QueryEngine.h"
#include <sstream>
#include <algorithm>
using namespace std;
namespace fs = std::filesystem;

FileHandler files;
void readInFiles(const string&);
void getSearch();
int main(int argc, char* argv[]) {
    // read in files and create avl tree
    char* path = "/home/cullenog/smalldataset";
    readInFiles(path);

    // get search from user
    getSearch();



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
    string search="tuesday PERSON kotb ORG mark";
    //cout<<"Enter a search:";
    //getline(cin,search);

    // parse string
    stringstream ss(search);
    string substring;
    getline(ss,substring, ' ');
    // chaining
    if(substring=="AND"){

    }else if(substring=="OR"){

    }
    else{
        // search for term
        files.queryTree(substring);

        // get person or org
        while(getline(ss,substring, ' ')){
            if(substring=="PERSON"){
                getline(ss,substring, ' ');
                files.queryHashPersons(substring);

            }
            else if(substring=="ORG"){
                getline(ss,substring, ' ');
                files.queryHashOrgs(substring);

            }
        }
        files.intersectSets();
        files.outputIntersect();
    }
}
