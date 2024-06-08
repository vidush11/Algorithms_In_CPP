#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;


int main(){
    
    vector<int> numbers={1,1,1,0,0,0,0,1};
    int n=8;
    int k=4;
    
    int count=-1;
    int start=~numbers[0] + 2;
    int rot_ind{};
    int is_true=true;
    
    for (int i=0; i<n; i++){

        if (not (i%k) ) {count++; start=~start+2;}
        if (not (numbers[i] == start) ){
            is_true=false;
            
            if (not (i%k)) rot_ind=i;
            else rot_ind=i;
            
            bool check=true;
            for (int e= n-1; e>n-1-(2*k-i); e--){
                if (numbers[e]!=start){ check=false; break;}
            }
            
            if (check){
                int new_mod=(n-1-(2*k-i))&k;
                start=~start+2;
                count++;
                for (int ni=n-1-(2*k-i); ni>=rot_ind; ni--){
                    if ((ni%k) ==new_mod){ count++; start=~start+2;}
                    if (numbers[ni] !=start){
                        check=false;
                        break;
                    }
                }
            }
            if (check){
                cout<<rot_ind-1<<endl;
                break;
            }
            else {cout<<-1<<endl;}
            
            break;
        }
        
    }
    
    if (is_true){
        if (n/k % 2){
            if (k==n) cout<<n-1<<endl;
            else cout<<2*k-1<<endl;
        }
        else cout<<k-1<<endl;
    }
    return 0;
}

/*
 7
 8 4
 11100001
 4 2
 1110
 12 3
 111000100011
 5 5
 00000
 6 1
 101001
 8 4
 01110001
 12 2
 110001100110
 
 */

