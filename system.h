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
            void findway(int, int, int, std::stack<std::pair<int, int> >&);
            void findway(int, int, int, std::queue<std::pair<int, int> >&);
    };
#endif