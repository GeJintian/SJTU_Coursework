//
// Created by 69009 on 2019/6/21.
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
    string species_summary = "a.txt";
    string world_file = "world_file.txt";
    world_t world;
    bool init = initWorld(world, species_summary, world_file);
    if(!init) return -1;
    cout<<"Initial state"<<endl;
    printGrid(world.grid);

    /*//Check for adjacentPoint
    point_t pt = adjacentPoint(world.creatures[1].location,world.creatures[1].direction);
    cout<<"The point in front of hop is"<<pt.r<<"*"<<pt.c<<endl;
    //Check for direction
    cout<<"Hop's left is "<<directName[leftFrom(world.creatures[0].direction)]<<" right is "
    <<directName[rightFrom(world.creatures[0].direction)]<<endl;
    //Check getInstruction
    instruction_t it0 = getInstruction(world.creatures[0]);
    instruction_t it1 = getInstruction(world.creatures[1]);
    cout<<"hop's first instruction is "<<opName[it0.op]<<endl;
    cout<<"fly's first instruction is "<<opName[it1.op]<<endl;
    //Check getCreature
    creature_t * cr = getCreature(world.grid, world.creatures[1].location);
    cout<<cr->species->name;*/

}