//
//  main.cpp
//  avl_tree
//
//  Created by Vidush Jindal on 01/06/24.
//

#include <iostream>
#include <cstdio>
#include <fstream>
#include <time.h>

using namespace std;

enum class CRT{
    before,
    after,
    match,
};

void print_CRT(CRT crt){
    switch (crt){
        case (CRT::before):{
            cout<<"before"<<endl;
        }break;
        case (CRT::after):{
            cout<<"after"<<endl;
        }break;
        case (CRT::match):{
            cout<<"match"<<endl;
        }break;
    }
}

struct Node{
    double data=0;
    Node* left;
    Node* right;
    int height=0;
    
};

int get_height(auto node){
    if (not node) return 0;
    else return node->height;
}

void update(auto &node){
    node->height=max(get_height(node->left), get_height(node->right))+1;
}


void rr(auto &node){
    auto temp= node->left;
    node->left=temp->right;
    temp->right=node;
    update(node);
    update(temp);
    
    node=temp;
    
}

void ll(auto &node){
    auto temp=node->right;
    node->right=temp->left;
    temp->left=node;
    update(node);
    update(temp);
    
    node=temp;
}


void balance(Node* &node){
    
    int lh=get_height(node->left);
    int rh=get_height(node->right);
    
    if (lh-rh >1){

        if (get_height(node->left->left)<get_height(node->left->right)){
            ll(node->left);
        }
        rr(node);
    }
    
    else if (rh-lh >1){

        if (get_height(node->right->left)>get_height(node->right->right)){
            rr(node->right);
        }
        ll(node);
    }
    
}



bool insert(double key, Node* &node){
    
    bool is_present;
    
    if (not node){
        Node* new_node= new Node();
        
        new_node->data=key;
        new_node->height=1;
    
        node=new_node;
        is_present=false;
    }
    
    else {
        CRT cr;
        if (key<node->data) cr=CRT::before;
        else if (key>node->data) cr=CRT::after;
        else cr=CRT::match;
        
        if (cr==CRT::before){
            is_present= insert(key, node->left);
        }
        else if (cr==CRT::after){
            is_present=insert(key, node->right);}
        else {
            is_present= true;
        }
    }
    
    if (is_present==false){
        update(node);
        if (not (node->height<3) ){
            balance(node);
        }
    }
    
    return is_present;
    
}

bool del(double key, Node* &node){ //node is passed by reference and is the root in first call, key is to be found
    bool found;
    CRT cr;
    
    if (not node) return false;
    if (key<node->data) cr=CRT::before;
    else if (key>node->data) cr=CRT::after;
    else cr=CRT::match;
    
    if (cr==CRT::before){ found= del(key, node->left) ;}
    else if (cr==CRT::after){ found= del(key, node->right); }
    else { //cr==CRT::match
        if (not (node->left)){ node=node->right;}
        else if (not (node->right)) {node=node->left;}
        else {
            Node* temp=node->right;
            while (temp->left){
                temp=temp->left;
            }
            node->data= temp->data;
            del(temp->data, node->right);
        }
        found= true;
    }
    
    if (found) {
        if (node){
            update(node);
            if (not (node->height<3) ){
                balance(node);}
        }
    }
    
    return found;
    
}

void print_node(auto node){
    if (not node) {cout<<"NO Node\n";return;}
    printf("Data- %lf, Height- %d\n", node->data, node->height);
}

Node* pop_first(auto &node){
    if (not node) return 0;
    Node* to_return;
    if (node->left){
        to_return=pop_first(node->left);
        balance(node);
        update(node);
    }
    else {
        to_return=node;
        node=0;
    }
    
    return to_return;
    
   
        
}


Node* search_succ(double key, Node* answer, auto root){
    CRT cr;
    
    if (not root) return answer;
    
    if (key<root->data) cr=CRT::before;
    else if (key>root->data) cr=CRT::after;
    else cr=CRT::match;
    
    if (cr==CRT::before){
        return search_succ(key, root, root->left );
    }
    else {
        return search_succ(key, answer, root->right);
    }
    
    
}

Node* search_pred(double key, Node* answer, Node* root){
    CRT cr;
    
    if (not root) return answer;
    
    if (key<root->data) cr=CRT::before;
    else if (key> root->data) cr=CRT::after;
    else cr=CRT::match;
    
    if (cr==CRT::after){
        return search_pred(key, root ,root->right );
    }
    else {
        return search_pred(key, answer, root->left);
    }
    
}
int main() {
    Node* root=0;
    

    ifstream fin("/Users/teo/Desktop/Algorithms_In_CPP/avl_tree/numbers.txt");
//    ofstream fout("/Users/teo/Desktop/Algorithms_In_CPP/avl_tree/output.txt");
//
    clock_t start= clock();
    double x;
    
    while (fin){
        fin>>x;
        
        insert(x, root);
    }
    
    clock_t end=clock();
    
    double time=(double) (end-start) /CLOCKS_PER_SEC;
    
    cout<<"Time elapsed- "<<time<<"s."<<endl;

    print_node(root);
    
    fin.close();
    
    start= clock();
    
    print_node(pop_first(root));
    cout<<endl;

    print_node(search_pred(1, 0, root));
    print_node(search_succ(42.036781, 0, root));
    cout<<endl;
    
    fin.open("/Users/teo/Desktop/Algorithms_In_CPP/avl_tree/numbers.txt");
   
    while (fin){
        fin>>x;
    
        del(x, root);
        
    }
    
    end=clock();
    
    time=(double) (end-start) /CLOCKS_PER_SEC;
    
    cout<<"Time elapsed for deletion- "<<time<<"s."<<endl;

    print_node(root);
    
    fin.close();
    
    return 0;
}
