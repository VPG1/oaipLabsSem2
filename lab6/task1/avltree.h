#ifndef AVLTREE_H
#define AVLTREE_H


template<typename K, typename V>
class AVLNode
{
    K key;
    V value;
    int height;

    int getBFactor(){
        int lheight = left ? left->height : 0;
        int rheight = right ? right->height : 0;

        return rheight - lheight;
    }

    void updateHeight(){
        int lheight = left ? left->height : 0;
        int rheight = right ? right->height : 0;

        height = ((lheight > rheight) ? lheight : rheight) + 1;
    }

    AVLNode *rotateRight(){
        AVLNode *p = this;
        AVLNode *q = p->left;
        p->left = q->right;
        q->right = p;

        p->updateHeight();
        q->updateHeight();

        return q;
    }
    AVLNode *rotateLeft(){
        AVLNode *q = this;
        AVLNode *p = q->right;

        q->right = p->left;
        p->left = q;

        q->updateHeight();
        p->updateHeight();

        return p;
    }

    AVLNode *balance(){
        updateHeight();
        if(getBFactor() == 2){
            if(right->getBFactor() < 0){
                right = right->rotateRight();
            }
            return rotateLeft();
        }
        else if(getBFactor() == -2){
            if(left->getBFactor() > 0){
                left = left->rotateLeft();
            }
            return rotateRight();
        }

        return this;
    }

public:
    AVLNode *left = nullptr;
    AVLNode *right = nullptr;

    AVLNode() = default;
    AVLNode(const K &key, const V &value) : key(key), value(value), height(1) {}

    AVLNode *addNode(AVLNode *node){
        if(node->key < key){
            if(left){
                left = left->addNode(node);
            }
            else{
                left = node;
            }
        }
        else{
            if(right){
                right = right->addNode(node);
            }
            else{
                right = node;
            }
        }

        return balance();
    }



    const K &getKey() const
    {
        return key;
    }

    const V &getValue() const
    {
        return value;
    }
};

#endif // AVLTREE_H
