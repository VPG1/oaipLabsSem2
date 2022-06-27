#ifndef MY_BITSET_H
#define MY_BITSET_H

#include <cstddef>
#include <string>


template<size_t N>
class bitset{
//    unsigned char *arr = new unsigned char[(N + 7) / 8];
    unsigned char arr[(N + 7) / 8];

public:

    class reference{
        friend class bitset;

        unsigned char &word;
        size_t nBit;

        reference(unsigned char &word, size_t nBit) : word(word), nBit(nBit){}

    public:
        reference &operator=(bool x){
            x ? word |= (1u << nBit) : word &= ~(1u << nBit);
            return *this;
        }
        operator bool(){
            return (word & (1u << nBit)) != 0;
        }
    };

    bitset(){
//        memset(arr, 0, (N + 7) / 8);
    };

    bool operator[](size_t pos) const{
        return (arr[pos / 8] & (1u << (pos % 8))) != 0;
    }

    reference operator[](size_t pos){
        return reference(arr[N / 8], pos % 8);
    }

    bool all() const{
        for(int i = 0; i < N; ++i){
            if((arr[i / 8] & (1u << (i % 8))) == 0){
                return false;
            }
        }
        return true;
    }

    bool any() const{
        for(int i = 0; i < N; ++i){
            if((arr[i / 8] & (1u << (i % 8))) != 0){
                return true;
            }
        }
        return false;
    }

    bool none() const{
        for(int i = 0; i < N; ++i){
            if((arr[i / 8] & (1u << (i % 8))) != 0){
                return false;
            }
        }
        return true;
    }

    size_t count() const{
        size_t res = 0;
        for(int i = 0; i < N; ++i){
            if((arr[i / 8] & (1u << (i % 8))) != 0){
                ++res;
            }
        }
        return res;
    }

    bitset &set(){
        for(int i = 0; i < N; ++i){
            arr[i / 8] |= (1u << (i % 8));
        }

        return *this;
    }
    bitset &set(size_t pos){
        arr[pos / 8] |= (1u << (pos % 8));
        return *this;
    }

    bitset &reset(){
        for(int i = 0; i < N; ++i){
            arr[i / 8] &= ~(1 << (i % 8));
        }

        return *this;
    }

    bitset &reset(size_t pos){
        arr[pos / 8] &= ~(1u << (pos % 8));
        return *this;
    }

    bitset &flip(){
        for(int i = 0; i < N; ++i){
            arr[i / 8] ^= (1u << (i % 8));
        }
        return *this;
    }

    bitset &flip(size_t pos){
        arr[pos / 8] ^= (1u << (pos % 8));
        return *this;
    }

    bool test(size_t pos) const{
        return (arr[pos / 8] & (1u << (pos % 8))) != 0;
    }


    std::string to_string(char zero = '0', char one = '1') const{
        std::string res;
        for(int i = 0; i < N; ++i){
            res += test(N - i - 1) ? one : zero;
        }
        return res;
    }

    unsigned long long to_ullong() const{
        unsigned long long res = 0;

        for(int i = 0; i < (N + 7) / 8; ++i){
            res |= arr[i];
        }

        return res;
    }

    unsigned long to_ulong() const{
        unsigned long res = 0;

        for(int i = 0; i < (N + 7) / 8; ++i){
            res |= arr[i];
        }

        return res;
    }

    size_t size() const{
        return N;
    }

    friend bitset operator~(const bitset &bts){
        bitset res;
        for(int i = 0; i < (N + 7) / 8; ++i){
            res.arr[i] = ~bts.arr[i];
        }
        return res;
    }

    friend bitset operator&(const bitset &lBts, const bitset &rBts){
        bitset res;
        for(int i = 0; i < (N + 7) / 8; ++i){
            res.arr[i] = lBts.arr[i] & rBts.arr[i];
        }
        return res;
    }

    friend bitset operator|(const bitset &lBts, const bitset &rBts){
        bitset res;
        for(int i = 0; i < (N + 7) / 8; ++i){
            res.arr[i] = lBts.arr[i] | rBts.arr[i];
        }
        return res;
    }
};
#endif // MY_BITSET_H
