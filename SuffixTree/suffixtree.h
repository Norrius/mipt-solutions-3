#ifndef SUFFIXTREE_SUFFIXTREE_H_
#define SUFFIXTREE_SUFFIXTREE_H_
#include <vector>
#include <string>
#include <limits>
#include <unordered_map>
#include <map>

const size_t infty = std::numeric_limits<size_t>::max();

class SuffixTree {
    struct NodeLink {
        size_t index;
        size_t left;
        size_t right;
        NodeLink() {}
        NodeLink(size_t index, size_t left, size_t right) :
            index(index), left(left), right(right) {}
    };

    struct ReferencePair {
        size_t closest;
        size_t left;
        size_t right;
        ReferencePair() {}
        ReferencePair(size_t closest, size_t left, size_t right) :
            closest(closest), left(left), right(right) {}
    };

    struct Node {
        size_t sufflink;
        std::map<char, NodeLink> links;
        Node() {}
        bool hasLink(char c);
    };

    const std::string string;
    size_t root;
    size_t dummy;
    std::vector<Node> nodes;
    ReferencePair activePoint;

    void addNextSymbol();
    void canonicalizeReference(ReferencePair *node);
    size_t testAndSplit();

    void buildTree();

public:
    explicit SuffixTree(const std::string &string);
    bool contains(const std::string &substring);
};

#endif  // SUFFIXTREE_SUFFIXTREE_H_
