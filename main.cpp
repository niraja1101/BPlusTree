#include <iostream>
#include <fstream>
#include "bplus.hpp"

using namespace std;

int main(int argc, char **argv) {

    string ifile = "input1.txt";
    //accept input from user
    if (argc > 1) {
       
        ifile = argv[1];
    }

    // read input file
    ifstream ip(ifile);

    // Error checking
    if (!ip) {
        
        cerr << "ATTENTION :" << ifile << "Could not read file" << endl;
        exit(1);
    }

    //prepare output file
    ofstream outfile("output_file.txt");
    // error checking
    if (!outfile) {
        
        cerr << "ATTENTION : Could not write to output file" << endl;
        exit(1);
    }

    //get order of tree
    string m;
    getline(ip, m);
   
    cout << "order of tree as read from input file : " << m << endl;
    auto tree = new PlusTree();
    tree->initial(atoi(m.c_str()));

    int current = 0;
    
   
    while (ip) {
        if (current == 0) {
            current++;
        } else {
            
            string inp_string;
            ip >> inp_string;
//            string parsed_input[3];
            string sep1 = "(";
            string sep2 = ",";
            string sep3 = ")";

            size_t place = inp_string.find(sep1);
            cout << "pos :delimiter1 " << place << endl;

            /*After parsing - 3 diffrent values stored in array - Insert or Search, key or key1, value or key2,
             key2 value not compulsory for exact search
             key 2 must have a value in rangesearch
             * 
             */
            string operation = inp_string.substr(0, place);  // operation type - Insert/Search
            cout << "Operation to be done " << operation << endl;
            inp_string.erase(0, place + sep1.length());
            cout << "ip2 : " << inp_string << endl;

            string input1, input2; 

            
            
            
            
            // Searching can take one or two keys as input, array is initiliazed accordingly
            if (operation == "Search") {
                
                if (inp_string.find(sep2) > (size_t) 1000) {
                    place = inp_string.find(sep3);
                    input1 = inp_string.substr(0, place);
                    cout << "Key for exact search : " << input1 << endl;
                    inp_string.erase(0, place + sep3.length());
                } else {
                    // range search
                    cout << " Key for range search : " << endl;
                    place = inp_string.find(sep2);
                    cout << "position : " << place << endl;
                    input1 = inp_string.substr(0, place);
                    cout << "2 : " << input1 << endl;
                    inp_string.erase(0, place + sep2.length());
                    cout << "ip3 : " << inp_string << endl;

                    place = inp_string.find(sep3);
                    input2 = inp_string.substr(0, place);
                    cout << "3 : " << input2 << endl;
                    inp_string.erase(0, place + sep3.length());
                }

                float kk1 = atof(input1.c_str());
                if (input2 == "") {
                    vector<string> val = tree->search(kk1);
                    if (val.empty()) {
                        outfile << "NULL" << endl;
                    } else {
                        for (vector<string>::const_iterator i = val.begin(); i < val.end(); ++i) {
                            outfile << *i;
                            if (i < val.end() - 1)
                                outfile << ",";
                            else
                                outfile << endl;
                            cout << "SEARCH VALUES: " << *i << endl;
                        }
                    }
                } else {
                    float kk2 = atof(input2.c_str());
                    vector<pair<float, string>> val_Data = tree->search(kk1, kk2);
                    if (val_Data.empty()) {
                        outfile << "NULL" << endl;
                    } else {
                        for (vector<pair<float, string>>::const_iterator i = val_Data.begin();
                             i < val_Data.end(); ++i) {
                            outfile << "(" << val_Data[i - val_Data.begin()].first << "," << val_Data[i - val_Data.begin()].second
                                 << ")";
                            if (i < val_Data.end() - 1)
                                outfile << ",";
                            else
                                outfile << endl;
                            cout << "SEARCH VALUES: " << val_Data[i - val_Data.begin()].first << ", "
                                      << val_Data[i - val_Data.begin()].second << endl;
                        }
                    }

                }

            } else {
                place = inp_string.find(sep2);
                cout << "position : " << place << endl;
                input1 = inp_string.substr(0, place);
                cout << "2 : " << input1 << endl;
                inp_string.erase(0, place + sep2.length());
                cout << "ip3 : " << inp_string << endl;

                place = inp_string.find(sep3);
                input2 = inp_string.substr(0, place);
                cout << "3 : " << input2 << endl;
                inp_string.erase(0, place + sep3.length());

                
                float key = atof(input1.c_str());
                cout << "Value to be inserted : " << key << endl;
                tree->insert_keyval(key, input2);
//                
            }

            cout << "Final string " << inp_string << endl;
        }
    }

    tree->print_key();

    return 0;
}
