#include "QueryEngine.h"

void QueryEngine::changeWord(const string&word){
    Word = word;
    stemWord();
}
void QueryEngine::stemWord(){
    // get stemmed version of word
    Porter2Stemmer::trim(Word);
    Porter2Stemmer::stem(Word);
}