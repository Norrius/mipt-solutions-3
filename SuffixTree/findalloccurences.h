#ifndef FINDALLOCCURENCES_FINDALLOCCURENCES_H
#define FINDALLOCCURENCES_FINDALLOCCURENCES_H
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include "suffixtree.h"

std::vector<int> findAllOccurences(const SuffixTree &tree,
                                   const std::string &string, const std::string &substring);

#endif  // FINDALLOCCURENCES_FINDALLOCCURENCES_H
