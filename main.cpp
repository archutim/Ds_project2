#include <iostream>
#include "map.h"
#include "system.h"
#include "system.cpp"
#include "steppostion.h"
#include "path.h"
using namespace std;
int main(){
    System system;
    system.readmap();
    system.CalculateStep(system.getir(), system.getjr(), 0);
    system.getinfo();
    system.MopFloor();
    system.outputfile();
    return 0;
}