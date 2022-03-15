//
// Created by 69009 on 2019/6/20.
//
#include <string>
#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "simulation.h"

using namespace std;


int main(){
    int rounds = 5;
    bool verbose = true;
    string species_summary = "a.txt";
    string world_file = "world_file.txt";
    world_t world;
    bool init = initWorld(world, species_summary, world_file);
    if(!init) return -1;
    cout<<"Initial state"<<endl;
    printGrid(world.grid);

    //Begin simulation
    for(int i = 1; i <= rounds; i++){
        cout<<"Round "<<i<<endl;
        for(int j = 0; j < world.numCreatures; j++){
            simulateCreature(world.creatures[j], world.grid, verbose);
            if(verbose) printGrid(world.grid);
        }
        if(!verbose) printGrid(world.grid);
    }


    return 0;
}
