#include "system.h"
#include <iostream>
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
    int k;
    path = new Path(ir, jr);
    Path* temp = path;
    Path* temp1;
    while(maxstep){
        for(int i=steppostion[maxstep].number;i>=0;i--){
            if(done[steppostion[maxstep].pos_i[i]][steppostion[maxstep].pos_j[i]]==0){
                System::findgoway(steppostion[maxstep].pos_i[i], steppostion[maxstep].pos_j[i], maxstep);
                totalpath--;
                System::findbackway(steppostion[maxstep].pos_i[i], steppostion[maxstep].pos_j[i], maxstep);
            }
        }
        maxstep--;
    }
    if(totalpath>0){
        path->next = new Path(ir, jr);
        path = temp->next;
        delete temp;
        temp = path;
        while(temp!=nullptr){
            if(temp->next!=nullptr){
                if(temp->x == temp->next->x && temp->y == temp->next->y){
                    temp1 = temp->next;
                    temp->next = temp->next->next;
                    delete temp1;
                    temp1 = nullptr;
                }
            }
            temp=temp->next;
        }
    }
    printf("%d\n", totalpath);
    while(path!=nullptr){
        printf("(%d,%d)\n", path->x, path->y);
        path=path->next;
    }
}
void System::findgoway(int i, int j , int distance){
    done[i][j]=1;
    if(power/2>distance+2){ //can mop more floor
        // not done && bigger
        if(done[i-1][j]==0 && map[i-1][j]>map[i][j])        findgoway(i-1, j, distance+2);
        else if(done[i+1][j]==0 && map[i+1][j]>map[i][j])   findgoway(i+1, j, distance+2);
        else if(done[i][j-1]==0 && map[i][j-1]>map[i][j])   findgoway(i, j-1, distance+2);
        else if(done[i][j+1]==0 && map[i][j+1]>map[i][j])   findgoway(i, j+1, distance+2);
        else{   // not done && equal
            if(done[i-1][j]==0 && map[i-1][j]==map[i][j])       findgoway(i-1, j, distance+1);
            else if(done[i+1][j]==0 && map[i+1][j]==map[i][j])  findgoway(i+1, j, distance+1);              
            else if(done[i][j-1]==0 && map[i][j-1]==map[i][j])  findgoway(i, j-1, distance+1);                
            else if(done[i][j+1]==0 && map[i][j+1]==map[i][j])  findgoway(i, j+1, distance+1);
            else{   // not done && smaller
                if(done[i-1][j]==0)         findgoway(i-1, j, distance);
                else if(done[i+1][j]==0)    findgoway(i+1, j, distance);
                else if(done[i][j-1]==0)    findgoway(i, j-1, distance);
                else if(done[i][j+1]==0)    findgoway(i, j+1, distance);
                else{   // done && smaller
                    if(done[i-1][j]>0 && map[i-1][j]<map[i][j]) findgoway(i-1, j, distance);
                    else if(done[i+1][j]>0 && map[i+1][j]<map[i][j]) findgoway(i+1, j, distance);
                    else if(done[i][j-1]>0 && map[i][j-1]<map[i][j]) findgoway(i, j-1, distance);
                    else if(done[i][j+1]>0 && map[i][j+1]<map[i][j]) findgoway(i, j+1, distance);
                    else {path->next = new Path(ir, jr);  path = path->next;totalpath++;}
                }
            }
        }
    }
    else{ //just go back for recharging
        // not done && smaller
        if(done[i-1][j]==0 && map[i-1][j]<map[i][j])        findgoway(i-1, j, distance);
        else if(done[i+1][j]==0 && map[i+1][j]<map[i][j])   findgoway(i+1, j, distance);
        else if(done[i][j-1]==0 && map[i][j-1]<map[i][j])   findgoway(i, j-1, distance);
        else if(done[i][j+1]==0 && map[i][j+1]<map[i][j])   findgoway(i, j+1, distance);
        else{   // done && smaller
            if(done[i-1][j]>0 && map[i-1][j]<map[i][j])     findgoway(i-1, j, distance);
            else if(done[i+1][j]>0 && map[i+1][j]<map[i][j])findgoway(i+1, j, distance);
            else if(done[i][j-1]>0 && map[i][j-1]<map[i][j])findgoway(i, j-1, distance);
            else if(done[i][j+1]>0 && map[i][j+1]<map[i][j])findgoway(i, j+1, distance);
            else {path->next = new Path(ir, jr);  path = path->next;totalpath++;}
        }
    }
    path->next = new Path(i, j);
    path = path->next;
    totalpath++;
}
void System::findbackway(int i, int j , int distance){
    path->next = new Path(i, j);
    path = path->next;
    totalpath++;
    done[i][j]=1;
    if(power/2>distance+2){ //can mop more floor
        // not done && bigger
        if(done[i-1][j]==0 && map[i-1][j]>map[i][j])        findbackway(i-1, j, distance+2);
        else if(done[i+1][j]==0 && map[i+1][j]>map[i][j])   findbackway(i+1, j, distance+2);
        else if(done[i][j-1]==0 && map[i][j-1]>map[i][j])   findbackway(i, j-1, distance+2);
        else if(done[i][j+1]==0 && map[i][j+1]>map[i][j])   findbackway(i, j+1, distance+2);
        else{   // not done && equal
            if(done[i-1][j]==0 && map[i-1][j]==map[i][j])       findbackway(i-1, j, distance+1);
            else if(done[i+1][j]==0 && map[i+1][j]==map[i][j])  findbackway(i+1, j, distance+1);              
            else if(done[i][j-1]==0 && map[i][j-1]==map[i][j])  findbackway(i, j-1, distance+1);                
            else if(done[i][j+1]==0 && map[i][j+1]==map[i][j])  findbackway(i, j+1, distance+1);
            else{   // not done && smaller
                if(done[i-1][j]==0)         findbackway(i-1, j, distance);
                else if(done[i+1][j]==0)    findbackway(i+1, j, distance);
                else if(done[i][j-1]==0)    findbackway(i, j-1, distance);
                else if(done[i][j+1]==0)    findbackway(i, j+1, distance);
                else{   // done && smaller
                    if(done[i-1][j]>0 && map[i-1][j]<map[i][j]) findbackway(i-1, j, distance);
                    else if(done[i+1][j]>0 && map[i+1][j]<map[i][j]) findbackway(i+1, j, distance);
                    else if(done[i][j-1]>0 && map[i][j-1]<map[i][j]) findbackway(i, j-1, distance);
                    else if(done[i][j+1]>0 && map[i][j+1]<map[i][j]) findbackway(i, j+1, distance);
                    //else que.push({ir, jr});
                }
            }
        }
    }
    else{ //just go back for recharging
        // not done && smaller
        if(done[i-1][j]==0 && map[i-1][j]<map[i][j])        findbackway(i-1, j, distance);
        else if(done[i+1][j]==0 && map[i+1][j]<map[i][j])   findbackway(i+1, j, distance);
        else if(done[i][j-1]==0 && map[i][j-1]<map[i][j])   findbackway(i, j-1, distance);
        else if(done[i][j+1]==0 && map[i][j+1]<map[i][j])   findbackway(i, j+1, distance);
        else{   // done && smaller
            if(done[i-1][j]>0 && map[i-1][j]<map[i][j])     findbackway(i-1, j, distance);
            else if(done[i+1][j]>0 && map[i+1][j]<map[i][j])findbackway(i+1, j, distance);
            else if(done[i][j-1]>0 && map[i][j-1]<map[i][j])findbackway(i, j-1, distance);
            else if(done[i][j+1]>0 && map[i][j+1]<map[i][j])findbackway(i, j+1, distance);
            //else que.push({ir, jr});
        }
    }
}