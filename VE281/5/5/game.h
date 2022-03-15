//
// Created by 69009 on 2019/11/6.
//

#ifndef INC_5_GAME_H
#define INC_5_GAME_H

#include "priority_queue.h"
#include "unsorted_heap.h"
#include "binary_heap.h"
#include "fib_heap.h"
using namespace std;

struct point_t{
    unsigned int x;//horizontal
    unsigned int y;//vertical
    bool is_reached;//true for reached, false for not reached
    int cost;
    int pathcost;
    int predecessor;
    bool is_start = false;
};

struct compare_t
{
    bool operator()(const point_t &a, const point_t &b) const
    {
        if(a.pathcost<b.pathcost) return true;
        else if(a.pathcost == b.pathcost){
            if(a.x == b.x) return a.y < b.y;
            else return a.x < b.x;
        }
        else return false;
    }
};

void trace_back_path(point_t &N, vector<point_t> &grid, int start_x, int start_y, int end_x, int end_y, int width, bool verbose);

void check_point(point_t *C, point_t *N, int width);//Return true if trace_back_path().

void play(vector<point_t> &grid, int start_x, int start_y, int end_x, int end_y, priority_queue<point_t, compare_t> *PQ,
          unsigned int height, unsigned int width, bool verbose);


#endif //INC_5_GAME_H
