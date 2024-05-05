//
//  main.cpp
//  djikstra_lazy
//
//  Created by Vidush Jindal on 05/05/24.
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

struct Pair{
    Node* node;
    int dist;
    
    Pair(Node* node, int dist){
        this->node=node;
        this->dist=dist;
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

struct pair_compare{
    bool operator()(Pair a, Pair b){
        return a.dist>b.dist;
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

vector<Pair> djikstra_(map<Node* , vector<Edge> > &graph, int n, int maxd, Node* from){
    
    priority_queue <Pair, vector<Pair>, pair_compare> pq;
 
    int visited[n]; //make sure to add nodes in order from 0 onwards
    Node* prev[n];
    vector<int> dist;
    
    for (int i=0; i<n; i++) {visited[i]=0;prev[i]=0; dist.push_back(maxd);}
    pq.push(Pair(from, 0));
    dist[from->data]=0;
    
    visited[from->data]=1;
    
    while (not pq.empty()){
        Pair curr_pair=pq.top();
        pq.pop();
        
        int node_int=curr_pair.node->data;
        if (dist[node_int]!=curr_pair.dist) continue; //if a nodes distance is larger, I will be not visited by default
        
        visited[node_int]=1;
        
        for (Edge edge: graph[curr_pair.node]){
            if (not visited[edge.to->data]){
                int new_dist=curr_pair.dist+edge.cost;
                if (new_dist<dist[edge.to->data]) {
//                    cout<<edge.to->data<<" "<<new_dist<<endl;
                    dist[edge.to->data]=new_dist;
                    pq.push(Pair(edge.to, new_dist));
                    prev[edge.to->data]=curr_pair.node;
                }
            }
        }
        
    }
    
    vector<Pair> answer;
    
    for (int i=0; i<n; i++){
        answer.push_back( Pair(prev[i],dist[i]) );
    }
    return answer;
}
struct Graph{
    vector<Node *> nodes;
    map<Node*, vector<Edge> > graph;
    
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
    
    void djikstra(int start, int to){
        Node* start_node=create_node(start);
        Node* to_node=create_node(to);
        int maxd=0;
        
        for (int i=0; i<nodes.size(); i++){
            for (Edge edge: graph[nodes[i]]){
                maxd+=edge.cost;
            }
        }
        
        vector<Pair> answer= djikstra_(graph, nodes.size(), maxd+1, start_node); //maxd+1 will be inf
        
        for (int i=0; i<nodes.size(); i++){
            if (answer[i].dist==maxd+1) {answer[i].dist=-1;}
            cout<<"Node "<<i<<" , Distance- "<<answer[i].dist<<endl;
        }
        //-1 represents can't be reached
        
        vector<Node*> revpath;
        vector<Node*> path;
        int c=0;
        
        for (Node* node=to_node ; node; node=answer[node->data].node){
            revpath.push_back(node);
            c++;
        }
        
        for (int i=c-1; i>=0; i--){
            path.push_back(revpath[i]);
        }
        printf("\nDistance- %d\n", answer[to].dist);
        printf("Path from %d to %d-\t", start,to);
        for (int i=0; i<c-1; i++){
            cout<<path[i]->data<<"->";
        }
        cout<<path[c-1]->data<<endl;
        
    }

};

int main(){
    Graph my_graph;
    
    my_graph.add_undirected_edge(0, 1, 1);
    my_graph.add_undirected_edge(1, 2, 3);
    my_graph.add_undirected_edge(2, 7, 6);
    my_graph.add_undirected_edge(2, 1, 5);
    my_graph.add_undirected_edge(3, 3, 2);
    
    my_graph.add_undirected_edge(5, 4, 0);
    my_graph.add_undirected_edge(2, 0, 1);
    my_graph.add_undirected_edge(7, 0, 10);
    my_graph.add_undirected_edge(2, 6, 4);
    
    my_graph.djikstra(0, 7);
    

}


