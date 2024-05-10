//
//  main.cpp
//  topological_sort
//
//  Created by Vidush Jindal on 02/05/24.
//

#include <iostream>
#include <cstdio>
#include <vector>
#include <map>

using namespace std;

struct Node{
    int data=-1;
};


struct Stack_elems{
    Node* elem;
    Stack_elems* next=0;
};

struct Stack{
    Stack_elems* top=0;

    
    void push(Node* node){
        Stack_elems* element= new Stack_elems();
        element->elem=node;
        
        if (top){
            element->next=top;
            top=element;
        }
        else {
            top=element;
        }
        
    }
    
    Node* pop(){
        Stack_elems* temp=top;
        top=top->next;
        
        return temp->elem;
    }
    
    void reset(){
        top=0;
    }
    
    bool is_empty(){
        return (top==0);
    }
    
    Node* top_elem(){
        return top->elem;
    }
};

struct Edge{
    Node* from;
    Node* to;
    int cost;
    
    Edge(Node* from, Node* to, int cost){
        this->from=from;
        this->to=to;
        this->cost=cost;
        
    }
};

void add_directed_edge_(map<Node* , vector<Edge> > &graph, Node* from, Node* to, int cost ){
    vector<Edge> list = graph[from];
    
    if (list.empty()) graph[from]= *(new vector<Edge>);
                     
    Edge new_edge=Edge(from, to, cost);
    graph[from].push_back(new_edge);
}



struct Graph{
    vector<Node *> nodes;
    map<Node*, vector<Edge>> graph;
    
    Node* create_node(int nd){
        Node* from_node=0;
        for (Node* node: nodes){
            if (node->data==nd) {
                from_node=node;
                break;}
        }
        
        if (not from_node) {
            from_node=new Node;
            from_node->data=nd;
            nodes.push_back(from_node);
        }
        return from_node;
    }
    
    void add_directed_edge(int from, int to, int cost){
        Node* from_node=create_node(from);
        Node* to_node=create_node(to);
                
        add_directed_edge_(graph, from_node, to_node, cost);
    }
    
    
    void TopSort(int from){
        Node* from_node=create_node(from);
        
        int n=nodes.size();
        
        Node* answers[n];
        for (int i=0; i<n; i++){
            answers[i]=0;
        }
        
        int j= n-1;
        int visit[n]; //visited array
        for (int i=0; i<n; i++) visit[i]=0;
        Stack my_stack= *(new Stack());
        
        while (true){
            
            my_stack.push(from_node);
            visit[from_node->data]=1;
            
            while (not my_stack.is_empty()){
                Node* node= my_stack.top_elem();
                int count=0;
                for (Edge edge: graph[node]){
                    if (not visit[edge.to->data]) {
                        count++;
                        my_stack.push(edge.to);
                        visit[edge.to->data]=1;
                    }
                }
                
                if (count==0) {answers[j]=my_stack.pop(); j--;}
            }
            
            int not_visit=0;
            for (int i=0; i<n; i++){
                if (not visit[i]){
                    from_node=create_node(i);
                    not_visit++;
                    break;
                }
            }
            if (not not_visit) break;
                
        }
        

        for (int i=0; i<n; i++){
            cout<<answers[i]->data<<' ';
        }
        cout<<endl;
    }
    
    
    
};


int main(){
    Graph my_graph;
    my_graph.add_directed_edge(0, 1, 3);
    my_graph.add_directed_edge(0, 2, 2);
    my_graph.add_directed_edge(0, 5, 3);
    my_graph.add_directed_edge(1, 3, 1);
    my_graph.add_directed_edge(1, 2, 6);
    my_graph.add_directed_edge(2, 3, 1);
    my_graph.add_directed_edge(2, 4, 10);
    my_graph.add_directed_edge(3, 4, 5);
    my_graph.add_directed_edge(5, 4, 7);
    
//    cout<<my_graph.nodes.size();
    my_graph.TopSort(0);
}



