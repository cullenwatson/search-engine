#include "IndexHandler.h"
#include<sstream>
#include<set>
#include<unordered_map>
#include "porter2_stemmer.h"
#include<vector>
#include <algorithm>
// list of stop words
set<string> stopWords{
        "able", "about", "above", "abroad", "according", "accordingly", "across", "actually", "adj", "after", "afterwards", "again", "against", "ago", "ahead", "ain't", "all", "allow", "allows", "almost", "alone", "along", "alongside", "already", "also", "although", "always", "am", "amid", "amidst", "among", "amongst", "an", "and", "another", "any", "anybody", "anyhow", "anyone", "anything", "anyway", "anyways", "anywhere", "apart", "appear", "appreciate", "appropriate", "are", "aren't", "around", "as", "a's", "aside", "ask", "asking", "associated", "at", "available", "away", "awfully", "back", "backward", "backwards", "be", "became", "because", "become", "becomes", "becoming", "been", "before", "beforehand", "begin", "behind", "being", "believe", "below", "beside", "besides", "best", "better", "between", "beyond", "both", "brief", "but", "by", "came", "can", "cannot", "cant", "can't", "caption", "cause", "causes", "certain", "certainly", "changes", "clearly", "c'mon", "co", "co.", "com", "come", "comes", "concerning", "consequently", "consider", "considering", "contain", "containing", "contains", "corresponding", "could", "couldn't", "course", "c's", "currently", "dare", "daren't", "definitely", "described", "despite", "did", "didn't", "different", "directly", "do", "does", "doesn't", "doing", "done", "don't", "down", "downwards", "during", "each", "edu", "eg", "eight", "eighty", "either", "else", "elsewhere", "end", "ending", "enough", "entirely", "especially", "et", "etc", "even", "ever", "evermore", "every", "everybody", "everyone", "everything", "everywhere", "ex", "exactly", "example", "except", "fairly", "far", "farther", "few", "fewer", "fifth", "first", "five", "followed", "following", "follows", "for", "forever", "former", "formerly", "forth", "forward", "found", "four", "from", "further", "furthermore", "get", "gets", "getting", "given", "gives", "go", "goes", "going", "gone", "got", "gotten", "greetings", "had", "hadn't", "half", "happens", "hardly", "has", "hasn't", "have", "haven't", "having", "he", "he'd", "he'll", "hello", "help", "hence", "her", "here", "hereafter", "hereby", "herein", "here's", "hereupon", "hers", "herself", "he's", "hi", "him", "himself", "his", "hither", "hopefully", "how", "howbeit", "however", "hundred", "i'd", "ie", "if", "ignored", "i'll", "i'm", "immediate", "in", "inasmuch", "inc", "inc.", "indeed", "indicate", "indicated", "indicates", "inner", "inside", "insofar", "instead", "into", "inward", "is", "isn't", "it", "it'd", "it'll", "its", "it's", "itself", "i've", "just", "k", "keep", "keeps", "kept", "know", "known", "knows", "last", "lately", "later", "latter", "latterly", "least", "less", "lest", "let", "let's", "like", "liked", "likely", "likewise", "little", "look", "looking", "looks", "low", "lower", "ltd", "made", "mainly", "make", "makes", "many", "may", "maybe", "mayn't", "me", "mean", "meantime", "meanwhile", "merely", "might", "mightn't", "mine", "minus", "miss", "more", "moreover", "most", "mostly", "mr", "mrs", "much", "must", "mustn't", "my", "myself", "name", "namely", "nd", "near", "nearly", "necessary", "need", "needn't", "needs", "neither", "never", "neverf", "neverless", "nevertheless", "new", "next", "nine", "ninety", "no", "nobody", "non", "none", "nonetheless", "noone", "no-one", "nor", "normally", "not", "nothing", "notwithstanding", "novel", "now", "nowhere", "obviously", "of", "off", "often", "oh", "ok", "okay", "old", "on", "once", "one", "ones", "one's", "only", "onto", "opposite", "or", "other", "others", "otherwise", "ought", "oughtn't", "our", "ours", "ourselves", "out", "outside", "over", "overall", "own", "particular", "particularly", "past", "per", "perhaps", "placed", "please", "plus", "possible", "presumably", "probably", "provided", "provides", "que", "quite", "qv", "rather", "rd", "re", "really", "reasonably", "recent", "recently", "regarding", "regardless", "regards", "relatively", "respectively", "right", "round", "said", "same", "saw", "say", "saying", "says", "second", "secondly", "see", "seeing", "seem", "seemed", "seeming", "seems", "seen", "self", "selves", "sensible", "sent", "serious", "seriously", "seven", "several", "shall", "shan't", "she", "she'd", "she'll", "she's", "should", "shouldn't", "since", "six", "so", "some", "somebody", "someday", "somehow", "someone", "something", "sometime", "sometimes", "somewhat", "somewhere", "soon", "sorry", "specified", "specify", "specifying", "still", "sub", "such", "sup", "sure", "take", "taken", "taking", "tell", "tends", "th", "than", "thank", "thanks", "thanx", "that", "that'll", "thats", "that's", "that've", "the", "their", "theirs", "them", "themselves", "then", "thence", "there", "thereafter", "thereby", "there'd", "therefore", "therein", "there'll", "there're", "theres", "there's", "thereupon", "there've", "these", "they", "they'd", "they'll", "they're", "they've", "thing", "things", "think", "third", "thirty", "this", "thorough", "thoroughly", "those", "though", "three", "through", "throughout", "thru", "thus", "till", "to", "together", "too", "took", "toward", "towards", "tried", "tries", "truly", "try", "trying", "t's", "twice", "two", "un", "under", "underneath", "undoing", "unfortunately", "unless", "unlike", "unlikely", "until", "unto", "up", "upon", "upwards", "us", "use", "used", "useful", "uses", "using", "usually", "v", "value", "various", "versus", "very", "via", "viz", "vs", "want", "wants", "was", "wasn't", "way", "we", "we'd", "welcome", "well", "we'll", "went", "were", "we're", "weren't", "we've", "what", "whatever", "what'll", "what's", "what've", "when", "whence", "whenever", "where", "whereafter", "whereas", "whereby", "wherein", "where's", "whereupon", "wherever", "whether", "which", "whichever", "while", "whilst", "whither", "who", "who'd", "whoever", "whole", "who'll", "whom", "whomever", "who's", "whose", "why", "will", "willing", "wish", "with", "within", "without", "wonder", "won't", "would", "wouldn't", "yes", "yet", "you", "you'd", "you'll", "your", "you're", "yours", "yourself", "yourselves", "you've", "zero"
};
unordered_map<string,string> hashedWords;
void IndexHandler::addPersons(const string&docName, list<string> persons){
    for (auto it=persons.begin(); it != persons.end(); ++it)
        hashTablePersons.insert(*it, docName);
}
void IndexHandler::addOrgs(const string&docName, list<string> persons){
    for (auto it=persons.begin(); it != persons.end(); ++it)
        hashTableOrgs.insert(*it, docName);
}
void IndexHandler::addDoc(const string&docName, const string&docText){
    // put text of file in ss
    stringstream ss(docText);

    // extract the words
    string word;
    while(ss>>word){
        // see if word is in stoplist
        auto it= stopWords.find(word);
        if(it!=stopWords.end()){
            continue;
        }
        numWords++;
        // check if word has been hashed
        auto it2 = hashedWords.find(word);
        if(it2!=hashedWords.end()){
            word = hashedWords[word];

        }
        else {
            // get stemmed version of word
            string temp = word;
            Porter2Stemmer::trim(word);
            Porter2Stemmer::stem(word);
            // add to table
            hashedWords[temp]=word;
            hashedWords[word]=word;
        }

        // continue if word is empty
        if(word.empty())
            continue;

        // insert word to tree
        IndexEntry temp(word);
        IndexEntry& test = TreeIndex.insert(temp);

        // add doc to entry
        test.addDocToIdxEntry(docName);

    }
}
void IndexHandler::getTop50Words(){
    TreeIndex.output();
    vector<IndexEntry>& allWords = TreeIndex.getSet();
    cout<<"  \t\tWord - # of Appearances"<<endl;
    struct greaterThan
    {
        inline bool operator() (const IndexEntry& struct1, const IndexEntry& struct2)
        {
            return (struct1.getNumDocs() > struct2.getNumDocs());
        }
    };
    // sort vector
    sort(allWords.begin(), allWords.end(), greaterThan());
    int i=0;
    for(IndexEntry& e: allWords){
        if(i>49)
            break;
        cout<<"  \t\t"<<i+1<<".  "<<e.getWord()<<" - "<<e.getNumDocs()<<endl;
        i++;
    }
}

