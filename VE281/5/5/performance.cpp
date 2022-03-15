//
// Created by 69009 on 2019/11/11.
//
#include <iostream>
#include <cstdlib>
#include <climits>
#include <ctime>
#include<vector>
#include "game.h"
#include "priority_queue.h"
#include "unsorted_heap.h"
#include "binary_heap.h"
#include "fib_heap.h"

int main(){
    unsigned int n = 800;
    unsigned int width = n;
    unsigned int height = n;
    vector<point_t> grid1;
    vector<point_t> grid2;
    vector<point_t> grid3;
    for(unsigned int y = 0; y < height; y++){
        for(unsigned int x = 0; x < width; x++){
            point_t point;
            point.x = x;
            point.y = y;
            point.cost = rand()%1000;
            point.is_reached = false;
            grid1.push_back(point);
            grid2.push_back(point);
            grid3.push_back(point);
        }
    }
    cout<<"The size is:"<<grid1.size()<<endl;
    priority_queue<point_t ,compare_t> *unsorted = new unsorted_heap<point_t ,compare_t>;
    priority_queue<point_t ,compare_t> *binary = new binary_heap<point_t ,compare_t>;
    priority_queue<point_t ,compare_t> *fibonacci = new fib_heap<point_t ,compare_t>;
    int t1 = clock();
    play(grid1,0,0,n-1,n-1,unsorted,n,n,false);
    cout<<"Unsorted time: "<<(clock() - t1)<<endl;
    delete unsorted;
    t1 = clock();
    play(grid2,0,0,n-1,n-1,binary,n,n,false);
    cout<<"Binary time: "<<(clock() - t1)<<endl;
    delete binary;
    t1 = clock();
    play(grid3,0,0,n-1,n-1,fibonacci,n,n,false);
    cout<<"Fibonacci time: "<<(clock() - t1)<<endl;
    delete fibonacci;
    return 0;
}
