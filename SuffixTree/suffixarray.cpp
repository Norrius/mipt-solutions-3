#include "suffixarray.h"

class SuffixArrayBuilder : public Visitor {
    std::string string;
    std::vector<int> suffarray;
    std::unordered_map<int, int> depth;
    int current = 0;

public:
    SuffixArrayBuilder(const std::string &string)
        : string(string), suffarray(string.length()) {}

    ~SuffixArrayBuilder() {}

    std::vector<int> getArray() {
        return suffarray;
    }

    void onEnter(size_t node) {
        static bool firstRun = true;
        if (firstRun) {
            depth[node] = 0;
            firstRun = false;
        }
    }

    bool onEdge(size_t from, size_t to, size_t left, size_t right) {
        if (right > string.length()) {
            // leaf
            suffarray[current++] = string.length() - depth[to];
        }
        depth[to] = depth[from] + (right - left);
        return true;
    }

    void onExit(size_t) {}
};

std::vector<int> suffixArray(const std::string &string) {
    SuffixTree tree(string);
    SuffixArrayBuilder visitor(string);
    tree.accept(&visitor);
    return visitor.getArray();
}
