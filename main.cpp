#include <string>
#include <iostream>

#include "suftree.h"

TNode::TNode(std::string::iterator start, std::string::iterator end): begin(start), end(end), sufLink(nullptr) {}

TSufTree::TSufTree(std::string s):text(std::move(s)),root(new TNode(text.end(), text.end())), isready(0) {
    activeEdge = text.begin();
    activeLen = 0;

    activeNode = root;
    SLmarker = root;
    root->sufLink = root;

    for (std::string::iterator i = text.begin(); i != text.end(); ++i) {
        TrExtend(i);
    }
}

void TSufTree::SufLinkActivate(TNode *node) {
    if (SLmarker != root) {
        SLmarker->sufLink = node;
    }

    SLmarker = node;
}

int TSufTree::EdgeLen(TNode *node, std::string::iterator cur_pos) {
    return static_cast<int>(min(node->end, cur_pos + 1) - node->begin);
}

void TSufTree::TreeDestroy(TNode *node) {
    for (auto &it : node->dest) {
        TreeDestroy(it.second);
    }
    delete node;
}

void TSufTree::TrExtend(std::string::iterator current) {
    SLmarker = root;
    ++isready;

    while (isready) {
        if (!activeLen) {
            activeEdge = current;
        }
        auto tree_it = activeNode->dest.find(*activeEdge);
        TNode *next = (tree_it == activeNode->dest.end()) ? NULL : tree_it->second;
        if (!next) {
            TNode *leaf = new TNode(current, text.end());
            activeNode->dest[*activeEdge] = leaf;
            SufLinkActivate(activeNode);
        } else {
            if (WalkDown(current, next)) {
                continue;
            }

            if (*(next->begin + activeLen) == *current) {
                ++activeLen;
                SufLinkActivate(activeNode);
                break;
            }

            TNode *split = new TNode(next->begin, next->begin + activeLen);
            TNode *leaf = new TNode(current, text.end());
            activeNode->dest[*activeEdge] = split;

            split->dest[*current] = leaf;
            next->begin += activeLen;
            split->dest[*next->begin] = next;
            SufLinkActivate(split);
        }
        --isready;
        if (activeNode == root && activeLen) {
            --activeLen;
            activeEdge = current - isready + 1;
        } else {
            activeNode = (activeNode->sufLink) ? activeNode->sufLink : root;
        }
    }
}

bool TSufTree::WalkDown(std::string::iterator cur_pos, TNode *node) {
    if (activeLen >= EdgeLen(node, cur_pos)) {
        activeEdge += EdgeLen(node, cur_pos);
        activeLen -= EdgeLen(node, cur_pos);
        activeNode = node;
        return true;
    }
    return false;
}

void TSufTree::DFS(TNode *node, std::vector<int> &result, int depth) {
    if (node->dest.empty()) {
        result.push_back(static_cast<int &&>(text.size() - depth));//found
        return;
    }
    for (auto &it : node->dest) {
        int tmp = depth;
        tmp += it.second->end - it.second->begin;
        DFS(it.second, result, tmp);
    }
}

TSufArr::TSufArr(TSufTree tree):text(tree.text), array() {
    tree.DFS(tree.root, array, 0);
    tree.TreeDestroy(tree.root); //leak
}

std::vector<int> TSufArr::Find(std::string pattern) {
    std::pair <std::vector<int>::iterator, std::vector<int>::iterator> bounds(array.begin(), array.end());
    for (int i = 0; i < pattern.size() && bounds.first != bounds.second; ++i) {
        bounds = equal_range(bounds.first, bounds.second, std::numeric_limits<int>::max(),
                            [this, &pattern, &i](int l, int r) -> bool {
                            bool tmp;
                            (l == std::numeric_limits<int>::max()) ? tmp = (pattern[i] < text[i + r]) : tmp = (text[i + l] < pattern[i]);
                            return tmp;
                            });
    }

    std::vector<int> result(bounds.first, bounds.second);
    std::sort(result.begin(), result.end());

    return result;
}

int main(void) {
    std::string text, pattern;
    std::cin >> text;

    TSufTree tree(text + "$");
    TSufArr array(tree);

    for (int pattern_num = 1; std::cin >> text; ++pattern_num) {
        std::vector<int> result = array.Find(text);
        if (!result.empty()) {
            std::cout << pattern_num << ": ";
            for (int i = 0; i < result.size(); ++i) {
                std::cout << result[i] + 1; // from 0
                if (i < result.size() -  1) std::cout << ", ";
            }
            std::cout << '\n';
        }
    }
    return 0;
}
