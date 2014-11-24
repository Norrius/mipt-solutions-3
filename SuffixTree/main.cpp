#include <bits/stdc++.h>
#include "suffixtree.h"

using namespace std;

int main()
{
    int k;
    cin >> k;
    while (k--) {
        string s;
        cin >> s;
        SuffixTree tree(s);
        cerr << "!";

        int q;
        cin >> q;
        while (q--) {
            string t;
            cin >> t;
            cout << (tree.contains(t) ? "y" : "n") << '\n';
        }
    }

    return 0;
}

