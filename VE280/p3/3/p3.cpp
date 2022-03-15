//
// Created by 69009 on 2019/6/17.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "simulation.h"




int main(int argc, char *argv[]){
    //Check input arguments
    if(argc < 4){
        cout<<"Error: Missing arguments!"<<endl;
        cout<<"Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]"<<endl;
        return -1;
    }
    //
    //Check rounds
    string species_summary = argv[1];
    string world_file = argv[2];
    int rounds = atoi(argv[3]);
    //Check rounds
    if(rounds < 0){
        cout<<"Error: Number of simulation rounds is negative!"<<endl;
        return -1;
    }
    //
//Check whether it is verbose or not. If v = 0, no need verbose. If v = 1, it
// needs verbose.
    bool verbose;
    string s = argv[argc - 1];
    if(argc == 4){verbose = false;}
    else if(s == "v" || s == "verbose"){
        verbose = true;
    }
    else {verbose = false;}
//End of check
    world_t world;
    bool init = initWorld(world, species_summary, world_file);
    if(!init) return 0;

    //Print initial world
    cout<<"Initial state"<<endl;
    printGrid(world.grid);

    //Begin simulation
    for(int i = 1; i <= rounds; i++){
        cout<<"Round "<<i<<endl;
        for(unsigned int j = 0; j < world.numCreatures; j++){
            simulateCreature(world.creatures[j], world.grid, verbose);
            if(verbose) printGrid(world.grid);
        }
        if(!verbose) printGrid(world.grid);
    }

    return 0;
}

