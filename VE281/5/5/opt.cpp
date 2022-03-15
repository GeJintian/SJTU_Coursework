//
// Created by 69009 on 2019/11/8.
//
#include <unistd.h>
#include <getopt.h>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char **argv){
    int verbose_flag = 0;
    int i_flag = 0;
    char *cvalue = NULL;
    int c;
    int option_index = 0;
    bool end = true;
    while(end){
        static struct option long_options[] = {
                {"--verbose", no_argument, &verbose_flag, 1},
                {"--implementation", required_argument, nullptr, 'i'},
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
        }
    }
    cout<<"is_verbose: "<<verbose_flag<<endl;
    cout<<"is_i: "<<i_flag<<endl;

    if(i_flag == 1){
        string str(cvalue);
        cout<<str<<endl;}
}
