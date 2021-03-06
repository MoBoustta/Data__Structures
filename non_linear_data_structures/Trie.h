/*******************************************************************************
 * DATA STRUCTURES IMPLEMENTATIONS
 *
 *   __                __
 *  |  \  _  |_  _    (_  |_  _      _ |_      _  _  _
 *  |__/ (_| |_ (_|   __) |_ |  |_| (_ |_ |_| |  (- _)
 *
 *
 * Trie
 *
 * -> Tries Applications:
 *  1. Building auto-completion
 *
 * -> Features:
 * being 'L' the length of the word we want to insert or delete
 * 1. Look Up O(L)
 * 2. Delete O(L)
 * 3. Insert O(L)
 *
 * https://en.wikipedia.org/wiki/Trie
 *
 * Created by moboustt on 10/4/20.
 * @author (moboustta6@gmail.com)
 * @github MoBoustta
 ******************************************************************************/


#ifndef DATA__STRUCTURES_TRIE_H
#define DATA__STRUCTURES_TRIE_H

#include <map>
#include <string>
#include <vector>

class Node {
public:

    Node() = default;
    explicit Node(char v);

public:
    bool hasChild(char& c) const;

    void addChild(char &c) const;

    Node* getChild(char& c) const;

    [[nodiscard]] std::vector<Node*> getChildren() const;

    void removeChild(char c) const;

public:

    char value;
    bool isEndOfWord;
    std::map<char, Node*> *children;
};


class Trie {

public:

    Trie();
    ~Trie();

public:

    void insert(const std::string &str);

    void remove(const std::string &str);

    bool contains_iter(const std::string& str);

    bool contains_rec(const std::string &str);

    std::size_t countWords();

    std::vector<std::string> autoCompletion(const std::string& str);

    void preOrderTraversal() const;

    void postOrderTraversal() const;

    std::string longestCommonPrefix(std::vector<std::string>& words);

private:
    Node *root;

private:

    bool contains_rec(Node *rootNode, const std::string &str);

    void countWords(Node *rootNode, std::size_t &counter);

    void remove(Node *rootNode, const std::string &str, int i);

    void preOrderTraversal(Node *node) const;

    void postOrderTraversal(Node *node) const;

    static bool hasNoChildren(const Node *rootNode, const std::string &str, int i) ;

    void autoCompletion(Node *rootNode, std::string str, std::vector<std::string> &out);

    Node *getLastNode(const std::string &str);

    void longestCommonPrefix(Node *rootNode, std::string &lgp, int len);
};



#endif //DATA__STRUCTURES_TRIES_H
