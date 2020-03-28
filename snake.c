#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>
#include <conio.h>
#define M 70
#define K 28
FILE *f;
int Field[K][M];
int x,y;
int Gy;
int head,tail;
int apple;
int a,b;
int dir='s';
int score=0;
int high_score=0;
int game;
int user_input;

int is_over(){
    if(game==0) return 0;
    return 1;
}


void randomize(){
    srand(time(0));
    a = 1+rand()%26;
    b = 1+rand()%68;

    if(apple == 0 && Field[a][b]==0){
        Field[a][b]=-1;
        apple = 1;
    }
}


int print_borders(){
     for(int i=0;i<M+2;i++){
        if(i==0) printf("%c",201);
        else if(i==M+1) printf("%c",187);
        else printf("%c",205);
    }

    printf("\n");


    for(int i=0;i<K;i++){
        printf("%c",186);
        for(int j=0;j<M;j++){
            if(Field[i][j]==0) printf(" ");
            if(Field[i][j]>0 && Field[i][j]!=head) printf("%c",176);
            if(Field[i][j]==head) printf("%c",178);
            if(Field[i][j]==-1) printf("%c",236);
            if(j==M-1) printf("%c\n",186);
        }

    }

    for(int i=0;i<M+2;i++){
        if(i==0) printf("%c",200);
        else if(i==M+1) printf("%c",188);
        else printf("%c",205);
    }
    printf("Score: %d, High Score: %d",score,high_score);
    printf("\n");
}

void snake_init(){
    f=fopen("High_Scores.txt","r");
    fscanf(f,"%d",&high_score);
    fclose(f);
    for(int i=0;i<K;i++){
        for(int j=0;j<M;j++){
            Field[i][j]=0;
        }
    }
    x=K/2;
    y=M/2;
    head=5;
    tail=1;
    Gy=y;
    apple=0;
    for(int i=0;i<head;i++){
        Gy++;
        Field[x][Gy-head]=i+1;
    }

}

int get_ch(){
    if(_kbhit()){
        return _getch();
    }
    return -1;
}
void game_over(){
    printf("\a");
    Sleep(1500);
    system("Cls");
    if(score>high_score){
        printf("    New High Score: %d!!!\n\n",score);
        system("pause");
        f=fopen("high_score.txt","w");
        fprintf(f,"%d",score);
        fclose(f);
    }
    system("Cls");
    printf("\n\n              GAME OVER");
    printf("                  SCORE: %d \n\n ",score);
    printf("                  PRESS ENTER to play again or ESC to exit . . .  \n");
    game = 1;

    while(1){
        user_input = get_ch();
        if(user_input==13){
            game =0;
            snake_init();
            break;
        }
        else if(user_input == 27){
            game =1;
            break;
        }
    }

}

void movement(int dif){
    user_input = get_ch();
    user_input = tolower(user_input);
    if(((user_input == 'd'||user_input =='a'))||((user_input == 's' || user_input == 'w'))&&(abs(dir-user_input))>5){
        dir = user_input;
    }


    if(dir == 'd'){
        y++;
        if(Field[x][y]!=0 && Field[x][y]!=-1) { game_over(); }
        if(y==M-1){
            if(dif==1)y=0;
            else game_over();
        }
        if(Field[x][y]==-1){
            apple =0;
            score+=5;
            tail -=dif;
        }

        head++;
        Field[x][y] = head;
    }

    if(dir == 'a'){
        y--;
        if(Field[x][y]!=0 && Field[x][y]!=-1) { game_over(); }
        if(y==0) {
          if(dif==1) y=M-1;
          else game_over();
        }
        if(Field[x][y]==-1){
            apple =0;
            score+=5;
            tail -=dif;
        }
        head++;
        Field[x][y] = head;
    }

    if(dir == 'w'){
        x--;
        if(Field[x][y]!=0 && Field[x][y]!=-1) { game_over(); }
        if(x==-1) {
            if(dif==1) x = K-1;
            else game_over();
        }
        if(Field[x][y]==-1){
            apple =0;
            score+=5;
            tail -=dif;
        }
        head++;
        Field[x][y] = head;
    }

    if(dir == 's'){
        x++;
        if(Field[x][y]!=0 && Field[x][y]!=-1) { game_over(); }
        if(x==K-1){
         if(dif==1) x=0;
         else game_over();
        }
        if(Field[x][y]==-1){
            apple =0;
            score+=5;
            tail -=dif;
        }
        head++;
        Field[x][y] = head;
    }

}

void tail_remove(){
    for(int i=0;i<K;i++){
        for(int j=0;j<M;j++){
            if(Field[i][j]==tail){
                Field[i][j] = 0;
            }
        }
    }
    tail++;

}
