//
// Created by spknnk on 07.03.19.
//

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <string>
#include <algorithm>

class TSufArr;

class TNode {
public:
    std::map<char, TNode *> dest;
    std::string::iterator begin, end;
    TNode *sufLink;
    TNode(std::string::iterator start, std::string::iterator end);
    ~TNode() = default;
};

class TSufTree  {
public:
    TSufTree(std::string s);
    ~TSufTree() = default;
    friend TSufArr;

private:
    std::string text;
    TNode *root;
    int isready;
    TNode *SLmarker, *activeNode;
    int activeLen;
    std::string::iterator activeEdge;

    int EdgeLen(TNode *node, std::string::iterator cur_pos);
    void TreeDestroy(TNode *node);
    bool WalkDown(std::string::iterator cur_pos, TNode *node);
    void SufLinkActivate(TNode *node);
    void TrExtend(std::string::iterator current);
    void DFS(TNode *node, std::vector<int> &result, int depth);
};

class TSufArr {
public:
    TSufArr(TSufTree tree);
    std::vector<int> Find(std::string pattern);
    ~TSufArr() = default;
private:
    std::string text;
    std::vector<int> array;
};
