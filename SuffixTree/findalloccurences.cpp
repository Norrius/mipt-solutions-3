#include "findalloccurences.h"

class FindAllVisitor : public SuffixTreeVisitor {
    const std::string string;
    const std::string substring;
    std::vector<int> occurences;
    std::unordered_map<int, int> depth;

public:
    FindAllVisitor(const std::string &string, const std::string &substring)
        : string(string), substring(substring) {}

    ~FindAllVisitor() {}

    std::vector<int> getOccurences() {
        return occurences;
    }

    void onEnter(size_t node) {
        static bool firstRun = true;
        if (firstRun) {
            depth[node] = 0;
            firstRun = false;
        }
    }

    bool onEdge(size_t current, size_t to, size_t left, size_t right) {
        bool leaf = false;
        if (right >= string.length()) {
            right = string.length();
            leaf = true;
        }
        size_t matchLength = std::min(substring.length() - depth[current], right - left);
        auto stringStart = string.begin() + left;
        auto stringEnd = string.begin() + left + matchLength;
        auto substringStart = substring.begin() + depth[current];
        if (depth[current] >= (int)substring.length()) {
            occurences.push_back(left - depth[current]);
            return true;
        }
        if (std::equal(stringStart, stringEnd, substringStart)) {
            depth[to] = depth[current] + (right - left);
            if (depth[to] >= (int)substring.length() && leaf) {
                occurences.push_back(left - depth[current]);
            }
            return true;
        } else {
            return false;
        }

    }

    void onExit(size_t) {}
};

std::vector<int> findAllOccurences(const SuffixTree &tree,
                                   const std::string &string, const std::string &substring) {
    FindAllVisitor visitor(string, substring);
    tree.DfsTraverse(visitor);
    return visitor.getOccurences();
}
