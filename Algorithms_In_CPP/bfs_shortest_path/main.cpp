//
//  main.cpp
//  BFS_SHORTEST_PATH
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


void BFS_shortest_(map<Node* , vector<Edge> > graph, Node* from, Node* to, int n, Node* prev[], int &cost){
    int visit[n]; //visited array
    for (int i=0; i<n; i++) visit[i]=0;
    Queue my_queue= *(new Queue());
    
    my_queue.push(from);
    visit[from->data]=1;
    
    Node* filler=new Node();
    my_queue.push(filler);
    
    cost=0;
    
    while (not my_queue.is_empty()){
        Node* node=my_queue.pop();
        if (node->data==-1){
            cost++;
            if (my_queue.is_empty()) {break;}
            Node* filler=new Node();
            my_queue.push(filler);
            continue;

        }
        
        
        if (node==to) break;
        
        for (Edge edge: graph[node]){
            if (not visit[edge.to->data]) {
                my_queue.push(edge.to);
                prev[edge.to->data]=node;
                visit[edge.to->data]=1;
            }
        }
    }
    
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
        
        nodes.push_back(from_node);
        nodes.push_back(to_node);
        
        add_directed_edge_(graph, from_node, to_node, cost);
    }
    
    void add_undirected_edge(int from, int to, int cost){
        
        add_directed_edge(from, to, cost);
        add_directed_edge(to, from, cost);
    }
    
    void BFS_shortest(int from, int to){
        Node* from_node=create_node(from);
        Node* to_node=create_node(to);
        
        Node* prev[nodes.size()];
        Node* path[nodes.size()];
        
        for (int i=0; i<nodes.size(); i++) {
            prev[i]=0;
            path[i]=0;
        } //initialize
        
        int cost=0;
        
        BFS_shortest_(graph, from_node, to_node, nodes.size(), prev, cost);
        
        int i=cost;
        
        for (Node* temp=to_node; temp; temp=prev[temp->data]){
            path[i]=temp;
            i--;
        }
        
        if (path[0]==from_node){
            for (int j=0; j<cost; j++){
                cout<<path[j]->data<<"->";
            }
            cout<<path[cost]->data<<endl;
            
            cout<<"Cost- "<<cost+1<<endl;
        }
        else{
            cout<<"No shortest path exists.\n";
        }
        
    }
    
    
    void clear(){
        nodes.clear();
        graph.clear();
    }
};


int main(){
    Graph my_graph;
    my_graph.add_undirected_edge(0, 1, 4);
    my_graph.add_undirected_edge(0, 2, 4);
    my_graph.add_undirected_edge(0, 3, 6);
    my_graph.add_undirected_edge(1, 3, 0);
    my_graph.add_undirected_edge(3, 4, 1);
    my_graph.add_undirected_edge(4, 5, 0);
    my_graph.add_undirected_edge(5, 2, 100);
//    my_graph.add_undirected_edge(2, 2, 1);
//    my_graph.add_undirected_edge(2, 3, 1);
//    my_graph.add_undirected_edge(6, 2, 1);
//    my_graph.add_undirected_edge(1, 6, 1);
    
    
    my_graph.BFS_shortest(0, 3);
    
    my_graph.clear();

}




