#ifdef GTEST
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include "suffixtree.h"
#include "findalloccurences.h"
#include "gtest/gtest.h"
#include <iostream>

std::vector<int> slowFindAllOccurences(const std::string &string, const std::string &substring) {
    std::vector<int> occurences;
    if (substring.length() <= string.length()) {
        for (size_t i = 0; i <= string.length() - substring.length(); ++i) {
            auto s_start = string.begin() + i;
            auto s_end = string.begin() + i + substring.length();
            if (std::equal(s_start, s_end, substring.begin())) {
                occurences.push_back(i);
            }
        }
    }
    return occurences;
}

TEST(test_palindromic, 1) {
    std::string text;
    for (int i = 0; i < 8; ++i) {
        text = text + std::string(1, 'a' + i%2 + 1) + text;
    }
    std::string pattern = "ab";
    SuffixTree tree(text);
    auto exp = slowFindAllOccurences(text, pattern);
    auto ans = findAllOccurences(tree, text, pattern);

    ASSERT_EQ(exp.size(), ans.size());
    ASSERT_EQ(std::set<int>(exp.begin(), exp.end()), std::set<int>(ans.begin(), ans.end()));
}
#endif
