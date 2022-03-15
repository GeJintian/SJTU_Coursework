//
// Created by 69009 on 2019/6/17.
//
#include "world_type.h"
#include "simulation.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>

using namespace std;

bool initWorld(world_t &world, const string &speciesFile,
               const string &creaturesFile){
    ////Begin to compute Species
    //Open species_summary;
    ifstream iFile1;
    iFile1.open(speciesFile);
    if(!iFile1) {
        cout << "Error: Cannot open file "<<speciesFile<<"!";
        return false;
    }
    //
    string species, line, directory, path;
    //Find directory
    getline(iFile1,line);
    istringstream iStream;
    iStream.str(line);
    iStream>>directory;
    //
    //Find species
    unsigned int i = 0;//Count the number of species
    while(getline(iFile1,line)) {
        if(line.length() == 0)  break;
        i++;
        //Error checking
        if(i>MAXSPECIES) {
            cout<<"Error: Too many species!"<<endl;
            cout<<"Maximal number of species is "<<MAXSPECIES<<"."<<endl;
            return false;
        }
        //
        istringstream iStream;
        iStream.str(line);
        iStream>>species;
        //Combine path
        ifstream iFile2;
        ostringstream oStream;
        oStream<<directory<<"/"<<species;
        path = oStream.str();
        //
        //Open path to find program files
        iFile2.open(path);
        if(!iFile2) {
            cout << "Error: Cannot open file "<<path<<"!";
            return false;
        }
        //
        //Read instructions
        string line_program, instruction;
        unsigned int n = 0;//Count program size
        world.species[i - 1].name = species;
        while(getline(iFile2, line)){
            if(line.length() == 0)  break;
            n++;
            //Error checking
            if(n>MAXPROGRAM) {
                cout<<"Error: Too many instructions for species "<<species<<"!"<<endl;
                cout<<"Maximal number of instructions is "<<MAXPROGRAM<<"."<<endl;
                return false;
            }
            //
            istringstream iStream;
            iStream.str(line);
            iStream>>instruction;
            int ans = 11;
            for(int j = 0;j<9;j++){
                if(opName[j] == instruction) ans = j;
            }
            //Error checking
            if(ans == 11){
                cout<<"Instruction "<<instruction<<" is not recognized!"<<endl;
                return false;
            }
            //
            //Find corresponding instruction
            switch (ans) {
                case 0: world.species[i - 1].program[n - 1].op = HOP; break;
                case 1: world.species[i - 1].program[n - 1].op = LEFT; break;
                case 2: world.species[i - 1].program[n - 1].op = RIGHT; break;
                case 3: world.species[i - 1].program[n - 1].op = INFECT; break;
                case 4: world.species[i - 1].program[n - 1].op = IFEMPTY;
                    iStream>>world.species[i - 1].program[n - 1].address; break;
                case 5: world.species[i - 1].program[n - 1].op = IFENEMY;
                    iStream>>world.species[i - 1].program[n - 1].address; break;
                case 6: world.species[i - 1].program[n - 1].op = IFSAME;
                    iStream>>world.species[i - 1].program[n - 1].address; break;
                case 7: world.species[i - 1].program[n - 1].op = IFWALL;
                    iStream>>world.species[i - 1].program[n - 1].address; break;
                case 8: world.species[i - 1].program[n - 1].op = GO;
                    iStream>>world.species[i - 1].program[n - 1].address; break;
                default: assert(0); break;
            }
        }
        iFile2.close();
        world.species[i - 1].programSize = n;
    }
    iFile1.close();
    world.numSpecies = i;
    ////Finish computing Species
    //////////////////////////////////
    //Begin to compute Creatures
    //Open world file.
    ifstream iFile3;
    iFile3.open(creaturesFile);
    if(!iFile3) {
        cout << "Error: Cannot open file "<<creaturesFile<<"!";
        return false;
    }
    string line_world, species_world, initial_direction;


    //Find height and weight
    unsigned int height;
    unsigned int width;
    getline(iFile3,line_world);
    istringstream iStream_world;
    iStream_world.str(line_world);
    iStream_world>>height;
    //Error checking for grid height
    if(height > MAXHEIGHT){
        cout<<"Error: The grid height is illegal!"<<endl;
        return false;
    }
    //
    istringstream iStream_world1;
    getline(iFile3,line_world);
    iStream_world1.str(line_world);
    iStream_world1>>width;
    //Error checking for grid width
    if(width > MAXWIDTH){
        cout<<"Error: The grid width is illegal!"<<endl;
        return false;
    }
    //
    //Assign world.height and world.width
    world.grid.height = height - 1;
    world.grid.width = width - 1;


    unsigned int k = 0;//Count the number of creatures
    while(getline(iFile3,line_world)){
        if(line_world.length() == 0)  break;
        k++;
        //Error checking
        if(k > MAXCREATURES) {
            cout<<"Error: Too many creatures!"<<endl;
            cout<<"Maximal number of creatures is "<<MAXCREATURES<<"."<<endl;
            return false;
        }
        //
        istringstream iStream_world;
        iStream_world.str(line_world);
        iStream_world>>species_world>>initial_direction>>world.creatures[k - 1].location.r>>world.creatures[k - 1].location.c;
        //Error checking for boundary
        if((unsigned int) world.creatures[k - 1].location.r > world.grid.height ||
                (unsigned int) world.creatures[k - 1].location.c > world.grid.width){
            cout<<"Error: Creature ("<<species_world<<" "<<initial_direction<<" "<<world.creatures[k - 1].location.r<<" "
            <<world.creatures[k - 1].location.c<<") is out of bound!"<<endl;
            cout<<"The grid size is "<<world.grid.height + 1<<"-by-"<<world.grid.width + 1<<"."<<endl;
            return false;
        }
        //
        //Find direction
        int d = 11;
        for(int j = 0;j<4;j++){
            if(directName[j] == initial_direction) d = j;
        }
        //Error checking
        if(d == 11){
            cout<<"Direction "<<initial_direction<<" is not recognized!"<<endl;
            return false;
        }
        //Assign direction
        switch (d) {
            case 0:
                world.creatures[k - 1].direction = EAST;
                break;
            case 1:
                world.creatures[k - 1].direction = SOUTH;
                break;
            case 2:
                world.creatures[k - 1].direction = WEST;
                break;
            case 3:
                world.creatures[k - 1].direction = NORTH;
                break;
            default:
                assert(0);
                break;
        }
        //

        //Initial programID
        world.creatures[k - 1].programID = 0;
        //Initial species
        unsigned int m = 40;
        //cout<<world.numSpecies;
        //cout<<world.species[1].name;
        for(unsigned int l = 0; l < world.numSpecies; l++){
            if(species_world == world.species[l].name) {
                m = l;
                break;
            }
        }
        //Error checking
        if(m == 40){
            cout<<"Error: Species "<<species_world<<" not found!";
            return false;
        }
        //
        world.creatures[k - 1].species = world.species + m;
    }
    iFile3.close();
    world.numCreatures = k;


    //Initial grid.creatures
    unsigned int r, c, index_creatures;
    int count;//Count the number of creatures appearing in th same grid
    for(r = 0; r <= world.grid.height; r++){
        for(c = 0; c <= world.grid.width; c++){
            count = 0;
            if(0 == world.numCreatures) world.grid.squares[r][c] = nullptr;
            else{
                world.grid.squares[r][c] = nullptr;
                for(index_creatures = 0; index_creatures < world.numCreatures; index_creatures++){//Exam all creatures
                    if(r == (unsigned int)world.creatures[index_creatures].location.r && c == (unsigned int)world.creatures[index_creatures].location.c){//Find the creature in the point
                        count ++;
                        //Error checking
                        if(count == 2){
                            cout<<"Error: Creature ("<<world.creatures[index_creatures].species->name<<" "
                            <<directName[world.creatures[index_creatures].direction]<<" "<<world.creatures[index_creatures].location.r<<" "
                            <<world.creatures[index_creatures].location.c<<") overlaps with creature ("<<world.grid.squares[r][c]->species->name<<" "
                            <<directName[world.grid.squares[r][c]->direction]<<" "<<world.grid.squares[r][c]->location.r<<" "
                            <<world.grid.squares[r][c]->location.c<<")!"<<endl;
                            return false;
                        }
                        //
                        world.grid.squares[r][c] = world.creatures + index_creatures;
                    }
                }
            }
        }
    }
    return true;
}


