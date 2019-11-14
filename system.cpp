#include "system.h"
#include <iostream>
#include <stack>
#include <queue>
void System::readmap(){
    FILE* fp;
    char garb, ch;
    if((fp = fopen("input.data", "r")) == nullptr){
        puts("File could not be opened");
    }    
    fscanf(fp, "%d%d%d", &height, &width, &power);
    //dynamic two dimensional array
    map = new int*[height];
    for(int i=0;i<height;i++)
        map[i] = new int[width];
    //dynamic two dimensional array
    done = new int*[height];
    for(int i=0;i<height;i++)
        done[i] = new int[width];
    //set map and done
    for(int i=0;i<height;i++){
        fscanf(fp, "%c", &garb);
        for(int j=0;j<width;j++){
            fscanf(fp, "%c", &ch);
            if(ch=='1'){
                map[i][j]=-1;
                done[i][j]=-1;
            }
            else if(ch=='0'){
                map[i][j]=0;
                done[i][j]=0;
            }
            else{
                map[i][j]=-2; 
                done[i][j]=-2;   
                ir=i;
                jr=j;
            }            
        }
    }
    fclose(fp);
}
void System::showmap(){
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++)
            printf("%d ", map[i][j]);
        printf("\n");
    }
    printf("recharge position:%d %d\n", ir, jr);
}
void System::CalculateStep(int i, int j, int _step){
    if(i>0){
        if(map[i-1][j]==0 || map[i-1][j]>_step+1){
            map[i-1][j]=_step+1;
            System::CalculateStep(i-1, j, _step+1);
        }
    }
    if(i+1<height){
        if(map[i+1][j]==0 || map[i+1][j]>_step+1){
            map[i+1][j]=_step+1;
            System::CalculateStep(i+1, j, _step+1);
        }
    }
    if(j>0){
        if(map[i][j-1]==0 || map[i][j-1]>_step+1){
            map[i][j-1]=_step+1;
            System::CalculateStep(i, j-1, _step+1);
        }
    }
    if(j+1<width){
        if(map[i][j+1]==0 || map[i][j+1]>_step+1){
            map[i][j+1]=_step+1;
            System::CalculateStep(i, j+1, _step+1);
        }
    }
}
void System::getinfo(){
    int* stepinfo;
    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++){
            if(map[i][j]==-1)   map[i][j]=0;
            if(map[i][j]>maxstep) maxstep=map[i][j];
        }
    //dynamic one dimensional array
    stepinfo = new int[maxstep+1];
    for(int i=0;i<=maxstep;i++)
        stepinfo[i]=0;
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            if(map[i][j]!=-2)
                stepinfo[map[i][j]]++;
        }
    }
    //dynamic one dimensional Steppostion array
    steppostion = new Steppostion[maxstep+1];
    for(int i=0;i<=maxstep;i++){
        steppostion[i].pos_i = new int[stepinfo[i]];
        steppostion[i].pos_j = new int[stepinfo[i]];
    }
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            if(map[i][j]!=-2){
                steppostion[map[i][j]].number++;
                steppostion[map[i][j]].pos_i[steppostion[map[i][j]].number] = i;
                steppostion[map[i][j]].pos_j[steppostion[map[i][j]].number] = j;
            }
        }
    }
    for(int i=0;i<=maxstep;i++)
        printf("%d step: %d\n", i, stepinfo[i]);
    delete []stepinfo;
}
void System::MopFloor(){
    std::stack<std::pair<int, int>> sta;
    std::queue<std::pair<int, int>> que;
    int k;
    while(maxstep){
        for(int i=steppostion[maxstep].number;i>=0;i--){
            if(done[steppostion[maxstep].pos_i[i]][steppostion[maxstep].pos_j[i]]==0){
                System::findway(steppostion[maxstep].pos_i[i], steppostion[maxstep].pos_j[i], maxstep, sta);
                //std::cin >> k;
                while(!sta.empty()){
                    printf("(%d,%d)\n", sta.top().first, sta.top().second);
                    sta.pop();
                }
                //System::showmap();
                System::findway(steppostion[maxstep].pos_i[i], steppostion[maxstep].pos_j[i], maxstep, que);
                //std::cin >> k;
                que.pop();
                while(!que.empty()){
                    printf("(%d,%d)\n", que.front().first, que.front().second);
                    que.pop();
                }
                //System::showmap();
            }
        }
        maxstep--;
    }
    printf("(%d,%d)\n", ir, jr);
}
void System::findway(int i, int j , int distance, std::stack<std::pair<int, int>>& sta){
    sta.push({i, j});
    done[i][j]=1;
    if(power/2>distance+2){ //can mop more floor
        // not done && bigger
        if(done[i-1][j]==0 && map[i-1][j]>map[i][j])        findway(i-1, j, distance+2, sta);
        else if(done[i+1][j]==0 && map[i+1][j]>map[i][j])   findway(i+1, j, distance+2, sta);
        else if(done[i][j-1]==0 && map[i][j-1]>map[i][j])   findway(i, j-1, distance+2, sta);
        else if(done[i][j+1]==0 && map[i][j+1]>map[i][j])   findway(i, j+1, distance+2, sta);
        else{   // not done && equal
            if(done[i-1][j]==0 && map[i-1][j]==map[i][j])       findway(i-1, j, distance+1, sta);
            else if(done[i+1][j]==0 && map[i+1][j]==map[i][j])  findway(i+1, j, distance+1, sta);              
            else if(done[i][j-1]==0 && map[i][j-1]==map[i][j])  findway(i, j-1, distance+1, sta);                
            else if(done[i][j+1]==0 && map[i][j+1]==map[i][j])  findway(i, j+1, distance+1, sta);
            else{   // not done && smaller
                if(done[i-1][j]==0)         findway(i-1, j, distance, sta);
                else if(done[i+1][j]==0)    findway(i+1, j, distance, sta);
                else if(done[i][j-1]==0)    findway(i, j-1, distance, sta);
                else if(done[i][j+1]==0)    findway(i, j+1, distance, sta);
                else{   // done && smaller
                    if(done[i-1][j]>0 && map[i-1][j]<map[i][j]) findway(i-1, j, distance, sta);
                    else if(done[i+1][j]>0 && map[i+1][j]<map[i][j]) findway(i+1, j, distance, sta);
                    else if(done[i][j-1]>0 && map[i][j-1]<map[i][j]) findway(i, j-1, distance, sta);
                    else if(done[i][j+1]>0 && map[i][j+1]<map[i][j]) findway(i, j+1, distance, sta);
                    else sta.push({ir, jr});
                }
            }
        }
    }
    else{ //just go back for recharging
        // not done && smaller
        if(done[i-1][j]==0 && map[i-1][j]<map[i][j])        findway(i-1, j, distance, sta);
        else if(done[i+1][j]==0 && map[i+1][j]<map[i][j])   findway(i+1, j, distance, sta);
        else if(done[i][j-1]==0 && map[i][j-1]<map[i][j])   findway(i, j-1, distance, sta);
        else if(done[i][j+1]==0 && map[i][j+1]<map[i][j])   findway(i, j+1, distance, sta);
        else{   // done && smaller
            if(done[i-1][j]>0 && map[i-1][j]<map[i][j])     findway(i-1, j, distance, sta);
            else if(done[i+1][j]>0 && map[i+1][j]<map[i][j])findway(i+1, j, distance, sta);
            else if(done[i][j-1]>0 && map[i][j-1]<map[i][j])findway(i, j-1, distance, sta);
            else if(done[i][j+1]>0 && map[i][j+1]<map[i][j])findway(i, j+1, distance, sta);
            else sta.push({ir, jr});
        }
    }
}
void System::findway(int i, int j , int distance, std::queue<std::pair<int, int>>& que){
    que.push({i, j});
    done[i][j]=1;
    if(power/2>distance+2){ //can mop more floor
        // not done && bigger
        if(done[i-1][j]==0 && map[i-1][j]>map[i][j])        findway(i-1, j, distance+2, que);
        else if(done[i+1][j]==0 && map[i+1][j]>map[i][j])   findway(i+1, j, distance+2, que);
        else if(done[i][j-1]==0 && map[i][j-1]>map[i][j])   findway(i, j-1, distance+2, que);
        else if(done[i][j+1]==0 && map[i][j+1]>map[i][j])   findway(i, j+1, distance+2, que);
        else{   // not done && equal
            if(done[i-1][j]==0 && map[i-1][j]==map[i][j])       findway(i-1, j, distance+1, que);
            else if(done[i+1][j]==0 && map[i+1][j]==map[i][j])  findway(i+1, j, distance+1, que);              
            else if(done[i][j-1]==0 && map[i][j-1]==map[i][j])  findway(i, j-1, distance+1, que);                
            else if(done[i][j+1]==0 && map[i][j+1]==map[i][j])  findway(i, j+1, distance+1, que);
            else{   // not done && smaller
                if(done[i-1][j]==0)         findway(i-1, j, distance, que);
                else if(done[i+1][j]==0)    findway(i+1, j, distance, que);
                else if(done[i][j-1]==0)    findway(i, j-1, distance, que);
                else if(done[i][j+1]==0)    findway(i, j+1, distance, que);
                else{   // done && smaller
                    if(done[i-1][j]>0 && map[i-1][j]<map[i][j]) findway(i-1, j, distance, que);
                    else if(done[i+1][j]>0 && map[i+1][j]<map[i][j]) findway(i+1, j, distance, que);
                    else if(done[i][j-1]>0 && map[i][j-1]<map[i][j]) findway(i, j-1, distance, que);
                    else if(done[i][j+1]>0 && map[i][j+1]<map[i][j]) findway(i, j+1, distance, que);
                    //else que.push({ir, jr});
                }
            }
        }
    }
    else{ //just go back for recharging
        // not done && smaller
        if(done[i-1][j]==0 && map[i-1][j]<map[i][j])        findway(i-1, j, distance, que);
        else if(done[i+1][j]==0 && map[i+1][j]<map[i][j])   findway(i+1, j, distance, que);
        else if(done[i][j-1]==0 && map[i][j-1]<map[i][j])   findway(i, j-1, distance, que);
        else if(done[i][j+1]==0 && map[i][j+1]<map[i][j])   findway(i, j+1, distance, que);
        else{   // done && smaller
            if(done[i-1][j]>0 && map[i-1][j]<map[i][j])     findway(i-1, j, distance, que);
            else if(done[i+1][j]>0 && map[i+1][j]<map[i][j])findway(i+1, j, distance, que);
            else if(done[i][j-1]>0 && map[i][j-1]<map[i][j])findway(i, j-1, distance, que);
            else if(done[i][j+1]>0 && map[i][j+1]<map[i][j])findway(i, j+1, distance, que);
            //else que.push({ir, jr});
        }
    }
}