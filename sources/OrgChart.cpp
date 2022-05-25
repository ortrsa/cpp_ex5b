#include "OrgChart.hpp"

using namespace std;
using namespace ariel;
using std::invalid_argument;
namespace ariel{
    

    OrgChart OrgChart::add_root(string const &node_name){
        if(this->top == nullptr){
        this->top = new Node(node_name);
        }else{
            Node* temp = new Node(node_name);
           (*temp).copy_child(this->top->get_childs());
            this->top = temp;
        }

        return *this;
    };
    OrgChart OrgChart::add_sub(string const &node1, string const &node2 ){
        if(this->top == nullptr){
            throw invalid_argument("cant add this sub");
        };
        (*BFS(node1)).add_child(new Node(node2));

        
        return *this;
    };
    Iter OrgChart::begin_level_order(){
        Iter it;
        if(this->top == nullptr){
            throw invalid_argument("emtpy chart");
        };
        fill_vec(this->top, it);

        return it;


    };

    Iter OrgChart::end_level_order(){
        Iter it;
        if(this->top == nullptr){
            throw invalid_argument("emtpy chart");
        };
        fill_vec(this->top, it);
        it.set_i(it.get_all_nods().size());
        return it;

    };

    

    Iter OrgChart::begin_reverse_order(){
        Iter it;
        if(this->top == nullptr){
            throw invalid_argument("emtpy chart");
        };
        fill_vec_reverse(this->top, it);
        it.reverse_node();
        return it;
    };

    Iter OrgChart::reverse_order(){
        Iter it;
        if(this->top == nullptr){
            throw invalid_argument("emtpy chart");
        };
        fill_vec_reverse(this->top, it);
        it.reverse_node();
        it.set_i(it.get_all_nods().size());
        return it;
    };




    Iter OrgChart::begin_preorder(){
        Iter it;
        if(this->top == nullptr){
            throw invalid_argument("emtpy chart");
        };
        fill_preorder(this->top, it);
        
        return it;
    };

    Iter OrgChart::end_preorder(){
        Iter it;
        if(this->top == nullptr){
            throw invalid_argument("emtpy chart");
        };
        fill_preorder(this->top, it);
        it.set_i(it.get_all_nods().size());
        return it;
    };

    Iter OrgChart::begin(){
        Iter it;
        if(this->top == nullptr){
            throw invalid_argument("emtpy chart");
        };
        fill_vec(this->top, it);

        return it;
    };
    Iter OrgChart::end(){
        Iter it;
        if(this->top == nullptr){
            throw invalid_argument("emtpy chart");
        };
        fill_vec(this->top, it);
        it.set_i(it.get_all_nods().size());
        return it;
    };



    Node* OrgChart::BFS(string const &to_find){
       if(this->top == nullptr){
            throw invalid_argument("emtpy chart");
        };
        list<Node*> q;

        q.push_back(this->top);

        while (!q.empty())
        {
            Node* node = q.front();
            if(node->get_name() == to_find){
                return node;
            }
            q.pop_front();
            for (auto *child : (*node).get_childs())
            {
                q.push_back(child);
            }
            
        }
        throw invalid_argument("cant find father node");
        

    };

 
    void OrgChart::fill_preorder(Node *node, Iter &it){
        if (node == nullptr){
            return;
        }

        it.push_node(node);

        for (Node *child : (*node).get_childs()){
            fill_preorder(child, it);
        }
    }

    void OrgChart::fill_vec(Node *top, Iter &it){
        if(top == nullptr){
            throw invalid_argument("emtpy chart");
        };
        list<Node*> q;
        
        q.push_back(top);

        while (!q.empty())
        {
            Node* node = q.front();
            it.push_node(node);
            q.pop_front();
            for (auto *child : (*node).get_childs())
            {
                q.push_back(child);
            }
            
        }
    }
    
    void OrgChart::printtree(std::ostream &output, Node *currNode, const std::string &prefix) {
        output << currNode->get_name() << endl ;
        for (Node *child: currNode->get_childs()) {
            output << prefix; 
            string newPrefix;
            for (int i = 0; i < child->get_level(); ++i) { 
                newPrefix += "|_____  ";
            }
            printtree(output, child, newPrefix);
        }
    }

   
    std::ostream &operator<<(std::ostream &output, OrgChart &n) {
        if (n.top != nullptr) {
            n.printtree(output, n.top, "");
        }

        return output;
    }



    void OrgChart::fill_vec_reverse(Node *top, Iter &it){
        if(top == nullptr){
            throw invalid_argument("emtpy chart");
        };
        list<Node*> q;
        list<Node*> s;
        q.push_back(top);

        while (!q.empty())
        {
            Node* node = q.front();
            
            s.insert(s.begin(),node);
            
            vector<Node*> rev_it = (*node).get_childs();
            it.push_node(node);
            std::reverse(rev_it.begin(), rev_it.end());
            q.pop_front();
            for (auto *child :rev_it )
            {
                q.push_back(child);
            }
            
        }
    }

}