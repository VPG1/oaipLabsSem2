#ifndef MY_UNORDERED_MAP_H
#define MY_UNORDERED_MAP_H
#include <utility>
#include <list>

template<typename K, typename V, typename Hash = std::hash<K>>
class unordered_map{
    using value_type = std::pair<K, V>;

    struct Node{
        value_type kv;
        size_t hash;
    };

    std::list<Node> *buckets = nullptr;
    size_t size = 0;
    size_t bucketCount = 0;

    static constexpr double maxLoadFactor = 1.0;

    size_t hashing(const K &key){
        return Hash()(key) % bucketCount;
    }

public:

    unordered_map() : buckets(new std::list<Node>[bucketCount]){}

    void insert(const value_type &kv){
        if(bucketCount == 0){
            rehash(2);
        }
        else if((size + 1) / bucketCount >= maxLoadFactor){
            rehash(2 * bucketCount + 1);
        }

        size_t hash = hashing(kv.first);

        if(!buckets[hash].empty()){
            for(auto it = buckets[hash].begin(); it != buckets[hash].end(); ++it){
                if(it->kv.first == kv.first){
                    return;
                }
            }
            buckets[hash].push_front({kv, hash});
            ++size;
        }
        else{
            buckets[hash].push_front({kv, hash});
            ++size;
        }
    }

    void erase(const K &key){
        assert(buckets);

        size_t hash = hashing(key);

        for(auto it = buckets[hash].begin(); it != buckets[hash].end(); ++it){
            if(it->kv.first == key){
                buckets[hash].erase(it);
                --size;
                break;
            }
        }
    }

    bool contains(const K &key){
        if(bucketCount == 0 || size == 0){
            return false;
        }
        size_t hash = hashing(key);

        for(auto it = buckets[hash].begin(); it != buckets[hash].end(); ++it){
            if(it->kv.first == key){
                return true;
            }
        }
        return false;
    }

    void rehash(size_t count){
        std::list<Node> *newBuckets = new std::list<Node>[count];

        for(int i = 0; i < bucketCount; ++i){
            for(auto it = buckets[i].begin(); it != buckets[i].end(); ++it){
                size_t newHash = hashing(it->kv.first);

                it->hash = newHash;
                newBuckets[newHash].push_front(*it);
            }
        }

        delete[] buckets;
        buckets = newBuckets;
        bucketCount = count;
    }

    void clear(){
        for(int i = 0; i < bucketCount; ++i){
            while(!buckets[i].empty()){
                buckets[i].pop_front();
            }
        }
        size = 0;
    }

    size_t getBucketCount(){
        return bucketCount;
    }

    V &operator[](const K &key){
        if(bucketCount == 0){
            rehash(2);
        }
        else if((size + 1) / bucketCount >= maxLoadFactor){
            rehash(2 * bucketCount + 1);
        }


        size_t hash = hashing(key);

        for(auto it = buckets[hash].begin(); it != buckets[hash].end(); ++it){
            if(it->kv.first == key){
                return it->kv.second;
            }
        }

        buckets[hash].push_front({{key, V()}, hash});
        return buckets[hash].begin()->kv.second;
    }

//    V operator[](const K &key) const{

//    }

//    void print(){
//        for(int i = 0; i < bucketCount; ++i){
//            for(auto it = buckets[i].begin(); it != buckets[i].end(); ++it){
//                 std::cout << it->kv.first << " " << it->kv.second << " ";
//            }
//        }
//    }

    std::vector<value_type> getElements(){
        std::vector<value_type> res;

        for(int i = 0; i < bucketCount; ++i){
            for(auto it = buckets[i].begin(); it != buckets[i].end(); ++it){
                res.push_back(it->kv);
            }
        }

        return res;
    }
};

#endif // MY_UNORDERED_MAP_H
