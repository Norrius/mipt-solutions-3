#include "suffixtree.h"

bool SuffixTree::Node::hasLink(char c) {
    return links.find(c) != links.end();
}

SuffixTree::SuffixTree(const std::string &string) :
    string(string+'\x1f'),
    root(0),
    dummy(1),
    nodes({Node(), Node()}),
    activePoint(ReferencePair(root, 0, 0)) {
    nodes[root].sufflink = dummy;
    for (size_t i = 0; i < this->string.size(); ++i) {
        if (!(nodes[dummy].hasLink(this->string[i]))) {
            nodes[dummy].links[this->string[i]] = NodeLink(root, i, i+1);
        }
    }
    buildTree();
}

void SuffixTree::buildTree() {
    for (size_t i = 0; i < string.length(); ++i) {
        addNextSymbol();
        ++activePoint.right;
        canonicalizeReference(&activePoint);
    }
}

void SuffixTree::addNextSymbol() {
    size_t previous = root;
    size_t current = testAndSplit();
    while (current != nodes.size()) {
        // restore suffix links
        if (previous != root) {
            nodes[previous].sufflink = current;
        }
        previous = current;

        // step
        activePoint.closest = nodes[activePoint.closest].sufflink;
        canonicalizeReference(&activePoint);

        current = testAndSplit();
    }
    if (previous != root) {
        // restore suffix link for the last node
        nodes[previous].sufflink = current;
    }
}

void SuffixTree::canonicalizeReference(SuffixTree::ReferencePair *node) {
    if (node->left != node->right) {
        // one jump back, one step forward
        NodeLink link = nodes[node->closest].links[string[node->left]];
        while (link.right - link.left <= node->right - node->left) {
            // update with lower ancestor
            node->closest = link.index;
            node->left += link.right - link.left;
            if (node->left < node->right) {
                // step, same logic
                link = nodes[node->closest].links[string[node->left]];
            }
        }
    }
}

size_t SuffixTree::testAndSplit() {
    // point of split node
    size_t target;
    if (activePoint.left == activePoint.right) {
        if (nodes[activePoint.closest].hasLink(string[activePoint.right])) {
            // found endPoint
            return nodes.size();
        } else {
            target = activePoint.closest;
        }
    } else {
        NodeLink link(nodes[activePoint.closest].links[string[activePoint.left]]);
        size_t targetIndex = link.left + (activePoint.right - activePoint.left);
        if (string[targetIndex] == string[activePoint.right]) {
            // found endPoint
            return nodes.size();
        }
        target = nodes.size();
        nodes.push_back(Node());
        // link the ancestor to the new node
        nodes[activePoint.closest].links[string[link.left]] =
                NodeLink(target, link.left, targetIndex);
        // link the new node to the node below
        nodes[target].links[string[targetIndex]] =
                NodeLink(link.index, targetIndex, link.right);
    }
    // add new inf-edge from the split point
    nodes.push_back(Node());
    nodes[target].links[string[activePoint.right]] =
            NodeLink(nodes.size()-1, activePoint.right, infty);
    return target;
}
