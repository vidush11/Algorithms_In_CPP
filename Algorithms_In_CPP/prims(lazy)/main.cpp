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

void print_vector(vector<Edge> v){
    for (int i=0; i<v.size(); i++){
        printf("From- %d, To- %d, Cost- %d\n", v[i].from->data, v[i].to->data, v[i].cost);
    }
}
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
    
    void add_undirected_edge(int from, int to, int cost){
        add_directed_edge(from, to, cost);
        add_directed_edge(to, from, cost);
        
    }
    

    
    void clear(){
        nodes.clear();
        graph.clear();
    }
    
    vector<vector <Edge>> prims(int start){
        Node* start_node=create_node(start);
        priority_queue <Edge, vector<Edge>, edge_compare> pq;
        
        int visited[nodes.size()]; //make sure to add nodes in order from 0 onwards
        for (int i=0; i<nodes.size(); i++) {visited[i]=0;}
        visited[start_node->data]=1;
        vector<vector<Edge>> answer;
        
        int count=0;
        while (not pq.empty() || start_node==create_node(start)){
            for (Edge edge: graph[start_node]){
                if (not visited[edge.to->data]) pq.push(edge);
            }
            Edge curr_edge=pq.top();
            pq.pop();
            if (not visited[curr_edge.to->data]) {
                if (answer[count].empty()) answer[count]=*(new vector<Edge> );
                answer[count].push_back(curr_edge);
                cout<<"done";
                start_node=curr_edge.to;
                continue;
                } //push edge
            
            if (pq.empty()){
                int ind=0;
                for (int i=0; i<nodes.size(); i++){
                    if (not visited[i]) {ind=i;break;}
                }
                start_node=create_node(ind);
                count++;
            }
        }
        
        return answer;
    }
};


int main(){
    Graph my_graph;
    
    my_graph.add_undirected_edge(0, 1, 5);
    my_graph.add_undirected_edge(1, 2, 4);
    my_graph.add_undirected_edge(2, 9, 2);
    my_graph.add_undirected_edge(0, 4, 1);
    my_graph.add_undirected_edge(0, 3, 4);
    my_graph.add_undirected_edge(1, 3, 2);
    my_graph.add_undirected_edge(2, 7, 4);
    my_graph.add_undirected_edge(2, 8, 1);
    my_graph.add_undirected_edge(9, 8, 0);
    my_graph.add_undirected_edge(4, 5, 1);
    my_graph.add_undirected_edge(5, 6, 7);
    my_graph.add_undirected_edge(6, 8, 4);
    my_graph.add_undirected_edge(4, 3, 2);
    my_graph.add_undirected_edge(5, 3, 5);
    my_graph.add_undirected_edge(3, 6, 11);
    my_graph.add_undirected_edge(6, 7, 1);
    my_graph.add_undirected_edge(3, 7, 2);
    my_graph.add_undirected_edge(7, 8, 6);
    
    vector<vector<Edge>> v=my_graph.prims(0);
    cout<<v.size();
}
