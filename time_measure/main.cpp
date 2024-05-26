//
//  main.cpp
//  time_measure
//
//  Created by Vidush Jindal on 25/05/24.
//

#include <iostream>
#include <cstdio>
#include <time.h>
#include <cmath>

using namespace std;
int main(int argc, const char * argv[]) {
    int ans=0;
    clock_t start=clock();
    for (int i=0; i<pow(10,9); i++){
        ans++;
    }
    clock_t end=clock();
    
    double time_elapsed=(double) (end-start)/CLOCKS_PER_SEC;
    
    cout<<"Time Elpased-"<<time_elapsed<<" s"<<endl;
    return 0;
}
