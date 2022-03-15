#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "simulation.h"
using namespace std;



int main() {
    world_t world;
    string species_summary;
    string world_file;
    string rounds;
    cout<<"Please input species_summary";
    cin>>species_summary;
    //Open species_summary;
    ifstream iFile1;
    iFile1.open(species_summary);
    if(!iFile1) {
        cerr << "Cannot open a.txt\n";
        return -1;
        }
    string species, line, directory, path;
    //Find directory
    getline(iFile1,line);
    istringstream iStream;
    iStream.str(line);
    iStream>>directory;
    //Find species
    unsigned int i = 0;//Count species number
    while(getline(iFile1,line)) {
        if(line.length() == 0) {cout<<"1"; break;}
        i++;
        //Error checking
        if(i>MAXSPECIES) {
            cout<<"Error: Too many species!"<<endl;
            cout<<"Maximal number of species is "<<MAXSPECIES<<"."<<endl;
            exit;
        }
        istringstream iStream;
        iStream.str(line);
        iStream>>species;
        //Combine path
        ifstream iFile2;
        ostringstream oStream;
        oStream<<directory<<"/"<<species;
        path = oStream.str();
        //Open path to find program files
        iFile2.open(path);
        if(!iFile2) {
            cerr << "Cannot open flytrap.txt\n";
            return -1;
        }
        //Read instructions
        string line_program, instruction;
        ////
        ////
        ////
        unsigned int n = 0;//Count program size
        world.species[i - 1].name = species;
        while(getline(iFile2, line)){
            if(line.length() == 0) {cout<<"1"; break;}
            n++;
            //Error checking
            if(n>MAXPROGRAM) {
                cout<<"Error: Too many instructions for species "<<species<<"!"<<endl;
                cout<<"Maximal number of instructions is "<<MAXPROGRAM<<"."<<endl;
                exit;
            }
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
                exit;
            }
            switch (ans) {
                case 0: world.species[i - 1].program[n - 1].op = HOP;break;
                case 1: world.species[i - 1].program[n - 1].op = LEFT;break;
                case 2: world.species[i - 1].program[n - 1].op = RIGHT;break;
                case 3: world.species[i - 1].program[n - 1].op = INFECT;break;
                case 4: world.species[i - 1].program[n - 1].op = IFEMPTY;
                    iStream>>world.species[i - 1].program[n - 1].address;break;
                case 5: world.species[i - 1].program[n - 1].op = IFENEMY;
                    iStream>>world.species[i - 1].program[n - 1].address;break;
                case 6: world.species[i - 1].program[n - 1].op = IFSAME;
                    iStream>>world.species[i - 1].program[n - 1].address;break;
                case 7: world.species[i - 1].program[n - 1].op = IFWALL;
                    iStream>>world.species[i - 1].program[n - 1].address;break;
                case 8: world.species[i - 1].program[n - 1].op = GO;
                    iStream>>world.species[i - 1].program[n - 1].address;break;
                default: assert(0);break;
            }
        }
        iFile2.close();
        world.species[i - 1].programSize = n;
    }
    iFile1.close();
    world.numSpecies = i;
    //
    //
    //
    //

    /*cout<<"Species number is "<<world.numSpecies<<endl;
    cout<<"The second species name is "<<world.species[1].name<<endl;
    cout<<"Its second instruction and step is "<<opName[world.species[1].program[1].op]<<" "<<world.species[1].program[1].address<<endl;
     */
    world_file = "world_file.txt";
    //Open world file.
    //
    //
    //
    ifstream iFile3;
    iFile3.open(world_file);
    if(!iFile3) {
        cerr << "Cannot open world_file.txt\n";
        return -1;
    }
    string line_world, species_world, initial_direction;


    //Find height and weight
    unsigned int height, width;
    getline(iFile3,line_world);
    istringstream iStream_world;
    iStream_world.str(line_world);
    iStream_world>>height;
    istringstream iStream_world1;
    getline(iFile3,line_world);
    iStream_world1.str(line_world);
    iStream_world1>>width;
    world.grid.height = height - 1;
    world.grid.width = width - 1;


    unsigned int k = 0;//Count the number of creatures
    while(getline(iFile3,line_world)){
        if(line_world.length() == 0) {cout<<"1"; break;}
        k++;
        //Error checking
        if(k > MAXCREATURES) {
            cout<<"Error: Too many creatures!"<<endl;
            cout<<"Maximal number of creatures is "<<MAXCREATURES<<endl;
            exit;
        }
        //
        istringstream iStream_world;
        iStream_world.str(line_world);
        iStream_world>>species_world>>initial_direction>>world.creatures[k - 1].location.r>>world.creatures[k - 1].location.c;
        //Find direction
        int d = 11;
        for(int j = 0;j<4;j++){
            if(directName[j] == initial_direction) d = j;
        }
        //Error checking
        if(d == 11){
            cout<<"Direction "<<initial_direction<<" is not recognized!"<<endl;
            exit;
        }
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

        //Initial programID
        world.creatures[k - 1].programID = 0;
        //Initial species
        int m = 40;
        //cout<<world.numSpecies;
        //cout<<world.species[1].name;
        for(int l = 0; l < world.numSpecies; l++){
            if(species_world == world.species[l].name) {
                m = l;
                break;
            }
        }
        //Error checking
        if(m == 40){
            cout<<"Error: Species "<<species_world<<" not found!";
        }
        //
        world.creatures[k - 1].species = world.species + m;
    }
    iFile3.close();
    world.numCreatures = k;


    //Initial grid.creatures
    for(int r = 0; r <= world.grid.height; r++){
        for(int c = 0; c <= world.grid.width; c++){
            if(0 == world.numCreatures) world.grid.squares[r][c] = nullptr;
            else {
                world.grid.squares[r][c] = nullptr;
                for(int index_creatures = 0; index_creatures < world.numCreatures; index_creatures++){
                    if(r == world.creatures[index_creatures].location.r && c == world.creatures[index_creatures].location.c){
                        world.grid.squares[r][c] = world.creatures + index_creatures;
                    }
                }
            }
        }
    }


    cout<<"There are "<<world.numCreatures<<" in world"<<endl;
    cout<<"The second one is Species "<<world.creatures[1].species->name<<endl;
    cout<<"It is in "<<directShortName[world.creatures[1].direction]<<" direction"<<endl;
    cout<<"In 2*2, there is ";
    if(world.grid.squares[1][1] == nullptr){cout<<"nothing"<<endl;}
    else{cout<<world.grid.squares[1][1]->species->name<<endl;}
    int count = 0;
    for(int ri = 0; ri<= 3; ri++){
        for(int cj = 0; cj<=3; cj++){
            if(world.grid.squares[ri][cj] == nullptr) count ++;
        }
    }
    cout<<count<<endl;
    /*cout<<"For the first species, it is "<<world.creatures[0].species->name<<". It is in "<<world.creatures[0].location.r<<"*"<<world.creatures[0].location.c<<endl;
    cout<<"For the second species, it is "<<world.creatures[1].species->name<<". It is in "<<world.creatures[1].location.r<<"*"<<world.creatures[1].location.c<<endl;*/


    return 0;
}