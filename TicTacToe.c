#include <stdlib.h>
#include <time.h>
#include <stdio.h>
char arr[3][3];
int winner = 0;
int spaces = 9;
void board()
{
    printf(" %c | %c | %c \n", arr[0][0], arr[0][1], arr[0][2]);
    printf(" --------- \n");
    printf(" %c | %c | %c \n", arr[1][0], arr[1][1], arr[1][2]);
    printf(" --------- \n");
    printf(" %c | %c | %c \n", arr[2][0], arr[2][1], arr[2][2]);
}

void resetboard(){
    for ( int i = 0; i < 3; i++){
        for ( int j = 0; j < 3; j++){
            arr[i][j] = ' ';
        }
    }
}

int checkwinner()
{
    for ( int i = 0; i < 3; i++)
    {
        if ( arr[i][0] == 'x' && arr[i][1] == 'x' && arr[i][2] == 'x'){
            printf("Player wins!!!\n");
            winner = 1;
        }
        if ( arr[0][i] == 'x' && arr[1][i] == 'x' && arr[2][i] == 'x'){
            printf("Player wins!!!\n");
            winner = 1;
        }
        if ( arr[0][0] == 'x' && arr[1][1] == 'x' && arr[2][2] == 'x'){
            printf("Player wins!!!\n");
            winner = 1;
        }
        if ( arr[0][2] == 'x' && arr[1][1] == 'x' && arr[2][0] == 'x'){
            printf("Player wins!!!\n");
            winner = 1;
        }
        
    }
    for ( int i = 0; i < 3; i++)
    {
        if ( arr[i][0] == 'o' && arr[i][1] == 'o' && arr[i][2] == 'o'){
            printf("Computer wins!!!\n");
            winner = 1;
        }
        if ( arr[0][i] == 'o' && arr[1][i] == 'o' && arr[2][i] == 'o'){
            printf("Computer wins!!!\n");
            winner = 1;
        }
        if ( arr[0][0] == 'o' && arr[1][1] == 'o' && arr[2][2] == 'o'){
            printf("computer wins!!!\n");
            winner = 1;
        }
        if ( arr[0][2] == 'o' && arr[1][1] == 'o' && arr[2][0] == 'o'){
            printf("computer wins!!!\n");
            winner = 1;
        }
        
    }
    return winner;
}

void playermove(){
    int row, column;
    do{
        printf("Enter row: ");
        scanf("%d", &row);
        row--;
        printf("Enter column: ");
        scanf("%d", &column);
        column--;
        if ( arr[row][column] == ' '){
            arr[row][column] = 'x';
            break;
        }
        else if (spaces == 0 )
        {
            printf("Draw!!");
        }    
        else{
            printf("Invalid move!\n");
        }
    }
    while(arr[row-1][column-1] != ' ');
        
}

void computermove() {
    int row, column;
    srand(time(0));
    while (1) {
        row = rand() % 3;
        column = rand() % 3;
        if (arr[row][column] == ' ') {
            arr[row][column] = 'o';
            break;
        }
        else if (spaces == 0 )
        {
            printf("Draw!!");
        }    
    }
}

int freespace()
{
    for ( int i = 0; i < 3; i++){
        for ( int j = 0; j < 3; j++){
            if (arr[i][j] != ' ')
            {
                spaces--;
            }
        }
    }
    if (spaces == 0 )
    {
        printf("Draw!!");
    }
    return spaces;
}

int main() {
    resetboard();
    while (checkwinner() != 1 && freespace() != 0)
    {
        printf("<xoxo---Tic-Tac-Toe---oxox>\n");
        checkwinner();
        board();
        freespace();
        playermove();
        freespace();
        checkwinner();
        computermove();
        printf("\033[2J\033[1;1H");
        freespace();
        checkwinner();
        
        
    }
    board();
    
    return 0;
}   
 
