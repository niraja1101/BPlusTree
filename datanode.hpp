#ifndef NODE_HPP_
#define NODE_HPP_

#include <string>
#include <vector>
#include <cmath>
#include <utility>
#include <cfloat>
#include <iostream>

using namespace std;


// Superclass InternalNode can point to any kind of Node
class BPNode {
protected:
    
    vector<float> keys = {FLT_MAX};
    BPNode *par = nullptr;

public:
    virtual string find_type() = 0;

    virtual BPNode *lookPar() { return par; }

    virtual void set_parent(BPNode *node) { par = node; }

   
    int num_keys() { return keys.size() - 1; }

    
    virtual void print_all_keys() {
        for (vector<float>::const_iterator ter = keys.begin(), j = --keys.end(); ter < j; ++ter) {
            cout << *ter << " ";
        }
        cout << endl;

    }

    friend class PlusTree;
};

class Node_internal : public BPNode {
protected:
    vector<BPNode *> child;
    Node_internal *par = nullptr;

public:
    virtual string find_type() { return "INTERNAL"; }

   
    
    
    // Key insertion at this index
    // child pointer added at this index
    int insert_K(float key) {
        for (vector<float>::iterator i = keys.begin(); i < keys.end(); ++i) {
            if (key < *i) {
                
                i = keys.insert(i, key);
                return i - keys.begin();
            }
        }
    }

    
    
    
    // merge this node with an internal node which was formed as a result of split
  
    void merge(pair<Node_internal *, BPNode *> res_Spl) {
        auto mw = res_Spl.first;
        auto ich = res_Spl.second;

        int k_pos = insert_K(*mw->keys.begin());
        insert_child(k_pos + 1, ich);
        ich->set_parent(this);
    }

    pair<Node_internal *, BPNode *> brk(int order) {
       
        int nodeLeft = (keys.begin() + (ceil(float(order) / 2) - 1)) - keys.begin();

 
        Node_internal *nR = new Node_internal();
        nR->keys = vector<float>(keys.begin() + nodeLeft + 1, keys.end());
        nR->child = vector<BPNode *>(child.begin() + nodeLeft + 1, child.end());

       
        for (auto child: nR->child) {
            child->set_parent(nR);
        }

        
        Node_internal *mid_N = new Node_internal();
        mid_N->insert_K(*(keys.begin() + nodeLeft));

       
        keys.resize(nodeLeft);
        keys.push_back(FLT_MAX);
        child.resize(nodeLeft + 1);

        
        nR->par = mid_N;

        return pair<Node_internal *, Node_internal *>(mid_N, nR);
    }

    
    void insert_child(int pos, BPNode *child_ptr) {
        child.insert(child.begin() + pos, child_ptr);
    }

    friend class PlusTree;
};

class dnode : public BPNode {
private:
    vector<string> values = {"END_MARKER"};
    dnode *left = nullptr;
    dnode *right = nullptr;

public:
    virtual string find_type() { return "LEAFNODE"; }

    virtual void print_all_keys() override {
        for (vector<float>::const_iterator i = keys.begin(), j = --keys.end(); i < j; ++i) {
            cout << "Key Value Pair: " << *i << ",  " << values.at(i - keys.begin()) << endl;
        }
        cout << endl;

    }

    void Insert(float key, string value) {
        for (vector<float>::iterator i = keys.begin(); i < keys.end(); ++i) {
            if (key < *i) {
                
                i = keys.insert(i, key);
                
                // insert value at ith position
                values.insert(values.begin() + (i - keys.begin()), value);
               
                break;
            }
        }
    }

    
    pair<Node_internal *, BPNode *> split(int order) {
       
       
        vector<float>::iterator oke = keys.begin() + ceil(float(order) / 2) - 2;
        vector<string>::iterator getio = values.begin() + ceil(float(order) / 2) - 2;

        
       
        
        //create new Data node
        dnode *ndNode = new dnode();
        ndNode->keys = vector<float>(oke + 1, keys.end());
        ndNode->values = vector<string>(getio + 1, values.end());

      
        keys.resize(oke - keys.begin() + 1);
        keys.push_back(FLT_MAX);
        values.resize(oke - keys.begin() + 1);
        values.push_back("END_MARKER");

        // update doubly-linked-list
        ndNode->right = right;
        ndNode->left = this;
        right = ndNode;

      
        Node_internal *new_in = new Node_internal();
        new_in->insert_K(*ndNode->keys.begin());

        return pair<Node_internal *, dnode *>(new_in, ndNode);
    }

    

    friend class PlusTree;

    friend class Node_internal;
};

#endif
