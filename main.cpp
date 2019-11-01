#include <iostream>
#include "map.h"
#include "system.h"
#include "system.cpp"
#include "steppostion.h"
using namespace std;
int main(){
    System system;
    system.readmap();
    system.CalculateStep(system.getir(), system.getjr(), 0);
    system.getinfo();
    system.showmap();
    return 0;
}