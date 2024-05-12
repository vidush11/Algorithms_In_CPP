//
//  main.cpp
//  merge_sort
//
//  Created by Vidush Jindal on 10/05/24.
//

#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <time.h>
#include <iomanip>
using namespace std;


void merge(int start, int mid, int end, vector <int> &numbers){
    int l=end-start+1;
    vector<int> merged(l,0);

    int s1=start;
    int e1=mid;
    int s2=mid+1;
    int e2=end;

    int curr_elem=0;

    while ((s1<=e1)&(s2<=e2)){
        if (numbers[s1]>numbers[s2]){
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

void merge_sort(int start, int end, vector <int> &numbers){
    if (not (end-start>0) ) return;
    if (end-start==1){
        if (numbers[start]>numbers[end]){
            int temp=numbers[start];
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
    vector <int> numbers;

    for (int i=pow(10,7); i>0; i--){
        numbers.push_back(i);
    }
    
    double time1=time(0);
    merge_sort(0, numbers.size()-1, numbers);
    double time2=time(0);
    
//    for (int i=0; i<numbers.size(); i++){
//        cout<<numbers[i]<<' ';
//    }
    
    cout<<"Finished"<<"Time- "<<fixed<<time2-time1<<setprecision(10)<<endl;
    return 0;
}
