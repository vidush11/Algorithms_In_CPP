#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void print_array(vector<int> x){
    for (int i=0; i< x.size(); i++){
        std::cout<<x[i]<<' ';
    }
    std::cout<<std::endl;

}

struct Heap{
    vector<int> heap{};
    int size=0;
    
    void heapify_up(int root){
        while (root!=0){
            int ind=(root-1)/2;
            if (heap[ind]> heap[root]) {
                int temp=heap[ind];
                heap[ind]=heap[root];
                heap[root]=temp;
                
                root=ind;
                
            }
            else {break;}
        }
        
    }

    void heapify_down(int root){
        int l=heap.size()-1; //off by one indicing
        int ind=2*root+1;
        while (ind <= l){
            int no_small= heap[root];
            int small=root;
            if (heap[root]> heap[ind]) {no_small=heap[ind]; small=ind;}
            
            if (ind!=l) {
                if (no_small>heap[ind+1]) {small=ind+1; no_small=heap[ind+1];}
            }
            
            if (small== root) break;
            else {
                int temp= heap[root];
                heap[root]=heap[small];
                heap[small]=temp;
                
                root=small;
                ind=2*small+1;
                
            }
            
        }
    }

    void insert(int d){
//        for (int i=0; i<heap.size(); i++) {if (heap[i]==d) return;} //duplicate element
        heap.push_back(d);
        heapify_up(heap.size()-1);
        

    }

    void del(int ind){
        int l=heap.size();
        heap[ind]=heap[l-1];
        heap.pop_back();
        heapify_down(ind);
        heapify_up(ind);
        
        
    }

//    int min_extract(){
//        if (heap.empty()) {cout<<"No values to return min.";return -1;}
//        int min=heap[0];
//        return min;
//    }
    
    void make_sorted(Heap heap_struct, vector <int> &x){
        while (not heap_struct.heap.empty()){
            int no=heap_struct.min();
            heap_struct.del(0);
            x.push_back(no);
        }
        
    }
    
    void update_size(){
        this->size=heap.size();
        
    }
    
    int min(){
        return heap[0];
    }
    
    int max(){ //o(n)
        int l=heap.size();
        int n= ceil(log2(l+1));
        int start=pow(2,n-1)-1;
        int end=l-1;
        int max=heap[start];
        for (int i=start; i<=end;i++){
            if (heap[i]>max) max=heap[i];
        }
        return max;
    }
    
};


int main(){
    //testing the heap code
/*    vector<int> arr={1,2,3,0,9,8,3,0,9,8,7,9,83,-1,-9,8,0,3,4,2,3,5,5,4,3,2,3,4,5,5};
    Heap my_heap;
    
    for (int i=0; i<arr.size(); i++) my_heap.insert(arr[i]);
    print_array(arr);
    print_array(my_heap.heap);
    
    vector<int> heap_sorted;
    my_heap.make_sorted(my_heap, heap_sorted);
    
    print_array(my_heap.heap);
    print_array(heap_sorted);
 */
    
    
    
    
    
}
