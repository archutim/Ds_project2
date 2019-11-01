#ifndef MAP
#define MAP
#include "steppostion.h"
    class Map {
        protected:
            int** map, **done;
            int height, width, step, ir, jr;
            Steppostion* steppostion;
        public:
            Map():map(nullptr), done(nullptr),height(0), width(0),
                     step(0), ir(0), jr(0), steppostion(nullptr){}      
            ~Map(){
                for(int i=0;i<height;i++){
                    delete []map[i];
                    delete []done[i];
                }
                delete []steppostion;
            }
    };
#endif