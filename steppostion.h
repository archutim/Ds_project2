#ifndef STEPPOSTION
#define STEPPOSTION
    class Steppostion{
        friend class System;
        private:
            int number;
            int remaining;
            int* pos_i, *pos_j;
        public:
            Steppostion():number(0), remaining(0){}
            ~Steppostion(){
                delete []pos_i;
                delete []pos_j;
            }
    };
#endif