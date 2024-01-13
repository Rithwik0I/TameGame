#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

 bool Dead=false;

void GameOver()
{
    system("clear");
    printf("Game Over!!");

}

void displayBoard(char arr[5][5], int e, char Player) //This function clears the console and displays the board.
{
    system("clear");
    Dead=true;
    for(int i = 0 ; i<e ; i++)
    {
        for(int j=0 ; j<e ; j++)
        {
            if(arr[i][j]==Player)
                Dead = false;
            printf("%c   ",arr[i][j]);
        }
        printf("\n");
    }
    Sleep(500);
    if(Dead)
        {
            GameOver();
        }
}

void enemyMove(char arr[5][5], char enmyJump, char enmyLongJump, char enmyPl, char floor, int rowPos, int colPos)
{
    for(int i = 0 ; i<5 ; i++)
    {
        for(int j=0 ; j<5 ; j++)
        {
            if(arr[i][j] == enmyJump)
            {
                if((i-1==colPos || i==colPos || i+1==colPos)&&(j-1==rowPos || j==rowPos || j+1==rowPos))
                {
                    PlayerAttack(enmyJump, 'X', 'o', i,j,arr);
                    Dead = true;
                    break;
                }
                if(i > colPos)
                {
                    arr[i][j] = floor;
                    arr[i-1][j] = enmyJump;
                    break;
                }
                else if(i < colPos)
                {
                    arr[i][j] = floor;
                    arr[i+1][j] = enmyJump;
                    break;
                }
                else if(j < rowPos)
                {
                    arr[i][j] = floor;
                    arr[i][j+1] = enmyJump;
                    break;
                }
                else if (j>rowPos)
                {
                    arr[i][j] = floor;
                    arr[i][j-1] = enmyJump;
                    break;
                }
            }
        }

    }

}

void PlayerAttack(char Player, char Pattack, char floor, int rowPos, int colPos, char arr[5][5])
{
    if(colPos != 0)         //If Player is all the way left
    {
        if(rowPos != 0)     //If Player is at the top
            arr[colPos-1][rowPos-1] = Pattack;
        if(rowPos != 4)     //If Player is at the bottom
            arr[colPos-1][rowPos+1] = Pattack;
        arr[colPos-1][rowPos] = Pattack;

    }

    if(colPos != 4)         //If Player is all the way to the right
    {
        if(rowPos != 0)     //If Player is at the top
            arr[colPos+1][rowPos-1] = Pattack;
        if(rowPos != 4)     //If Player is at the bottom
            arr[colPos+1][rowPos+1] = Pattack;
         arr[colPos+1][rowPos] = Pattack;
    }
    if(rowPos != 0)
        arr[colPos][rowPos-1] = Pattack;
    if(rowPos != 4)
        arr[colPos][rowPos+1] = Pattack;


    displayBoard(arr,5,Player);                //DISPLAY


    arr[colPos][rowPos+1] = floor;
    arr[colPos][rowPos-1] = floor;
    arr[colPos+1][rowPos-1] = floor;
    arr[colPos+1][rowPos] = floor;
    arr[colPos+1][rowPos+1] = floor;
    arr[colPos-1][rowPos-1] = floor;
    arr[colPos-1][rowPos] = floor;
    arr[colPos-1][rowPos+1] = floor;


    // turn back
}

int main()
{
    srand(time(0));
    bool Dead = false;
    int rowPos = rand()%5, colPos = rand()%5;
    char choice, floor = 'o', player = 'P', Pattack = 'X', enmy1='Q';
    char moveup = 'w' ,movedown='s',moveleft='a', moveright='d';
    int e = 5;
    char arr[5][5]={{floor,floor,floor,floor,floor},{floor,floor,floor,floor,floor},{floor,floor,floor,floor,floor},{floor,floor,floor,floor,floor},{floor,floor,floor,floor,floor}};
    arr[colPos][rowPos] = player;
    arr[rand()%5][rand()%5] = enmy1;
    while(1)
    {
        if(Dead)
        {
            GameOver();
            break;
        }

        displayBoard(arr,5, player);                    //DISPLAY
        scanf("%c" , &choice);
        if(choice == 'x')
            exit(0);
        else if(choice == moveup){//moves up player
            if(colPos!=0){
                arr[colPos][rowPos]=floor;
                colPos--;
                arr[colPos][rowPos] = player;
            }
            enemyMove(arr,enmy1,'q','w', floor, rowPos,colPos);
        }
        else if(choice==movedown){
            if(colPos != e-1){
                arr[colPos][rowPos]=floor;
                colPos++;
                arr[colPos][rowPos] = player;
            }
            enemyMove(arr,enmy1,'q','w', floor, rowPos,colPos);
        }
        else if(choice==moveright){
            if(rowPos != e-1){
                arr[colPos][rowPos]=floor;
                rowPos++;
                arr[colPos][rowPos] = player;
            }
            enemyMove(arr,enmy1,'q','w', floor, rowPos,colPos);
        }
        else if(choice==moveleft){
            if(rowPos != 0){
                arr[colPos][rowPos]=floor;
                rowPos--;
                arr[colPos][rowPos] = player;
            }
            enemyMove(arr,enmy1,'q','w', floor, rowPos,colPos);
        }

        else if (choice == 'j')
            PlayerAttack(player, Pattack, floor, rowPos, colPos, arr);
            enemyMove(arr,enmy1,'q','w', floor, rowPos, colPos);

    }






    return 0;
}
