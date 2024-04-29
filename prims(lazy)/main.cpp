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
#include <queue>


using namespace std;

struct Node{
    int data=-1;
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

struct edge_compare{
    bool operator()(Edge a, Edge b){
        return a.cost>b.cost;
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
    
    void add_undirected_edge(int from, int to, int cost){
        add_directed_edge(from, to, cost);
        add_directed_edge(to, from, cost);
        
    }
    

    
    void clear(){
        nodes.clear();
        graph.clear();
    }
    
    vector<Edge> prims(int start){
        Node* start_node=create_node(start);
        priority_queue <Edge, vector<Edge>, edge_compare> pq;
        
        int visited(nodes.size());
    }
};


int main(){
    
}
