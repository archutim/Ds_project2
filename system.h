#ifndef SYSTEM
#define SYSTEM
#include "steppostion.h"
#include <stack>
#include <queue>
    class System: public Map{
        public:
            void readmap();
            void showmap();
            void CalculateStep(int, int, int);
            void getinfo();
            int getir() {   return ir;  }
            int getjr() {   return jr;  }
            void MopFloor();
            void findgoway(int, int, int);
            void findbackway(int, int, int);
            //void outputfile(void);
    };
#endif