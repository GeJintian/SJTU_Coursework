#include <iostream>
#include <iomanip>
#include "class.h"

using namespace std;
int main(){
    int graden;
    char gradec;
    cout<<"Input two space seprated grades(1st in %, 2nd in letter): ";
    cin>>graden>>gradec;
    Grade grade1,grade2;
    grade1.gradeprct(graden);grade2.gradelrt(gradec);
    cout<<"Grade: "<<graden<<"->"<<grade1.lrt()<<endl;
    cout<<"Grade: "<<grade2.prct()<<"->"<<gradec<<endl;
    return 0;
}