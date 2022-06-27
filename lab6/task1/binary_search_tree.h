#ifndef BST_H
#define BST_H

#include <cstddef>
#include <utility>
#include <optional>
#include <iostream>
#include <vector>
#include <QListWidget>
#include "avltree.h"

template<typename K, typename V>
struct BinaryNode{
    K key;
    V value;
    BinaryNode *left;
    BinaryNode *right;
};


template <typename K, typename V>
class BinarySearchTreeMethod{


    static void sTraversePreorder(BinaryNode<K, V> *node, std::vector<V> &v){
        v.push_back(node->value);

        if(node->left){
            sTraversePreorder(node->left, v);
        }
        if(node->right){
            sTraversePreorder(node->right, v);
        }
    }

    static void sTraverseInorder(BinaryNode<K, V> *node, std::vector<V> &v){
        if(node->left){
            sTraverseInorder(node->left, v);
        }

        v.push_back(node->value);

        if(node->right){
            sTraverseInorder(node->right, v);
        }
    }

    static void sTraversePostorder(BinaryNode<K, V> *node, std::vector<V> &v){
        if(node->left){
            sTraversePostorder(node->left, v);
        }
        if(node->right){
            sTraversePostorder(node->right, v);
        }

        v.push_back(node->value);
    }

public:
    static BinaryNode<K, V> *arrayToBTS(const std::vector<V> &arr, int first, int last){
        if(first > last){
            return nullptr;
        }
        else if(first == last){
            return new BinaryNode<K, V>{first, arr[first], nullptr, nullptr};
        }

        return new BinaryNode<K, V>{(first + last) / 2, arr[(first + last) / 2],
                arrayToBTS(arr, first,(first + last) / 2 - 1),
                arrayToBTS(arr, (first + last) / 2 + 1, last)};
    }

    static void insert(const K &key, const V &value, BinaryNode<K, V> *&node){
        if(!node){
            node = new BinaryNode<K, V>{key, value, nullptr, nullptr};
            return;
        }

        if(key < node->key ){
            if(node->left){
                insert(key, value, node->left);
            }
            else{
                node->left = new BinaryNode<K, V>{key, value, nullptr, nullptr};
            }
        }
        else if(key > node->key){
            if(node->right){
                insert(key, value, node->right);
            }
            else{
                node->right = new BinaryNode<K, V>{key, value, nullptr, nullptr};
            }
        }
    }

    static std::optional<V> find(const K &key, BinaryNode<K, V> *node){
        if(node == nullptr){
            return std::nullopt;
        }
        if(node->key == key){
            return node->value;
        }

        if(key < node->key){
            return find(key, node->left);
        }
        else{
            return find(key, node->right);
        }
    }



    static void erase(const K &key, BinaryNode<K, V> *&node){
        if(node == nullptr){
            return;
        }
        else if(key < node->key){
            erase(key, node->left);
        }
        else if(key > node->key){
            erase(key, node->right);
        }
        else{
            if(!node->left && !node->right){
                delete node;
                node = nullptr;
            }
            else if(!node->left){
                BinaryNode<K, V> *temp = node;
                node = node->right;
                delete temp;
            }
            else if(!node->right){
                BinaryNode<K, V> *temp = node;
                node = node->left;
                delete temp;
            }
            else{
                BinaryNode<K, V> *&temp = toLeftestChild(node->right);

                node->key = temp->key;
                node->value = temp->value;

                erase(temp->key, temp);
            }
        }
    }



    static std::vector<V> traversePreorder(BinaryNode<K, V> *node){
        std::vector<V> v;
        sTraversePreorder(node, v);
        return v;
    }




    static std::vector<V> traverseInorder(BinaryNode<K, V> *node){
        std::vector<V> v;
        sTraverseInorder(node, v);
        return v;
    }


    static std::vector<V> traversePostorder(BinaryNode<K, V> *node){
        std::vector<V> v;
        sTraversePostorder(node, v);
        return v;
    }



    static BinaryNode<K, V> *balance(BinaryNode<K, V> *root){
        AVLNode<K, V> *avlRoot = nullptr;
        creatAVLTree(root, avlRoot);
        return convertFromAVLTree(avlRoot);
    }

    static void creatAVLTree(BinaryNode<K, V> *root, AVLNode<K, V> *&avlRoot){
        if(!avlRoot){
            avlRoot = new AVLNode<K, V>(root->key, root->value);
        }
        else{
            auto p = new AVLNode<K, V>(root->key, root->value);
            avlRoot = avlRoot->addNode(p);
        }

        if(root->left){
            creatAVLTree(root->left, avlRoot);
        }
        if(root->right){
            creatAVLTree(root->right, avlRoot);
        }
    }

    static BinaryNode<K, V> *convertFromAVLTree(AVLNode<K, V> *avlRoot){
        if(!avlRoot) return nullptr;
        return new BinaryNode<K, V>{avlRoot->getKey(), avlRoot->getValue(), convertFromAVLTree(avlRoot->left), convertFromAVLTree(avlRoot->right)};
    }


    static void clear(BinaryNode<K, V> *&root){
        if(root){
            clear(root->left);
            clear(root->right);

            delete root;
            root = nullptr;
        }
    }

    static BinaryNode<K, V> *&toLeftestChild(BinaryNode<K, V> *&node){
        if(!node->left)
            return node;

        toLeftestChild(node->left);
    }
    static BinaryNode<K, V> *&toRightestChild(BinaryNode<K, V> *&node){
        if(!node->right)
            return node;
        toRightestChild(node->right);
    }

};

#endif // BST_H
