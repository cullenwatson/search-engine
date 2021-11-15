#include "IndexEntry.h"
#include<algorithm>
void IndexEntry::addDocToIdxEntry(const string& docName){
    // increase quantity
    auto it= find(DocNames.begin(),DocNames.end(),docName);
    if(it!=DocNames.end()){
        it->increase();
    }
        // or add doc
    else
        DocNames.emplace_back(docName);
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
