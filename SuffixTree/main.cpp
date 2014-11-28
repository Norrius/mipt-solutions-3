#include <bits/stdc++.h>
#include "suffixtree.h"

std::vector<int> findAllOccurences(const SuffixTree &tree,
                                   const std::string &string, const std::string &substring);
using namespace std;

int main()
{
    int k;
    cin >> k;
    while (k--) {
        string s;
        cin >> s;
        SuffixTree tree(s);

        int q;
        cin >> q;
        while (q--) {
            string t;
            cin >> t;
            cout << (findAllOccurences(tree, s, t).empty() ? "n" : "y") << '\n';
        }
    }

    return 0;
}

