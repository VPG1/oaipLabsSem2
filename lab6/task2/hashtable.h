#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stack>
#include <string>
#include <optional>
#include <vector>

class HashTable
{
    std::stack<std::pair<int, std::string>> *table;
    int size; // размер массива
    int count = 0; // кол-во элементов
public:
    HashTable(int size = 100);

    int hashFunc(int key);

    void insert(int key, const std::string &value);

    std::optional<std::string> find(int key);

    void erase(int key);

    std::vector<std::string> hashTableView();

    std::optional<std::string> findElementWithLargestKey();
};

#endif // HASHTABLE_H
