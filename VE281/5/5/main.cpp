#include <iostream>
#include <unistd.h>
#include <getopt.h>
#include "game.h"
#include "priority_queue.h"
#include "unsorted_heap.h"
#include "binary_heap.h"
#include "fib_heap.h"
using namespace std;

int main(int argc, char **argv) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    //Input part
    int verbose_flag = 0;
    int i_flag = 0;
    char *cvalue = NULL;
    int c;
    int option_index = 0;
    while(true){
        static struct option long_options[] = {
                {"verbose", no_argument, &verbose_flag, 1},
                {"implementation", required_argument, nullptr, 'i'},
                {0,0,0,0}
        };
        c = getopt_long(argc, argv,"+vi:", long_options, &option_index);
        if(c == -1) break;
        switch(c){
            case 'i':
                cvalue = optarg;
                i_flag = 1;
                break;
            case 'v':
                verbose_flag = 1;
                break;
            default:
                break;
        }
    }
    if(i_flag == 0) return 0;
    string str(cvalue);
    priority_queue<point_t ,compare_t> *PQ;
    if(str == "BINARY") PQ = new binary_heap<point_t ,compare_t>;
    else if(str == "UNSORTED") PQ = new unsorted_heap<point_t ,compare_t>;
    else PQ = new fib_heap<point_t ,compare_t>;
    bool verbose;
    if(verbose_flag == 1) verbose = true;
    else verbose = false;
    //
    unsigned int height, width;
    cin>>width>>height;
    unsigned int start_x, start_y, end_x, end_y;
    cin>>start_x>>start_y>>end_x>>end_y;
    vector<point_t> grid;
    for(unsigned int y = 0; y < height; y++){
        for(unsigned int x = 0; x < width; x++){
            point_t point;
            point.x = x;
            point.y = y;
            cin>>point.cost;
            point.is_reached = false;
            grid.push_back(point);
        }
    }
    //cout<<"Start point is ("<<grid[start_x + start_y*width].x<<", "<<grid[start_x + start_y*width].y<<")."<<endl;
    //
    play(grid, start_x, start_y, end_x, end_y, PQ, height, width, verbose);
    delete PQ;
    return 0;
}