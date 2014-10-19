#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

string censor(const string &s, const vector<string> &u) {
    string r(s);
    int start = 0;
    for (string t : u) {
        size_t match = s.find(t, start);
        if (match == (size_t)(-1)) {
            return "I HAVE FAILED!!!";
        } else {
            for (size_t i = max(start-1,0); i < match; ++i) {
                if (r[i] != ' ') {
                    r[i] = '_';
                }
            }
            start = match + t.length() + 1;
        }
    }
    for (size_t i = max(start-1,0); i < s.length(); ++i) {
        if (r[i] != ' ') {
            r[i] = '_';
        }
    }

    return r;
}

int main() {
    string s, t;
    getline(cin, s);
    vector<string> u;
    while (cin >> t) {
        u.push_back(t);
    }

    cout << censor(s, u) << endl;

    return 0;
}
