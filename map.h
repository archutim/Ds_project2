#ifndef MAP
#define MAP
#include "steppostion.h"
#include "path.h"
    class Map {
        protected:
            int** map, **done;
            int height, width, power, ir, jr, maxstep, totalpath;
            Path* path;
            Steppostion* steppostion;
        public:
            Map():map(nullptr), done(nullptr),height(0), width(0),
                     power(0), ir(0), jr(0), maxstep(0), totalpath(0), path(nullptr), steppostion(nullptr){}      
            ~Map(){
                for(int i=0;i<height;i++){
                    delete []map[i];
                    delete []done[i];
                }
                delete []steppostion;
            }
    };
#endif