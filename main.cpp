#include <iostream>
#include "map.h"
#include "system.h"
#include "system.cpp"
#include "steppostion.h"
#include "path.h"
using namespace std;
int main(){
<<<<<<< HEAD
    printf("OHHHHHHH\n");
=======
    printf("Hello World!\n");
>>>>>>> 660962b4cdcf73a9a63210ffeba779016d5643c7
    cout << "oh my god << endl;
    System system;
    system.readmap(); 
    system.CalculateStep();
    system.MopFloor();
    system.outputfile();
    return 0;
}