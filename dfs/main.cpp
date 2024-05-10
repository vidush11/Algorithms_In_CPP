//
//  main.cpp
//  dfs
//
//  Created by Vidush Jindal on 27/04/24.
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


void DFS_(map<Node* , vector<Edge> > graph, Node* from, int n){
    int visit[n]; //visited array
    for (int i=0; i<n; i++) visit[i]=0;
    Stack my_stack= *(new Stack());
    
    my_stack.push(from);
    while (not my_stack.is_empty()){
        Node* node=my_stack.pop();
        if (visit[node->data]) continue; //if node is visited;
        cout<<node->data<<' ';
        for (Edge edge: graph[node]){
            my_stack.push(edge.to);
        }
        visit[node->data]=1;
    }
    cout<<endl;
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
        
        if (not from_node) from_node=new Node;
        from_node->data=nd;
        return from_node;
    }
    
    void add_directed_edge(int from, int to, int cost){
        Node* from_node=create_node(from);
        Node* to_node=create_node(to);
        
        nodes.push_back(from_node);
        nodes.push_back(to_node);
        
        add_directed_edge_(graph, from_node, to_node, cost);
    }
    void DFS(int from){
        Node* from_node=create_node(from);
        
        DFS_(graph, from_node, nodes.size());
    }
        
};


int main(){
    Graph my_graph;
    my_graph.add_directed_edge(0, 1, 4);
    my_graph.add_directed_edge(0, 2, 5);
    my_graph.add_directed_edge(1, 2, -2);
    my_graph.add_directed_edge(1, 3, 6);
    my_graph.add_directed_edge(2, 3, 1);
    my_graph.add_directed_edge(2, 2, 10);
    
    my_graph.DFS(1);
}



