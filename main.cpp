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
    char* path = argv[1];
    readInFiles(path);

    files.queryTree(argv[2]);
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
