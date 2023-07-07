// Name: Mert Can Bilgin
//Student ID: 2453025

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define ROWS 5
#define COLUMNS 4

int randomPowerTwo(int);
int shootMerge(int **, int, int, int);
void displayBoard(int **);
int fullorNot(int **);

int main()
{
    int **array;
    int i, j, number, row = 0, column = 0, max = 32, counter = 0, check = 0;
    char play_again = 'Y';

    srand(time(NULL));

    array = (int **)malloc(ROWS * sizeof(int*));//Rows are created dynamically.
    if(array == NULL){
        printf("Allocation failed!\n");//Allocation are checked.
        return -1;
    }
    for(i = 0; i < ROWS; i++){//Columns are created cynamically.
        array[i] = (int *)malloc(COLUMNS * sizeof(int));
        if(array[i] == NULL){//Allocation are checked.
            printf("Allocation failed!\n");
            return -1;
        }
    }

    printf("*Shoot Merge*\n");
    while(play_again == 'Y'){
        printf("Lets get started!\n");
        displayBoard(array);
        printf("\n");

        number = randomPowerTwo(max);//We start max value with 32

        for(i = 0; i < ROWS; i++){
            for(j = 0; j < COLUMNS; j++)
                array[i][j] = 0;
        }

        do{
            max = shootMerge(array, row, column, number);
            counter++;
            number = randomPowerTwo(max);
            displayBoard(array);
            printf("\n%d shot so far!\n\n", counter);
        }while(fullorNot(array) == 0);

        printf("The board is full now with %d shots!\n", counter);
        printf("Game over!\n");

        while(check == 0){
            fflush(stdin);
            printf("Would you like to play again (Y/N)? ");
            scanf("%c", &play_again);
            if(play_again == 'Y' || play_again == 'N')
                check = 1;
            else
                printf("That is not valid, please try again!\n");
        }

        if(play_again == 'N'){//When the player doesn't want to play more, we need to free the memory
            printf("Byeee!\n");
            for(i = 0; i < ROWS; i++)
                free(array[i]);
            free(array);
        }

        for(i = 0; i < ROWS; i++){//We need to rebuild the array to play again
            for(j = 0; j < COLUMNS; j++)
                array[i][j] = 0;
        }
        counter = 0;
        check = 0;
        }


    return 0;
}

int shootMerge(int **array, int rows, int columns, int number)
{
    int choose, maximum = array[0][0], check = 0, check_col;
    int i, j;
    do{
        check_col = 1;
        fflush(stdin);
        printf("You have %d, which column would you like to shoot [1-4]?", number);
        scanf("%d", &choose);
        if(choose < 1 || choose > 4)
            printf("Sorry, that is not a valid column, try again!\n");
        else if(array[ROWS - 1][choose - 1] != 0){//If column is full we ask to user choose another one
            printf("Sorry, this column is full! Choose another one!\n");
            check_col = 0;
            }
    }while((choose < 1 || choose > 4) || check_col == 0);

    //SHOOT PART
    for(i = 0; i < ROWS; i++){
        if(array[i][choose - 1] == 0 && check == 0){//this part assign the value in a proper place in array
            array[i][choose - 1] = number;
            check = 1;//after assigning check should be assigned as 1 in order to not assign other places with the same value.
        }
    }

    //MERGE PART
    for(i = ROWS - 1; i > 0; i--){//the program should merge from bottom to top
        if(array[i][choose - 1] == array[i - 1][choose - 1]){
            array[i - 1][choose - 1] *= 2;//if same numbers are one after the other, the top one should be multiplied by 2.
            array[i][choose - 1] = 0;//the bottom one should be assigned as zero
        }

    }


    for(i = 0; i < ROWS; i++){//This part take the maximum value in the array
        for(j = 1; j < COLUMNS; j++){
            if(array[i][j] > maximum)
                maximum = array[i][j];
        }
    }

    return maximum;
}

void displayBoard(int **array)
{
    int i, j;
    printf("\tC1\tC2\tC3\tC4\n");
    for(i = 0; i < ROWS; i++){
        for(j = 0; j < COLUMNS; j++){
            printf("\t");
            if(array[i][j] != 0)
                printf("%d", array[i][j]);
        }
        printf("\n");
    }
}

int randomPowerTwo(int max)
{
    int exponent = 0;
    while(pow(2, exponent) < max){
        exponent++;
    }
    return pow(2, rand()%(exponent) + 1);
}


int fullorNot(int **array)
{
    int i, j;
    for(i = 0; i < ROWS; i++){
        for(j = 0; j < COLUMNS; j++){
            if(array[i][j] == 0)
                return 0;
        }
    }
    return 1;
}
