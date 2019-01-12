#include <string>
#include <queue>
#include <iostream>

#include "bplus.hpp"

using namespace std;

void PlusTree::initial(int m) {
   
    
    // initialise root as an empty (with FLT_MAX as the only key) data node
    root = new dnode();
    tail = head = static_cast<dnode *>(root);
    
    // For Bplustree an InternalNode have at most m children
    // InternalNodes and DataNodes have at most (m - 1) no. of keys
    this->order = m;

    
    
    
}   

int PlusTree::get_m() {
    return order;
}

void PlusTree::insert_keyval(float key_insert, string data_Val) {
    BPNode *cnode = root;
   
    // find a DataNode
    while (cnode->find_type().compare("LEAFNODE") != 0) {
        cout << "Found internal node" << endl;
        Node_internal *ninode = static_cast<Node_internal *>(cnode);
        for (vector<float>::iterator i = ninode->keys.begin();
             i < ninode->keys.end(); ++i) {
            if (key_insert < *i) {
                cnode = ninode->child.at(i - ninode->keys.begin());
                cout << "Shifted to child " << i - ninode->keys.begin() << endl;
                break;
            }
        }
    }
    
    
    
    
    cout << "Inserting in DataNode" << endl;
    static_cast<dnode *>(cnode)->Insert(key_insert, data_Val);
    

    if (cnode->num_keys() == order) {
        
        auto slp_result = static_cast<dnode *>(cnode)->split(order);
        

        Node_internal *CParent = static_cast<Node_internal *>(cnode->par);
        bool root_need= true;
        while (nullptr != CParent) {
            CParent->merge(slp_result);
           
            
            // Splitting the parent if combine caused it to have m children
           
            if (CParent->num_keys() == order) {
                slp_result = CParent->brk(order);
                
                cnode = CParent;
                CParent = static_cast<Node_internal *>(cnode->lookPar());
            } else {
                root_need = false;
                break;
            }
        }

        if (root_need) {
            Node_internal *rootN = slp_result.first;
            auto nChild = slp_result.second;
            
            rootN->insert_child(0, cnode); 
            rootN->insert_child(1, nChild);
            cnode->set_parent(rootN);
            nChild->set_parent(rootN);
            root = rootN;
        }
        
    }
}

vector<string> PlusTree::search(float key) {
    BPNode *cnode = root;
    vector<string> aos;
   
    while (cnode->find_type().compare("LEAFNODE") != 0) {
        cout << "Entered an internal node" << endl;
        
        
        Node_internal *ni_node = static_cast<Node_internal *>(cnode);
        for (vector<float>::iterator i = ni_node->keys.begin();
             i < ni_node->keys.end(); ++i) {
            
            if (key < *i) {
                cnode = ni_node->child.at(i - ni_node->keys.begin());
                cout << "Shifted to the child at " << i - ni_node->keys.begin() << endl;
                break;
            }
        }
    }

   
    dnode *cdnode = static_cast<dnode *>(cnode);
    dnode *cdleft = cdnode->left;


    while (cdleft != nullptr) {
        for (vector<float>::const_iterator i = cdleft->keys.begin();
             i < cdleft->keys.end(); ++i) {
            if (key == *i) {
                aos.push_back(cdleft->values.at(i - cdleft->keys.begin()));
            }
        }
        cdleft = cdleft->left;
    }

    while (cdnode != nullptr) {
        for (vector<float>::const_iterator i = cdnode->keys.begin(); i < cdnode->keys.end(); ++i) {
            if (key == *i) {
                aos.push_back(cdnode->values.at(i - cdnode->keys.begin()));
            }
        }
        cdnode = cdnode->right;
    }

    return aos;
}









/*
 * Ranged search
 *
 * Search for key such that key_start <= key <= key_end
 */
vector<pair<float, string>> PlusTree::search(float key1, float key2) {
    cout << "In RANGE search method:: " << endl;
    BPNode *cNode = root;
    pair<float, string> range_val;
    vector<pair<float, string>> out_Arr;
    
    while (cNode->find_type().compare("LEAFNODE") != 0) {
       
        Node_internal *niner = static_cast<Node_internal *>(cNode);
        for (vector<float>::iterator i = niner->keys.begin();
             i < niner->keys.end(); ++i) {
            
            if (key1 < *i) {
                cNode = niner->child.at(i - niner->keys.begin());
                cout << "Shifted to the child at " << i - niner->keys.begin() << endl;
                break;
            }
        }
    }

    
    dnode *dataC = static_cast<dnode *>(cNode);

    
    while (dataC != nullptr) {
        for (vector<float>::const_iterator i = dataC->keys.begin(); i < dataC->keys.end(); ++i) {
            if ((*i >= key1) && (*i <= key2)) {
                out_Arr.push_back(
                        make_pair(*i, dataC->values.at(i - dataC->keys.begin())));
            }
        }
        dataC = dataC->right;
    }
    return out_Arr;
}




void PlusTree::print_key() {
    for (dnode *d1 = head; d1 != nullptr; d1 = d1->right) {
        d1->print_all_keys();
    }
}
