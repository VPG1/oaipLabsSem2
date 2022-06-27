#include "hashtable.h"


HashTable::HashTable(int size) : size(size){
    table = new std::stack<std::pair<int, std::string>>[size];
}

int HashTable::hashFunc(int key){
    return std::abs(key % size);
}

void HashTable::insert(int key, const std::string &value){
    if(find(key).has_value()) return;

    int h = hashFunc(key);
    table[h].push({key, value});

    ++count;
}

std::optional<std::string> HashTable::find(int key){
    int h = hashFunc(key);

    std::stack<std::pair<int, std::string>> temp = table[h];
    while(true){
        if(temp.empty()){
            return std::nullopt;
        }
        else if(temp.top().first == key){
            return temp.top().second;
        }

        temp.pop();
    }
}

void HashTable::erase(int key){
    int h = hashFunc(key);

    std::stack<std::pair<int, std::string>> temp;
    while(true){
        if(table[h].empty()){
            break;
        }
        else if(table[h].top().first == key){
            table[h].pop();
            --count;
            break;
        }
        temp.push(table[h].top());
        table[h].pop();
    }

    while(!temp.empty()){
        table[h].push(temp.top());
        temp.pop();
    }
}

std::vector<std::string> HashTable::hashTableView()
{
    std::vector<std::string> view;
    for(int i = 0; i < size; ++i){
        if(!table[i].empty()){
            std::stack<std::pair<int, std::string>> temp = table[i];
            std::string viewString;
            while(!temp.empty()){
                viewString += "key: " + std::to_string(temp.top().first) + " data: " + temp.top().second + "\t";
                temp.pop();
            }
            view.push_back(viewString);
        }
    }

    return view;
}

std::optional<std::string> HashTable::findElementWithLargestKey()
{
    int key = INT_MIN;
    std::optional<std::string> data = std::nullopt;
    for(int i = 0; i < size; ++i){
        std::stack<std::pair<int, std::string>> temp = table[i];
        while(true){
            if(temp.empty()){
                break;
            }
            else if(temp.top().first >= key){
                key = temp.top().first;
                data = temp.top().second;
            }
            temp.pop();
        }
    }


    return data;
}