////////////////////////////////////////////////////////
bool IFwall(creature_t creature, grid_t grid){//EFFECTS: Return true if the grid in front of the creature is outside of the world
    point_t pt = adjacentPoint(creature.location, creature.direction);
    return !(0 <= pt.c && pt.c <= (int) grid.width && 0 <= pt.r && pt.r <= (int) grid.height);
}
bool IFempty(creature_t creature, grid_t grid){//EFFECTS: Return true if the grid in front of the creature is empty
    int r = creature.location.r;
    int c = creature.location.c;
    if(!IFwall(creature,grid)) {
        switch (creature.direction) {
            case NORTH:
                return (grid.squares[r - 1][c] == nullptr);
            case SOUTH:
                return (grid.squares[r + 1][c] == nullptr);
            case EAST:
                return (grid.squares[r][c + 1] == nullptr);
            case WEST:
                return (grid.squares[r][c - 1] == nullptr);
        }
    }
    return false;
}
void hop(creature_t &creature, grid_t &grid){//EFFECTS: HOP behave
    creature.programID ++;
    int r = creature.location.r;
    int c = creature.location.c;
    point_t pt = adjacentPoint(creature.location, creature.direction);
    if(IFempty(creature,grid)) {
        grid.squares[pt.r][pt.c] = grid.squares[r][c];
        grid.squares[r][c] = nullptr;
        creature.location = pt;
    }
}
void left(creature_t &creature){//EFFECTS:LEFT behave
    creature.programID ++;
    creature.direction = leftFrom(creature.direction);
}
void right(creature_t &creature){//EFFECTS: RIGHT behave
    creature.programID ++;
    creature.direction = rightFrom(creature.direction);
}
bool IFenemy(creature_t &creature, grid_t &grid){
    point_t pt = adjacentPoint(creature.location, creature.direction);
    if(!IFwall(creature, grid) && !IFempty(creature, grid)){
        creature_t * front = getCreature(grid, pt);
        string species_front = front->species->name;
        return !(species_front == creature.species->name);
    }
    return false;
}
bool IFsame(creature_t &creature, grid_t &grid){
    point_t pt = adjacentPoint(creature.location, creature.direction);
    if(!IFwall(creature, grid) && !IFempty(creature, grid)){
        creature_t * front = getCreature(grid, pt);
        string species_front = front->species->name;
        return (species_front == creature.species->name);
    }
    return false;
}
void infect(creature_t &creature, grid_t &grid){
    creature.programID ++;
    point_t pt = adjacentPoint(creature.location, creature.direction);
    if(IFenemy(creature, grid)){
        grid.squares[pt.r][pt.c]->species = creature.species;
        grid.squares[pt.r][pt.c]->programID = 0;
    }
}
void ifempty(unsigned int n, creature_t &creature, grid_t &grid){
    if(IFempty(creature, grid)) creature.programID = n - 1;
    else creature.programID ++;
}
void ifwall(unsigned int n, creature_t &creature, grid_t &grid){
    if(IFwall(creature, grid)) creature.programID = n - 1;
    else creature.programID ++;
}
void ifsame(unsigned int n, creature_t &creature, grid_t &grid){
    if(IFsame(creature, grid)) creature.programID = n - 1;
    else creature.programID ++;
}
void ifenemy(unsigned int n, creature_t &creature, grid_t &grid){
    if(IFenemy(creature, grid)) creature.programID = n - 1;
    else creature.programID ++;
}
void go(unsigned int n, creature_t &creature){
    creature.programID = n - 1;
}
static void v_Operation(creature_t &creature, grid_t &grid){
    instruction_t instruct = getInstruction(creature);
    opcode_t operation = instruct.op;
    switch(operation){
        case HOP:
            cout<<"Instruction "<<creature.programID + 1<<": "<<opName[operation]<<endl;
            hop(creature, grid);
            break;
        case LEFT:
            cout<<"Instruction "<<creature.programID + 1<<": "<<opName[operation]<<endl;
            left(creature);
            break;
        case RIGHT:
            cout<<"Instruction "<<creature.programID + 1<<": "<<opName[operation]<<endl;
            right(creature);
            break;
        case INFECT:
            cout<<"Instruction "<<creature.programID + 1<<": "<<opName[operation]<<endl;
            infect(creature, grid);
            break;
        case IFEMPTY:
            cout<<"Instruction "<<creature.programID + 1<<": "<<opName[operation]<<" "<<instruct.address<<endl;
            ifempty(instruct.address, creature, grid);
            v_Operation(creature, grid);
            break;
        case IFWALL:
            cout<<"Instruction "<<creature.programID + 1<<": "<<opName[operation]<<" "<<instruct.address<<endl;
            ifwall(instruct.address, creature, grid);
            v_Operation(creature, grid);
            break;
        case IFSAME:
            cout<<"Instruction "<<creature.programID + 1<<": "<<opName[operation]<<" "<<instruct.address<<endl;
            ifsame(instruct.address, creature, grid);
            v_Operation(creature, grid);
            break;
        case IFENEMY:
            cout<<"Instruction "<<creature.programID + 1<<": "<<opName[operation]<<" "<<instruct.address<<endl;
            ifenemy(instruct.address, creature, grid);
            v_Operation(creature, grid);
            break;
        case GO:
            cout<<"Instruction "<<creature.programID + 1<<": "<<opName[operation]<<" "<<instruct.address<<endl;
            go(instruct.address, creature);
            v_Operation(creature, grid);
            break;
    }
}
static void Operation(creature_t &creature, grid_t &grid){
    instruction_t instruct = getInstruction(creature);
    opcode_t operation = instruct.op;
    switch(operation){
        case HOP:
            cout<<" "<<opName[operation]<<endl;
            hop(creature, grid);
            break;
        case LEFT:
            cout<<" "<<opName[operation]<<endl;
            left(creature);
            break;
        case RIGHT:
            cout<<" "<<opName[operation]<<endl;
            right(creature);
            break;
        case INFECT:
            cout<<" "<<opName[operation]<<endl;
            infect(creature, grid);
            break;
        case IFEMPTY:
            ifempty(instruct.address, creature, grid);
            Operation(creature, grid);
            break;
        case IFWALL:
            ifwall(instruct.address, creature, grid);
            Operation(creature, grid);
            break;
        case IFSAME:
            ifsame(instruct.address, creature, grid);
            Operation(creature, grid);
            break;
        case IFENEMY:
            ifenemy(instruct.address, creature, grid);
            Operation(creature, grid);
            break;
        case GO:
            go(instruct.address, creature);
            Operation(creature, grid);
            break;
    }
}
void simulateCreature(creature_t &creature, grid_t &grid, bool
verbose){
        cout << "Creature (" << creature.species->name << " " << directName[creature.direction] << " "
             << creature.location.r << " " << creature.location.c << ") takes action:";
    if(verbose) {
        cout<<endl;
        v_Operation(creature, grid);
    }
    else{
        Operation(creature, grid);
    }
}

