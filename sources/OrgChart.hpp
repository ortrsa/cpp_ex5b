#ifndef OrgChart_H
#define OrgChart_H

#include <iostream>
#include <vector>
#include "Node.hpp"
#include <bits/stdc++.h>

using std::string;
using std::vector;
using std::invalid_argument;
using std::ostream;
namespace ariel
{
    
    class Node;
    class Iter{
        private:
        vector<Node*> all_nods;
        unsigned int iter_index;

        public:
            


            Iter(){
                iter_index = 0;
            };
            
            // ptr to strinng in iterator
            string operator*(){
                return all_nods.at(iter_index)->get_name();
            };

            string *operator->(){
                return &(all_nods[iter_index]->get_name());
            };

            // increase by 1
            Iter operator++(){
                if(iter_index >= all_nods.size()){
                    throw;
                }
                
                iter_index ++;
                
                return *this;
            };
            
            friend bool operator==(const Iter &this_iter,const Iter  &other_iter){
                if(this_iter.all_nods.empty()||other_iter.all_nods.empty()){
                    throw invalid_argument("Iterators are empty");
                }
                if(this_iter.iter_index==other_iter.iter_index){
                    if(this_iter.all_nods == other_iter.all_nods){
                        return true;
                    }
                }
                return false;
            };
            friend bool operator!=(const Iter &this_iter,const Iter  &other_iter){
                return !(this_iter==other_iter);
            };

            
            void add_to_it(Node* n){all_nods.push_back(n);};
            void reset_i(){iter_index =0;};
            void set_i(unsigned int i ){iter_index =i;}
            vector<Node*> get_all_nods() const {return all_nods;};
            void reverse_node(){std::reverse(all_nods.begin(), all_nods.end());};
            void push_node(Node * n){all_nods.push_back(n);};
            friend ostream &operator << ( ostream &output, const Iter &it){
                output << (*it.all_nods[it.iter_index]).get_name();
                return(output);
            }
    };

    class OrgChart
    {
        Node *top;
    public:
        OrgChart(){
            top = nullptr;
        };

        
    
        OrgChart add_root(string const &node);
        OrgChart add_sub(string const &node1, string const &node2 );
        Node* BFS(string const &to_find);
        Node* get_top(){return top;};

        void printtree(std::ostream &output, Node *currNode, const std::string &prefix);
        static void fill_vec(Node *top, Iter &it);

        static void fill_vec_reverse(Node *top, Iter &it);
        void fill_preorder(Node *node, Iter &it);
        Iter begin_level_order();
        Iter end_level_order();
        Iter begin_reverse_order();
        Iter reverse_order();
        Iter begin_preorder();
        Iter end_preorder();
        Iter begin();
        Iter end();
        friend ostream &operator << ( ostream &output,  OrgChart &n);


    };

    
}
#endif