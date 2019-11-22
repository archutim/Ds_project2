#ifndef PATH
#define PATH
    class Path {
        friend class System;
        protected:
            Path* next;
            int x, y;
        public:
            Path(int x, int y):x(x), y(y), next(nullptr){}      
            ~Path(){
                delete &x;
                delete &y;
            }
    };
#endif