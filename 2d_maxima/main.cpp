//
//  main.cpp
//  2d_maxima
//
//  Created by Vidush Jindal on 10/05/24.
//

#include <iostream>
#include <cstdio>
#include <vector>
#include <set>

using namespace std;
struct Pair{
    int x;
    int y;
    
    Pair(int x, int y){
        this->x=x;
        this->y=y;
    }
};


struct Stack_elems{
    Pair* elem;
    Stack_elems* next=0;
};

struct Stack{
    Stack_elems* top=0;
    
    void push(Pair* Pair){
        Stack_elems* element= new Stack_elems();
        element->elem=Pair;
        
        if (top){
            element->next=top;
            top=element;
        }
        else {
            top=element;
        }
        
    }
    
    Pair* pop(){
        if (not top) return 0;
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


void merge(int start, int mid, int end, vector <Pair> &numbers){
    int l=end-start+1;
    vector<Pair> merged(l,{0,0});

    int s1=start;
    int e1=mid;
    int s2=mid+1;
    int e2=end;

    int curr_elem=0;

    while ((s1<=e1)&(s2<=e2)){
        if (numbers[s1].x>numbers[s2].x){
            merged[curr_elem]=numbers[s2];
            s2++;

        }
        else {
            merged[curr_elem]=numbers[s1];
            s1++;
        }
            curr_elem++;
    }

    while (s1<=e1){
        merged[curr_elem]=numbers[s1];
        curr_elem++;
        s1++;
    }
    while (s2<=e2){
        merged[curr_elem]=numbers[s2];
        curr_elem++;
        s2++;
    }

    for (int i=0; i<l;i++){
        numbers[start+i]=merged[i];
    }

}

void merge_sort(int start, int end, vector <Pair> &numbers){
    if (not (end-start>0) ) return;
    if (end-start==1){
        if (numbers[start].x>numbers[end].x){
            Pair temp=numbers[start];
            numbers[start]=numbers[end];
            numbers[end]=temp;
        }
    }
    else{
        int mid=(end+start)/2;
        merge_sort(start,mid, numbers);
        merge_sort(mid+1,end, numbers);
        merge(start,mid,end, numbers);
    }
    
}
int main(){
    vector<Pair> points;
    int x,y;
    for (int i=0; i<4; i++){
        cin>>x>>y;
        points.push_back(Pair(x,y));
    }
//    points.push_back(Pair(7,13));
//    points.push_back(Pair(4,11));
//    points.push_back(Pair(12,12));
//    points.push_back(Pair(9,10));
//    points.push_back(Pair(14,10));
//    points.push_back(Pair(7,7));
//    points.push_back(Pair(15,7));
//    points.push_back(Pair(2,5));
//    points.push_back(Pair(11,5));
//    points.push_back(Pair(4,4));
//    points.push_back(Pair(5,1));
//    points.push_back(Pair(13,3));
    
    
    //brute force
    /*
    set<int> indices;

    for (int i=0; i<points.size(); i++){
        Pair point1=points[i];
        int x1=point1.x;
        int y1=point1.y;
        
        for (int j=0; j<points.size(); j++){
            Pair point2=points[j];
            int x2=point2.x;
            int y2=point2.y;
            
            if ( ((x2<=x1)&&(y2<=y1))&& not(x2==x1 && y2==y1) ){
                indices.insert(j);
            }
        }
    }

    
    vector<Pair> answers;
    
    for (int i=0; i<points.size(); i++){
        if (not indices.count(i)){
            answers.push_back(points[i]);
        }
    }
    

    for (int i=0; i<answers.size(); i++){
        cout<<answers[i].x<<' '<<answers[i].y<<endl;
    }
     
    */
    
    //Smarter solution using stack
    //Sort the points using merge_sort
    merge_sort(0,points.size()-1,points);
    
//    for (int i=0; i<points.size(); i++){
//        cout<<points[i].x<<' '<<points[i].y<<endl;
//    }
    
    Stack my_stack=Stack();
    my_stack.push(&points[0]);
    
    for (int i=1; i<points.size(); i++){
        int y=points[i].y;
        int x=points[i].x;
        int add=1;
        while (my_stack.top){
            if (my_stack.top->elem->y>y){
                if (my_stack.top->elem->x==x){
                    add=0;
                }
                break;
            }
            my_stack.pop();
        }
        if (add)    my_stack.push(&points[i]);
        
    }
    
    Stack_elems* temp=my_stack.top;
    while (temp){
        cout<<temp->elem->x<<' '<<temp->elem->y<<endl;
        temp=temp->next;
    }
    
}

 
