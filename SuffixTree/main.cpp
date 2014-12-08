#include <bits/stdc++.h>
#include "suffixarray.h"
#include "gtest/gtest.h"

using namespace std;

int main(int argc, char **argv) {
#ifdef GTEST
    ::testing::GTEST_FLAG(print_time) = false;
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
#else
    string s;
    cin >> s;

    auto v = suffixArray(s);

    for (auto e : v) {
        cout << e << ' ';
    }
    cout << endl;

    return 0;
#endif
}


/*

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
            auto v = findAllOccurences(tree, s, t);
            cout << (v.empty() ? "n" : "y " + to_string(v.size())) << '\n';
            for (auto e : v) {
                cout << e << ' ';
            }   cout << endl;
        }
    }

*/
