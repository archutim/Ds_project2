#include "system.h"
#include <iostream>
void System::readmap(){
    FILE* fp;
    char garb, ch;
    if((fp = fopen("floor.data", "r")) == nullptr){
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
void System::CalculateStep(){
    if(power > 10000)
        steppostion = new Steppostion[10001];
    else
        steppostion = new Steppostion[power/2+2];
    steppostion[0].number=1;    steppostion[0].pos_i = new int(ir);    steppostion[0].pos_j = new int(jr);
    int i;
    for(i=0;steppostion[i].number!=0;i++){
        steppostion[i+1].pos_i = new int[steppostion[i].number*4];
        steppostion[i+1].pos_j = new int[steppostion[i].number*4];
        for(int j=0;j<steppostion[i].number;j++)
            Visitneighbor(steppostion[i].pos_i[j], steppostion[i].pos_j[j], i);
    }
    maxstep = i-1;
}
void System::Visitneighbor(int i, int j, int _step){
    if(i>0){
        if(map[i-1][j]==0 || map[i-1][j]>_step+1){
            map[i-1][j]=_step+1;
            steppostion[_step+1].pos_i[steppostion[_step+1].number] = i-1;
            steppostion[_step+1].pos_j[steppostion[_step+1].number] = j;
            steppostion[_step+1].number++;
        }
    }
    if(i+1<height){
        if(map[i+1][j]==0 || map[i+1][j]>_step+1){
            map[i+1][j]=_step+1;
            steppostion[_step+1].pos_i[steppostion[_step+1].number] = i+1;
            steppostion[_step+1].pos_j[steppostion[_step+1].number] = j;
            steppostion[_step+1].number++;
        }
    }
    if(j>0){
        if(map[i][j-1]==0 || map[i][j-1]>_step+1){
            map[i][j-1]=_step+1;
            steppostion[_step+1].pos_i[steppostion[_step+1].number] = i;
            steppostion[_step+1].pos_j[steppostion[_step+1].number] = j-1;
            steppostion[_step+1].number++;
        }
    }
    if(j+1<width){
        if(map[i][j+1]==0 || map[i][j+1]>_step+1){
            map[i][j+1]=_step+1;
            steppostion[_step+1].pos_i[steppostion[_step+1].number] = i;
            steppostion[_step+1].pos_j[steppostion[_step+1].number] = j+1;
            steppostion[_step+1].number++;
        }
    }
}
void System::MopFloor(){
    int k;
    path = new Path(ir, jr);
    Path* temp = path;
    Path* temp1;
    if(maxstep<=power/2){
        while(maxstep){
            for(int i=steppostion[maxstep].number-1;i>=0;i--){
                if(done[steppostion[maxstep].pos_i[i]][steppostion[maxstep].pos_j[i]]==0){
                    System::findgoway(steppostion[maxstep].pos_i[i], steppostion[maxstep].pos_j[i], maxstep);
                    totalpath--;
                    System::findbackway(steppostion[maxstep].pos_i[i], steppostion[maxstep].pos_j[i], maxstep);
                }
            }
            maxstep--;
        }
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
void System::outputfile(){
    FILE* fp;
    if((fp = fopen("final.path", "w")) == nullptr){
        puts("File could not be opened");
    }      
    fprintf(fp, "%d\n", totalpath);
    int lastx = ir, lasty = jr-1, nowx, nowy;
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            if(done[i][j]==0)
                printf("error_1\n");
        }
    }
    while(path!=nullptr){
        if((abs(lastx-path->x)+abs(lasty-path->y))!=1){
            printf("error_2\n");
            printf("last:%d %d\n", lastx, lasty);
            printf("new:%d %d\n", path->x, path->y);
        }
        lastx = path->x;
        lasty = path->y;        
        if(map[path->x][path->y]==-1){
            printf("error_3\n");
            printf("%d %d\n", path->x, path->y);
        }
        fprintf(fp, "%d %d\n", path->x, path->y);
        path=path->next;
    } 
    fclose(fp);
}