void printGrid(const grid_t &grid){
    unsigned int r, c;
    for(r = 0; r <= grid.height; r++){
        for(c = 0; c <= grid.width; c++){
            if(grid.squares[r][c] == nullptr) {
                cout<<"____";
            }
            else{
                cout<<grid.squares[r][c]->species->name[0]<<grid.squares[r][c]->species->name[1]<<"_"<<directShortName[grid.squares[r][c]->direction];
            }
            cout<<" ";
        }
        cout<<endl;
    }
}

point_t adjacentPoint(point_t pt, direction_t dir){
    int r = pt.r;
    int c = pt.c;
    switch (dir){
        case NORTH:
            r --; break;
        case SOUTH:
            r++; break;
        case EAST:
            c++;break;
        case WEST:
            c--;break;
    }
    pt.r = r;
    pt.c = c;
    return pt;
}

direction_t leftFrom(direction_t dir){
    switch(dir){
        case EAST:
            dir = NORTH;
            break;
        case SOUTH:
            dir = EAST;
            break;
        case WEST:
            dir = SOUTH;
            break;
        case NORTH:
            dir = WEST;
            break;
    }
    return dir;
}

direction_t rightFrom(direction_t dir){
    switch(dir){
        case EAST:
            dir = SOUTH;
            break;
        case SOUTH:
            dir = WEST;
            break;
        case WEST:
            dir = NORTH;
            break;
        case NORTH:
            dir = EAST;
            break;
    }
    return dir;
}

instruction_t getInstruction(const creature_t &creature){
    unsigned int id = creature.programID;
    return creature.species->program[id];
}

creature_t *getCreature(const grid_t &grid, point_t location){
    int r = location.r;
    int c = location.c;
    return grid.squares[r][c];
}