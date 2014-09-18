#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

vector<int> prefix_function(const string &s) {
    string concat(s);
    reverse(concat.begin(), concat.end());
    concat += "#"+s;
    int n = (int)concat.length();

    vector<int> p(n);
    int j;
    for (int i=1; i<n; ++i) {
        j = p[i-1];
        while (j>0 && concat[j] != concat[i]) {
            j = p[j-1];
        }
        if (concat[i] == concat[j]) ++j;
        if (j != (int)s.length()) {
            p[i] = j;
        } else {
            p[i] = p[j-1];
        }
    }
    return p;
}

string palindromize(const string &s) {
    vector<int> p = prefix_function(s);
    int maxPal = p.back();

    int len = (int)s.length();
    int newLen = len*2-maxPal;

    string palindrome(s);
    palindrome.resize(newLen);

    for (int i=len; i<newLen; ++i) {
        palindrome[i] = palindrome[newLen-i-1];
    }

    return palindrome;
}

int main() {
    string s;
    cin >> s;

    cout << palindromize(s) << endl;

    return 0;
}