set<string>* IndexHandler::getDocsFromTree(const string&word){
    IndexEntry* result= TreeIndex.getElement(IndexEntry(word));
    if(result==nullptr){
        //cout<<"No docs for that word found ("<<word<<") \n";
        return nullptr;
    }
    else{
       //cout<<*result<<endl;
        return &result->getDocNamesSet();
    }


}
set<string>* IndexHandler::getDocsFromHashPerson(const string&word){
    //cout<<word<<" (PERSON)"<<endl;

    if(hashTablePersons.get(word)!=nullptr){
        set<string>& a = *hashTablePersons.get(word);

        /*for(const auto& e: a){
            cout<<"     "<<e<<endl;
        }
        cout<<endl;*/
    }
    /*else{
        cout<<"     No docs for that person found\n\n";
    }*/
    return hashTablePersons.get(word);
}
set<string>* IndexHandler::getDocsFromHashOrgs(const string&word){
    //cout<<word<<" (ORG)"<<endl;
    if(hashTableOrgs.get(word)!=nullptr){
        set<string>& a = *hashTableOrgs.get(word);

        /*for(const auto& e: a){
            cout<<"     "<<e<<endl;
        }
        cout<<endl;*/
    }
    /*else{
        cout<<"     No docs for that org found\n\n";
    }*/
    return hashTableOrgs.get(word);
}


