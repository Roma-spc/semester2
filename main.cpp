#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool areBracketsBalanced(const string& e) {
    stack<char> s;
    for (char ch : e) {
        if (ch == '(' || ch == '{' || ch == '[') {
            s.push(ch);
        }
        else if (ch == ')' || ch == '}' || ch == ']') {
            if (s.empty()) return false;
            char top = s.top();
            if ((ch == ')' && top != '(') ||
                (ch == '}' && top != '{') ||
                (ch == ']' && top != '[')) {
                return false;
            }
            s.pop();
        }
    }
    return s.empty();
}

int main() {
    cout << "Enter text with brackets: ";
    string text;
    getline(cin, text);
    cout << "Are brackets balanced? - " << (areBracketsBalanced(text) ? "yes" : "no") << endl;
}