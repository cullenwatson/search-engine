#include <iostream>
#include<filesystem>
#include "FileHandler.h"
#include "QueryEngine.h"
using namespace std;
namespace fs = std::filesystem;

FileHandler files;
void readInFiles(const string&);

int main(int argc, char* argv[]) {
    // read in files and create avl tree
    char* path = "/home/cullenog/smalldataset";
    readInFiles(path);

    string search;
    //cout<<"Enter a search:";
    //getline(cin,search);
    //files.queryTree(search);
   // files.queryHashPersons("dominic blakemore");
    files.queryHashOrgs("reuters staff");
    // output tree
    //files.output();

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
