#ifndef MAP
#define MAP
#include "steppostion.h"
    class Map {
        protected:
            int** map, **done;
            int height, width, power, ir, jr, maxstep;
            Steppostion* steppostion;
        public:
            Map():map(nullptr), done(nullptr),height(0), width(0),
                     power(0), ir(0), jr(0), maxstep(0), steppostion(nullptr){}      
            ~Map(){
                for(int i=0;i<height;i++){
                    delete []map[i];
                    delete []done[i];
                }
                delete []steppostion;
            }
    };
#endif