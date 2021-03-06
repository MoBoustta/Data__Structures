//
// Created by one for all on 16/09/2020.
//

#include "Exercises.h"

void Exercises::reverse(std::string &input) {
    std::stack<char> stackOfChars;
    for (char & i : input)
        stackOfChars.push(i);
    std::size_t i {};
    while (!stackOfChars.empty()) {
        input[i++] = stackOfChars.top();
        stackOfChars.pop();
    }
}

void Exercises::queueReverse(std::queue<int> &queue) {
    std::stack<int> stackOfInts;
    while(!queue.empty()) {
        stackOfInts.push(queue.front());
        queue.pop();
    }
    while (!stackOfInts.empty()) {
        queue.push(stackOfInts.top());
        stackOfInts.pop();
    }
}

bool Exercises::isBalanced(std::string &str) {
    std::string closingSymbol(")}>]");
    std::stack<char> stack;
    for(char& c : str){
        if (c == '(' || c == '[' || c == '<' || c == '(') stack.push(c);
        else if (str.find(c) != std::string::npos){
            auto current = stack.top();
            stack.pop();
            if (current - c == 1 || current - c == 2) continue;
            else return false;
        }
    }
    return true;
}

std::queue<int> Exercises::queueReversKElements(std::queue<int> &queue, std::size_t k) {
    if (queue.empty() || k > queue.size() || k < 0) throw std::runtime_error{ "Invalid operation" };
    std::stack<int> stack;
    std::queue<int> outQueue;
    int i = k;
    while (i--) {
        stack.push(queue.front());
        queue.pop();
    }
    while (!stack.empty()){
        outQueue.push(stack.top());
        stack.pop();
    }
    while (!queue.empty()){
        outQueue.push(queue.front());
        queue.pop();
    }
    return outQueue;
}

char Exercises::findFirstNonRepeatedCharacter(const std::string &string) {
    std::map<char, std::size_t> mapOfChars;
    for (std::size_t i{}; i < string.length() ; ++i)
        mapOfChars[string[i]] = mapOfChars[string[i]] + 1;
    for (char i : string)
        if (mapOfChars[i] == 1) return string[i];
    return '\0';
}

char Exercises::findFirstRepeatedCharacter(const std::string &string){
    std::set<char> setOfChars;
    for (const char ch : string){
        if (setOfChars.count(ch) == 1) return ch;
        setOfChars.insert(ch);
    }
    return '\0';
}

template<size_t N>
int Exercises::mostFrequent(int (&input)[N]) {
    std::map<int, int> map;
    auto comp = [](const std::pair<int, int>& lhs, const std::pair<int, int>& rhs){ return lhs.second > rhs.second; };
    for (std::size_t i{}; i < N; ++i)
        map[input[i]] = map[input[i]] + 1;
    std::vector<std::pair<int, int>> vectorOfPairs(map.begin(), map.end());
    std::sort(vectorOfPairs.begin(), vectorOfPairs.end(), comp);
    return vectorOfPairs[0].first;
}

int Exercises::countPairsWithDiff(std::vector<int>& nums, int k) {
    if (k < 0 || nums.empty()) return 0;
    std::map<int, int> mapOfDiffPairs;
    int counter {};
    for (int & num : nums)
        mapOfDiffPairs[num] = mapOfDiffPairs[num] + 1;
    for (auto& itr : mapOfDiffPairs) {
        if (k == 0) {
            if (mapOfDiffPairs[itr.first] >= 2) counter++;
        }
        else if (mapOfDiffPairs.count(itr.first + k)) counter++;
    }
    return counter;
}

std::vector<int> Exercises::twoSum(std::vector<int>& nums, int target) {
    std::map<int , int> map;
    auto diff = 0;
    for (int i = 0; i < nums.size(); ++i) {
        diff = target - nums[i];
        if (map.count(diff)) return std::vector<int> {map[diff], i};
        map[nums[i]] = i;
    }
    throw std::runtime_error { "No such element" };
}


