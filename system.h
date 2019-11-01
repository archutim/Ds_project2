#ifndef SYSTEM
#define SYSTEM
#include "steppostion.h"
    class System{
        private:
            int** map, **done;
            int* stepinfo;
            int width, height, step, ir, jr, maxstep;
            Steppostion* steppostion;
        public:
            System():map(nullptr), width(0), height(0), step(0), maxstep(0){}
            void readmap();
            void showmap();
            void CalculateStep(int, int, int);
            void getinfo();
            int getir() {   return ir;  }
            int getjr() {   return jr;  }
            //void MopFloor();
    };
#endif