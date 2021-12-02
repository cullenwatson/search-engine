#include "IndexEntry.h"
#include<algorithm>
void IndexEntry::addDocToIdxEntry(const string& docName){
    // increase quantity
    auto it= DocNames.find(docName);
    if(it!=DocNames.end()){
        it->second++;
        //return;
    }
    // or add doc
    else{
        DocNames[docName] = 1;
        DocNamesSet.insert(docName);
    }
}

bool IndexEntry::operator== (const IndexEntry& s) const {
    return Word == s.Word;
}
bool IndexEntry::operator< (const IndexEntry& s) const {
    return Word < s.Word;
}
bool IndexEntry::operator> (const IndexEntry& s) const {
    return s.Word < Word;
}
