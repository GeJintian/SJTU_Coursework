//
// Created by 69009 on 2019/11/6.
//

#include <iostream>
#include "game.h"
#include "priority_queue.h"
using namespace std;

static void trace_helper(point_t N, vector<point_t> &grid){
    if(N.is_start){
        cout<<"("<<N.x<<", "<<N.y<<")"<<endl;
        return;}
    trace_helper(grid[N.predecessor],grid);
    cout<<"("<<N.x<<", "<<N.y<<")"<<endl;
}


void trace_back_path(point_t &N, vector<point_t> &grid, int start_x, int start_y, int end_x, int end_y){
    cout<<"The shortest path from ("<<start_x<<", "<<start_y<<") to ("<<end_x<<", "<<end_y<<") is ";
    cout<<N.pathcost<<"."<<endl;
    cout<<"Path:"<<endl;
    trace_helper(N, grid);
}

void check_point(point_t *C, point_t *N, int width){
    N->pathcost = C->pathcost + N->cost;
    N->is_reached = true;
    N->predecessor = C->x + width*C->y;
}

void play(vector<point_t> &grid, int start_x, int start_y, int end_x, int end_y, priority_queue<point_t, compare_t> *PQ,
        unsigned int height, unsigned int width, bool verbose){//index = x + y*width
    //Start_point.pathcost=start_point.cellweight
    grid[start_x + start_y*width].pathcost = grid[start_x + start_y*width].cost;
    //Mark start_point as reached
    grid[start_x + start_y*width].is_reached = true;
    grid[start_x + start_y*width].is_start = true;
    //PQ.enqueue(start_point)
    PQ->enqueue(grid[start_x + start_y*width]);
    int n = 0;
    //cout<<PQ->empty()<<endl;
    while(!PQ->empty()){
        point_t C = PQ->dequeue_min();
        if(verbose){
            cout<<"Step "<<n<<endl;
            cout<<"Choose cell ("<<C.x<<", "<<C.y<<") with accumulated length "<<C.pathcost<<"."<<endl;
            n++;
        }
        //cout<<"C points at ("<<C.x<<", "<<C.y<<")."<<endl;
        //if(C.predecessor!= nullptr)cout<<"C's predecessor is at"<<C.predecessor->x<<", "<<C.predecessor->y<<endl;
        //Right
        if(C.x + 1 < width && !grid[C.x + 1 + width*C.y].is_reached){
            //cout<<"Right neighbor is at ("<<grid[C.x + 1 + width*C.y].x<<", "<<grid[C.x + 1 + width*C.y].y<<")."<<endl;
            check_point(&C, &grid[C.x + 1+ width*C.y], width);
            if(grid[C.x + 1+ width*C.y].x == end_x && grid[C.x + 1+ width*C.y].y == end_y){
                if(verbose){cout<<"Cell ("<<grid[C.x + 1+ width*C.y].x<<", "<<grid[C.x + 1+ width*C.y].y<<") with accumulated length ";
                cout<<grid[C.x + 1+ width*C.y].pathcost<<" is the ending point."<<endl;}
                trace_back_path(grid[C.x + 1+ width*C.y], grid, start_x, start_y, end_x, end_y);
                return;
            }
            else PQ->enqueue(grid[C.x + 1+ width*C.y]);
            if(verbose){
                cout<<"Cell ("<<grid[C.x + 1+ width*C.y].x<<", "<<grid[C.x + 1+ width*C.y].y<<") with accumulated length ";
                cout<<grid[C.x + 1+ width*C.y].pathcost<<" is added into the queue."<<endl;
            }
        }
        //Down
        if(C.y + 1 < height && !grid[C.x+ width*(C.y + 1)].is_reached){
            //cout<<"Down neighbor is at ("<<grid[C.x+ width*(C.y + 1)].x<<", "<<grid[C.x+ width*(C.y + 1)].y<<")."<<endl;
            check_point(&C, &grid[C.x+ width*(C.y + 1)], width);
            if(grid[C.x+ width*(C.y + 1)].x == end_x && grid[C.x+ width*(C.y + 1)].y == end_y){
                if(verbose){cout<<"Cell ("<<grid[C.x+ width*(C.y + 1)].x<<", "<<grid[C.x+ width*(C.y + 1)].y<<") with accumulated length ";
                cout<<grid[C.x+ width*(C.y + 1)].pathcost<<" is the ending point."<<endl;}
                trace_back_path(grid[C.x+ width*(C.y + 1)], grid, start_x, start_y, end_x, end_y);
                return;
            }
            else PQ->enqueue(grid[C.x+ width*(C.y + 1)]);
            if(verbose){
                cout<<"Cell ("<<grid[C.x+ width*(C.y + 1)].x<<", "<<grid[C.x+ width*(C.y + 1)].y<<") with accumulated length ";
                cout<<grid[C.x+ width*(C.y + 1)].pathcost<<" is added into the queue."<<endl;
            }
        }
        //Left
        if(C.x >= 1 && !grid[C.x - 1 + width*C.y].is_reached){
            //cout<<"Left neighbor is at ("<<grid[C.x - 1 + width*C.y].x<<", "<<grid[C.x - 1 + width*C.y].y<<")."<<endl;
            check_point(&C, &grid[C.x - 1 + width*C.y], width);
            if(grid[C.x - 1 + width*C.y].x == end_x && grid[C.x - 1 + width*C.y].y == end_y){
                if(verbose){cout<<"Cell ("<<grid[C.x - 1 + width*C.y].x<<", "<<grid[C.x - 1 + width*C.y].y<<") with accumulated length ";
                cout<<grid[C.x + width*(C.y - 1)].pathcost<<" is the ending point."<<endl;}
                trace_back_path(grid[C.x - 1 + width*C.y], grid, start_x, start_y, end_x, end_y);
                return;
            }
            else PQ->enqueue(grid[C.x - 1 + width*C.y]);
            if(verbose){
                cout<<"Cell ("<<grid[C.x - 1+ width*C.y].x<<", "<<grid[C.x - 1+ width*C.y].y<<") with accumulated length ";
                cout<<grid[C.x - 1+ width*C.y].pathcost<<" is added into the queue."<<endl;
            }
        }
        //Up
        if(C.y >= 1 && !grid[C.x + width*(C.y - 1)].is_reached){
            //cout<<"Up neighbor is at ("<<grid[C.x + width*(C.y - 1)].x<<", "<<grid[C.x + width*(C.y - 1)].y<<")."<<endl;
            check_point(&C, &grid[C.x + width*(C.y - 1)], width);
            if(grid[C.x + width*(C.y - 1)].x == end_x && grid[C.x + width*(C.y - 1)].y == end_y){
                if(verbose){cout<<"Cell ("<<grid[C.x + width*(C.y - 1)].x<<", "<<grid[C.x + width*(C.y - 1)].y<<") with accumulated length ";
                cout<<grid[C.x + width*(C.y - 1)].pathcost<<" is the ending point."<<endl;}
                trace_back_path(grid[C.x + width*(C.y - 1)], grid, start_x, start_y, end_x, end_y);
                return;
            }
            else PQ->enqueue(grid[C.x + width*(C.y - 1)]);
            if(verbose){
                cout<<"Cell ("<<grid[C.x + width*(C.y - 1)].x<<", "<<grid[C.x + width*(C.y - 1)].y<<") with accumulated length ";
                cout<<grid[C.x + width*(C.y - 1)].pathcost<<" is added into the queue."<<endl;
            }
        }
    }
}