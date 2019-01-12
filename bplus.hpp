#ifndef BPLUS_HPP_
#define BPLUS_HPP_

#include <iostream>
#include <string>
#include "datanode.hpp"

using namespace std;

class PlusTree {
private:
    BPNode *root;
    int order;

    
    dnode *head;
    dnode *tail;

public:
    void initial(int order);

    int get_m();

    void insert_keyval(float key, string value);

    vector<string> search(float key);

    
    
    
    /*
     * Ranged search
     * Search for key such that key_start <= key <= key_end
     */
    vector<pair<float, string>> search(float st, float en);

   
    void print_key();

   
};

#endif
