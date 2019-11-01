#include "system.h"
#include <iostream>
void System::readmap(){
    FILE* fp;
    char garb, ch;
    if((fp = fopen("input.data", "r")) == nullptr){
        puts("File could not be opened");
    }    
    fscanf(fp, "%d%d%d", &height, &width, &step);
    //dynamic two dimensional array
    map = new int*[height];
    for(int i=0;i<height;i++)
        map[i] = new int[width];
    //dynamic two dimensional array
    done = new int*[height];
    for(int i=0;i<height;i++)
        done[i] = new int[width];
    //set map and done
    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++){
            done[i][j]=0;
            fscanf(fp, "%c%c", &garb, &ch);
            if(ch=='1'){
                map[i][j]=-1;
            }
            else if(ch=='0')    map[i][j]=0;
            else{
                map[i][j]=-2;    
                ir=i;
                jr=j;
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
    int maxstep=0;
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
        steppostion[i].number = stepinfo[i];
        steppostion[i].remaining = -1;
        steppostion[i].pos_i = new int[stepinfo[i]];
        steppostion[i].pos_j = new int[stepinfo[i]];
    }
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            if(map[i][j]!=-2){
                steppostion[map[i][j]].remaining++;
                steppostion[map[i][j]].pos_i[steppostion[map[i][j]].remaining] = i;
                steppostion[map[i][j]].pos_j[steppostion[map[i][j]].remaining] = j;
            }
        }
    }
    for(int i=0;i<=maxstep;i++)
        printf("%d step: %d\n", i, stepinfo[i]);
    delete []stepinfo;
}