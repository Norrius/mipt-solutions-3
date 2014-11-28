#include <vector>
#include <string>
#include <unordered_map>
#include "suffixtree.h"

class FindAllVisitor {
    const std::string string;
    const std::string substring;
    std::vector<int> occurences;
    bool foundSuffix = false;
    std::unordered_map<int, int> depth;
    int currentDepth = 0;

public:
    FindAllVisitor(const std::string &string, const std::string &substring)
        : string(string), substring(substring) {}

    std::vector<int> getOccurences() {
        return occurences;
    }

    void onEnter(size_t node) {
        depth[node] = currentDepth;
    }

    bool onEdge(size_t current, size_t to, size_t left, size_t right) {
        if (right >= string.length()) {
            right = string.length() - 1;
        }
        if (!foundSuffix) {
            if (string.substr(left, right).compare(
                        substring.substr(left - currentDepth, right - currentDepth)) == 0) {
                currentDepth += right - left;
                return true;
            } else {
                return false;
            }
        } else {
            for (size_t i = 0; i < right - left; ++i) {
                occurences.push_back(0);
            }
            return true;
        }
    }

    void onExit(size_t node) {
        currentDepth = depth[node];
    }
};

std::vector<int> findAllOccurences(const SuffixTree &tree,
                                   const std::string &string, const std::string &substring) {
    FindAllVisitor visitor(string, substring);
    tree.DfsTraverse(visitor);
    return visitor.getOccurences();
}
