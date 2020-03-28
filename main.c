#include <stdio.h>
#include "snake.c"
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
int is_running=0;
void screen_reset(){
    HANDLE h_out;
    COORD pos;
    h_out = GetStdHandle(STD_OUTPUT_HANDLE);
    pos.X=0;
    pos.Y=0;
    SetConsoleCursorPosition(h_out,pos);
}

int welcome(){
    printf("Hello and welcome to Cnake\n");
    printf("Please choose a number between 1 to 3 to determine the difficulty\nthen press ENTER. \n");
    printf("1-I have two left hands\n2-I can handle slow games\n3-I'm pro\n");

    printf("I CHOOSE: ");
    int input;
    scanf("%d",&input);
    if(input!=1 && input !=2 && input !=3) {
        printf("HOW COULD YOU???");
        exit(0);
}
    return input;
}


int main(){
    int difficulty = welcome();


    snake_init();
    randomize();

    while(is_running==0){
        randomize();
        print_borders();
        screen_reset();
        movement(difficulty);
        tail_remove();

        if(difficulty==1) Sleep(90);
        else if(difficulty==2) Sleep(50);
        else Sleep(5);
        is_running = is_over();





    }

    return 0;
}

