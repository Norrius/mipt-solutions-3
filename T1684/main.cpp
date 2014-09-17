#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

vector<int> prefix_function(const string &s, const string &t) {
    string x = s+"#"+t;
    int n = (int)x.length();
    vector<int> p(n);
    int j;
    for (int i=1; i<n; ++i) {
        j = p[i-1];
        while (j>0 && x[j] != x[i]) {
            j = p[j-1];
        }
        if (x[i] == x[j]) ++j;
        p[i] = j;
    }
    return p;
}

bool isOriginal(const string &source, const string &lastWord, vector<string> &decomposition) {
    int n = source.size();
    int m = lastWord.size();
    decomposition = vector<string>();

    vector<int> p = prefix_function(source, lastWord);

    bool hasZeroes = true;
    for (int i=n+1; i<n+m+1; ++i) {
        if (!p[i]) hasZeroes = false;
    }

    if (hasZeroes) {
        string subword;
        for (int i=n+m; i>n; i-=p[i]) {
            for (int j=p[i], c=0; j>0; --j, c++) {
                subword.push_back(lastWord[i-n-1-c]);
            }
            subword.push_back(' ');
        }
        subword.erase(subword.end()-1);
        reverse(subword.begin(), subword.end());
        decomposition.push_back(subword);
        return true;
    } else {
        return false;
    }
}

int main() {
    string s, t;
    vector<string> v;
    cin >> s >> t;

    bool result = isOriginal(s, t, v);

    if (result) {
        cout << "No\n";
        for (string w : v) {
            cout << w << ' ';
        }
    } else {
        cout << "Yes";
    }
    cout << endl;

    return 0;
}
