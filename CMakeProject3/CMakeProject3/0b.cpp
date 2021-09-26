#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <iostream>
#include <vector>

using std::map;
using std::multimap;
using std::string;

class Frequency {
    map<string, int> wordMap;

    int wordCounter = 0;

public:
    Frequency();

    void openFile(const std::string& f);

    void createCSV(const std::string& f);
};

Frequency::Frequency() {
    wordCounter = 0;
}

using namespace std;

string GetWord(istream& in) {
    char symbol;
    string ans = "";
    symbol = in.get();
    while (!isalpha(symbol) && !in.eof()) {
        symbol = in.get();
    }
    while (isalpha(symbol)) {
        ans.push_back(symbol);
        symbol = in.get();
    }
    return ans;
}


void Frequency::openFile(const string& f) {
    ifstream input(f);

    string word;
    while (!(word = GetWord(input)).empty()) {
        ++wordMap[word];
        ++wordCounter;
    }
}


void Frequency::createCSV(const std::string& f) {
    multimap<int, string> sortedWordMap;
    for (auto word = wordMap.rbegin(); word != wordMap.rend(); ++word) {
        sortedWordMap.insert(pair<int, string>(word->second, word->first));
    }
    wordMap.clear();
    ofstream out(f);

    for (auto element = sortedWordMap.rbegin(); element != sortedWordMap.rend(); ++element) {
        out << element->second << ',' << element->first << ',' << element->first / (double)wordCounter * 100 << '%'
            << endl;
    }
}

int main(int argc, char* argv[]) {
    Frequency wordFrequency;
    for (int i = 1; i < argc - 1; ++i) {
        wordFrequency.openFile(argv[i]);
    }
    wordFrequency.createCSV(argv[argc - 1]);
   
}