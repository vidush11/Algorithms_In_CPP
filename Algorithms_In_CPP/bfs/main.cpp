//
//  main.cpp
//  BFS
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


struct Queue_elems{
    Node* elem;
    Queue_elems* next=0;
};

struct Queue{
    Queue_elems* top=0;
    Queue_elems* end=0;
    
    void push(Node* node){
        Queue_elems* element= new Queue_elems();
        element->elem=node;
        
        if (top){
            top->next=element;
            top=element;
        }
        else {
            top=element;
            end=element;
        }
        
    }
    
    Node* pop(){
        Queue_elems* temp=end;
        end=end->next;
        if (not end) top=end;
        return temp->elem;
    }
    
    void reset(){
        top=0;
        end=0;
    }
    
    bool is_empty(){
        return (end==0);
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


void BFS_(map<Node* , vector<Edge> > graph, Node* from, int n){
    int visit[n]; //visited array
    for (int i=0; i<n; i++) visit[i]=0;
    Queue my_queue= *(new Queue());
    
    my_queue.push(from);
    visit[from->data]=1;
    
    while (not my_queue.is_empty()){
        Node* node=my_queue.pop();
        //if node is visited;
        cout<<node->data<<' ';
        for (Edge edge: graph[node]){
            if (not visit[edge.to->data]) my_queue.push(edge.to);
            visit[edge.to->data]=1;
        }
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
    void BFS(int from){
        Node* from_node=create_node(from);
        
        BFS_(graph, from_node, nodes.size());
    }
    
    void clear(){
        nodes.clear();
        graph.clear();
    }
};


int main(){
    Graph my_graph;
    my_graph.add_directed_edge(1, 2, 1);
    my_graph.add_directed_edge(1, 2, 1);
    my_graph.add_directed_edge(1, 3, 1);
    my_graph.add_directed_edge(2, 4, 1);
    my_graph.add_directed_edge(2, 5, 1);
    my_graph.add_directed_edge(3, 6, 1);
    my_graph.add_directed_edge(3, 7, 1);
    my_graph.add_directed_edge(2, 2, 1);
    my_graph.add_directed_edge(2, 3, 1);
    my_graph.add_directed_edge(6, 2, 1);
    my_graph.add_directed_edge(1, 6, 1);
    
    my_graph.BFS(1);
    
    my_graph.clear();
    

    int numNodes = 100;
    for (int i = 0; i < numNodes; i++){
        for (int j = 0; j < numNodes; j++) {my_graph.add_directed_edge( i, j, 1);}
    }
    my_graph.BFS(6);
}



