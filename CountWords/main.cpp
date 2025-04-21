#include <iostream>
#include <sstream>
#include <map>
#include <string>
using namespace std;

bool isPunctuation(char ch) {
    
    return (ch == ',' || ch == '.' || ch == '!' || ch == '?' || ch == ';' || ch == ':' || ch == '"' || ch == '\'');
}

void countWords(const string& text) {
    map<string, int> wordCount;
    stringstream ss(text);
    string word;

    while (ss >> word) {    
        while (!word.empty() && isPunctuation(word[0])) {
            word.erase(word.begin());  
        }
        while (!word.empty() && isPunctuation(word.back())) {
            word.pop_back();  
        }  
        if (!word.empty()) {
            ++wordCount[word];
        }
    }

    for (const auto& pair : wordCount) {
        cout << pair.first << ": " << pair.second << endl;
    }
}

int main() {
    string text;
    cout << "Enter text: ";
    getline(cin, text);
    countWords(text);
}