#include <iostream>
#include "map.h"
#include "system.h"
#include "system.cpp"
#include "steppostion.h"
#include "path.h"
using namespace std;
int main(){
    printf("Hello World!\n");
    System system;
    system.readmap(); 
    system.CalculateStep();
    system.MopFloor();
    system.outputfile();
    return 0;
}