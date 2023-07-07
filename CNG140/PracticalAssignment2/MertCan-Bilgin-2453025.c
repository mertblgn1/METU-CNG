// Name: Mert Can Bilgin
// Student ID: 2453025

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int play_computer();
int play_user();
int computer_strategy(int, int, int, int, int, int);//This function decides their strategy for the first kept dice
int computer_strategy2(int, int, int, int, int, int, int, int, int);//This function decides their strategy for the second kept dice
int computer_strategy3(int, int, int, int, int, int, int, int, int, int);// This function decides  their strategy for the third kept dice
int computer_strategy4(int, int, int, int, int, int, int, int, int, int, int);// this function decides their strategy dor the fourth kept dice
int largest_finder(int, int, int, int);//This function finds the largest number among four numbers
int largest_finder5(int, int, int, int, int);//This funtion finds the largest number among five numbers
int largest_finder3(int, int, int);//This function finds the largest number amon three numbers
int assign_dice(int, int, int, int, int, int, int, int, int);//This funtion decides the number of kept dice for kept3
int assign_dicefirst(int, int, int, int, int, int, int, int);//This function decides the number of kept dice for kept2
int assign_dicekept4(int, int, int, int, int, int, int, int, int, int);//This function decides the number of kept dice for kept4
int roll_a_dice();
int score_calculator(int, int, int, int, int, int, int, int);
void scoresheet(int, int);

int main()
{
    int check_round = 0, rounds, players_dice, computers_dice, i, players_point = 0, computers_point = 0;
    char answer;
    printf("Welcome to the MidnightDice game.\n");
    printf("Lets get started!\n\n");

    //I will check the input for the round is valid or not
    do{
        printf("How many rounds would you like to play? ");
        scanf("%d", &rounds);
        if(rounds < 1)
            printf("Please enter a valid number!\n");
        else
            check_round = 1;

    }while(check_round == 0);

    //This part checks who rolled larger before start the game until they are not equal.
    do{
        srand(time(NULL));
        computers_dice = roll_a_dice();
        printf("I have rolled the dice and got %d!\n", computers_dice);

        //This part will ask the user to roll a dice until s/he say yes
        do{
            fflush(stdin);
            printf("Shall I roll the dice for you (Y/N)? ");
            scanf("%c", &answer);
        }while(answer != 'Y');

        players_dice = roll_a_dice();
        printf("I have rolled the dice for you and you got %d!\n\n", players_dice);

    }while(players_dice == computers_dice);

    //Who rolled larger will start
    if(computers_dice > players_dice){
        for(i = 1; i <= rounds; i++){
            printf("Round %d -- My Turn:\n", i);
            printf("=============================================================\n");
            computers_point += play_computer();
            printf("\nRound %d -- Your Turn:\n", i);
            printf("=============================================================\n");
            players_point += play_user();
            printf("\n");
            scoresheet(computers_point, players_point);
        }
    }
    else{
        for(i = 1; i <= rounds; i++){
            printf("Round %d -- Your Turn:\n", i);
            printf("=============================================================\n");
            players_point += play_user();
            printf("\nRound %d -- My Turn:\n", i);
            printf("=============================================================\n");
            computers_point += play_computer();
            printf("\n");
            scoresheet(computers_point, players_point);
        }
    }
    if(computers_point > players_point)
        printf("I AM THE WINNER!\n");
    else if(players_point > computers_point)
        printf("YOU ARE THE WINNER!\n");
    else
        printf("DRAW!\n");

    return 0;
}

int play_computer()
{
    int d1, d2, d3, d4, d5, d6, score = 0, i ,j;
    int kept1 = 0, kept2 = 0, kept3 = 0, kept4 = 0, kept5 = 0, kept6 = 0;
    int check_one = 0, check_four = 0;
    srand(time(NULL));
    for(i = 0; i < 3; i++){
        d1 = roll_a_dice(); d2 = roll_a_dice(); d3 = roll_a_dice(); d4 = roll_a_dice(); d5 = roll_a_dice(); d6 = roll_a_dice();
        printf("I got -> ");
        for(j = 1; j <= 6; j++){//printing
            if(j != kept1 && j != kept2 && j != kept3 && j != kept4 && j != kept5 && j != kept6){
                if(j == 1){
                    printf("[Dice %d]: %d ", j, d1);
                }
                else if(j == 2){
                    printf("[Dice %d]: %d ", j, d2);
                }
                else if(j == 3){
                    printf("[Dice %d]: %d ", j, d3);
                }
                else if(j == 4){
                    printf("[Dice %d]: %d ", j, d4);
                }
                else if(j == 5){
                    printf("[Dice %d]: %d ", j, d5);
                }
                else if(j == 6){
                    printf("[Dice %d]: %d ", j, d6);
                }
            }
        }
        if(i == 0){//while i = 0, there are no kept dice, we decide our strategy according to this
            kept1 = computer_strategy(d1, d2, d3, d4, d5, d6);//kept1 and kept2 is decided one by one
            //I will check whether there is 'one' or 'four'
            if((d1 == 1 || d1 == 4) && kept1 == 1){
                if(d1 == 1)
                    check_one = 1;
                if(d1 == 4)
                    check_four = 1;
            }
            else if((d2 == 1 || d2 == 4) && kept1 == 2){
                if(d2 == 1)
                    check_one = 1;
                if(d2 == 4)
                    check_four = 1;
            }
            else if((d3 == 1 || d3 == 4) && kept1 == 3){
                if(d3 == 1)
                    check_one = 1;
                if(d3 == 4)
                    check_four = 1;
            }
            else if((d4 == 1 || d4 == 4) && kept1 == 4){
                if(d4 == 1)
                    check_one = 1;
                if(d4 == 4)
                    check_four = 1;
            }
            else if((d5 == 1 || d5 == 4) && kept1 == 5){
                if(d5 == 1)
                    check_one = 1;
                if(d5 == 4)
                    check_four = 1;
            }
            else if((d6 == 1 || d6 == 4) && kept1 == 6){
                if(d6 == 1)
                    check_one = 1;
                if(d6 == 4)
                    check_four = 1;
            }
            kept2 = computer_strategy2(check_one, check_four, kept1, d1, d2, d3, d4, d5, d6);
            if((d1 == 1 || d1 == 4) && kept2 == 1){//I didn't use else if statements this time because 'four' checked.
                if(d1 == 1)
                    check_one = 1;
                if(d1 == 4)
                    check_four = 1;
            }
            if((d2 == 1 || d2 == 4) && kept2 == 2){
                if(d2 == 1)
                    check_one = 1;
                if(d2 == 4)
                    check_four = 1;
            }
            if((d3 == 1 || d3 == 4) && kept2 == 3){
                if(d3 == 1)
                    check_one = 1;
                if(d3 == 4)
                    check_four = 1;
            }
            if((d4 == 1 || d4 == 4) && kept2 == 4){
                if(d4 == 1)
                    check_one = 1;
                if(d4 == 4)
                    check_four = 1;
            }
            if((d5 == 1 || d5 == 4) && kept2 == 5){
                if(d5 == 1)
                    check_one = 1;
                if(d5 == 4)
                    check_four = 1;
            }
            if((d6 == 1 || d6 == 4) && kept2 == 6){
                if(d6 == 1)
                    check_one = 1;
                if(d6 == 4)
                    check_four = 1;
            }
            //I calculate the score for the first two kept dices
            if(kept1 == 1 || kept2 == 1)
                score += d1;
            if(kept1 == 2 || kept2 == 2)
                score += d2;
            if(kept1 == 3 || kept2 == 3)
                score += d3;
            if(kept1 == 4 || kept2 == 4)
                score += d4;
            if(kept1 == 5 || kept2 == 5)
                score += d5;
            if(kept1 == 6 || kept2 == 6)
                score += d6;

            printf("\nKept dice %d and %d", kept1, kept2);
        }
        if(i == 1){//This part decide their strategy with four dices
            kept3 = computer_strategy3(check_one, check_four, kept1, kept2, d1, d2, d3, d4, d5, d6);
            if((d1 == 1 || d1 == 4) && kept3 == 1){
                if(d1 == 1)
                    check_one = 1;
                if(d1 == 4)
                    check_four = 1;
            }
            if((d2 == 1 || d2 == 4) && kept3 == 2){
                if(d2 == 1)
                    check_one = 1;
                if(d2 == 4)
                    check_four = 1;
            }
            if((d3 == 1 || d3 == 4) && kept3 == 3){
                if(d3 == 1)
                    check_one = 1;
                if(d3 == 4)
                    check_four = 1;
            }
            if((d4 == 1 || d4 == 4) && kept3 == 4){
                if(d4 == 1)
                    check_one = 1;
                if(d4 == 4)
                    check_four = 1;
            }
            if((d5 == 1 || d5 == 4) && kept3 == 5){
                if(d5 == 1)
                    check_one = 1;
                if(d5 == 4)
                    check_four = 1;
            }
            if((d6 == 1 || d6 == 4) && kept3 == 6){
                if(d6 == 1)
                    check_one = 1;
                if(d6 == 4)
                    check_four = 1;
            }
            kept4 = computer_strategy4(check_one, check_four, kept1, kept2, kept3, d1, d2, d3, d4, d5, d6);
            if((d1 == 1 || d1 == 4) && kept4 == 1){
                if(d1 == 1)
                    check_one = 1;
                if(d1 == 4)
                    check_four = 1;
            }
            if((d2 == 1 || d2 == 4) && kept4 == 2){
                if(d2 == 1)
                    check_one = 1;
                if(d2 == 4)
                    check_four = 1;
            }
            if((d3 == 1 || d3 == 4) && kept4 == 3){
                if(d3 == 1)
                    check_one = 1;
                if(d3 == 4)
                    check_four = 1;
            }
            if((d4 == 1 || d4 == 4) && kept4 == 4){
                if(d4 == 1)
                    check_one = 1;
                if(d4 == 4)
                    check_four = 1;
            }
            if((d5 == 1 || d5 == 4) && kept4 == 5){
                if(d5 == 1)
                    check_one = 1;
                if(d5 == 4)
                    check_four = 1;
            }
            if((d6 == 1 || d6 == 4) && kept4 == 6){
                if(d6 == 1)
                    check_one = 1;
                if(d6 == 4)
                    check_four = 1;
            }
            //I will calculate the score for these two kept dices too
            if(kept3 == 1 || kept4 == 1)
                score += d1;
            if(kept3 == 2 || kept4 == 2)
                score += d2;
            if(kept3 == 3 || kept4 == 3)
                score += d3;
            if(kept3 == 4 || kept4 == 4)
                score += d4;
            if(kept3 == 5 || kept4 == 5)
                score += d5;
            if(kept3 == 6 || kept4 == 6)
                score += d6;

            printf("\nKept dice %d and %d", kept3, kept4);
        }
        //there must be only 15 option (1,2),(1,3)..(5,6) etc. program checks these options.
        if(i == 2){//this part check 'one' and 'four' for the last two dices, and calculates the score
            if(kept1 == 6 || kept2 == 6 || kept3 == 6 || kept4 == 6){
                if(kept1 == 5 || kept2 == 5 || kept3 == 5 || kept4 == 5){
                    if(kept1 == 4 || kept2 == 4 || kept3 == 4 || kept4 == 4){
                        if(kept1 == 3 || kept2 == 3 || kept3 == 3 || kept4 == 3){
                            score += d1 + d2;
                            if(d1 == 4 || d2 == 4)
                                check_four = 1;
                            if(d1 == 1 || d2 == 1)
                                check_one = 1;
                        }
                        else if(kept1 == 2 || kept2 == 2 || kept3 == 2 || kept4 == 2){
                            score += d1 + d3;
                            if(d1 == 4 || d3 == 4)
                                check_four = 1;
                            if(d1 == 1 || d3 == 1)
                                check_one = 1;
                        }
                        else if(kept1 == 1 || kept2 == 1 || kept3 == 1 || kept4 == 1){
                            score += d2 + d3;
                            if(d2 == 4 || d3 == 4)
                                check_four = 1;
                            if(d2 == 1 || d3 == 1)
                                check_one = 1;
                        }
                    }
                    if(kept1 == 3 || kept2 == 3 || kept3 == 3 || kept4 == 3){
                        if(kept1 == 2 || kept2 == 2 || kept3 == 2 || kept4 == 2){
                            score += d1 + d4;
                            if(d1 == 4 || d4 == 4)
                                check_four = 1;
                            if(d1 == 1 || d4 == 1)
                                check_one = 1;
                        }
                    }
                    if(kept1 == 1 || kept2 == 1 || kept3 == 1 || kept4 == 1){
                        if(kept1 == 3 || kept2 == 3 || kept3 == 3 || kept4 == 3){
                            score += d2 + d4;
                            if(d2 == 4 || d4 == 4)
                                check_four = 1;
                            if(d2 == 1 || d2 == 1)
                                check_one = 1;
                        }
                        else if(kept1 == 2 || kept2 == 2 || kept3 == 2 || kept4 == 2){
                            score += d3 + d4;
                            if(d3 == 4 || d4 == 4)
                                check_four = 1;
                            if(d3 == 1 || d4 == 1)
                                check_one = 1;
                        }
                    }
                }
                if(kept1 == 4 || kept2 == 4 || kept3 == 4 || kept4 == 4){
                    if(kept1 == 3 || kept2 == 3 || kept3 == 3 || kept4 == 3){
                        if(kept1 == 2 || kept2 == 2 || kept3 == 2 && kept4 == 2){
                            score += d1 + d5;
                            if(d1 == 4 || d5 == 4)
                                check_four = 1;
                            if(d1 == 1 || d5 == 1)
                                check_one = 1;
                        }
                        else if(kept1 == 1 || kept2 == 1 || kept3 == 1 || kept4 == 1){
                            score += d2 + d5;
                            if(d2 == 4 || d5 == 4)
                                check_four = 1;
                            if(d2 == 1 || d5 == 1)
                                check_one = 1;
                        }
                    }
                    if(kept1 == 2 || kept2 == 2 || kept3 == 2 || kept4 == 2){
                        if(kept1 == 1 || kept2 == 1 || kept3 == 1 || kept4 == 1){
                            score += d3 + d5;
                            if(d3 == 4 || d5 == 4)
                                check_four = 1;
                            if(d3 == 1 || d5 == 1)
                                check_one = 1;
                        }
                    }
                }
                if(kept1 == 1 || kept2 == 1 || kept3 == 1 || kept4 == 1){
                    if(kept1 == 2 || kept2 == 2 || kept3 == 2 || kept4 == 2){
                        if(kept1 == 3 || kept2 == 3 || kept3 == 3 || kept4 == 3){
                            score += d4 + d5;
                            if(d4 == 4 || d5 == 4)
                                check_four = 1;
                            if(d4 == 1 || d5 == 1)
                                check_one = 1;
                        }
                    }
                }
            }
            if(kept1 == 5 || kept2 == 5 || kept3 == 5 || kept4 == 5){
                if(kept1 == 4 || kept2 == 4 || kept3 == 4 || kept4 == 4){
                    if(kept1 == 3 || kept2 == 3 || kept3 == 3 || kept4 == 3){
                        if(kept1 == 2 || kept2 == 2 || kept3 == 2 || kept4 == 2){
                            score += d1 + d6;
                            if(d1 == 4 || d6 == 4)
                                check_four = 1;
                            if(d1 == 1 || d6 == 1)
                                check_one = 1;
                        }
                        else if(kept1 == 1 || kept2 == 1 || kept3 == 1 || kept4 == 1){
                            score += d2 + d6;
                            if(d2 == 4 || d6 == 4)
                                check_four = 1;
                            if(d2 == 1 || d6 == 1)
                                check_one = 1;
                        }
                    }
                    if(kept1 == 1 || kept2 == 1 || kept3 == 1 || kept4 == 1){
                        if(kept1 == 2 || kept2 == 2 || kept3 == 2 || kept4 == 2){
                            score += d3 + d6;
                            if(d3 == 4 || d6 == 4)
                                check_four = 1;
                            if(d3 == 1 || d6 == 1)
                                check_one = 1;
                        }
                    }
                }
                if(kept1 == 1 || kept2 == 1 || kept3 == 1 || kept4 == 1){
                    if(kept1 == 2 || kept2 == 2 || kept3 == 2 || kept4 == 2){
                        if(kept1 == 3 || kept2 == 3 || kept3 == 3 || kept4 == 3){
                            score += d4 + d6;
                            if(d4 == 4 || d6 == 4)
                                check_four = 1;
                            if(d4 == 1 || d6 == 1)
                                check_one = 1;
                        }
                    }
                }
            }
            if(kept1 == 1 || kept2 == 1 || kept3 == 1 || kept4 == 1){
                if(kept1 == 2 || kept2 == 2 || kept3 == 2 || kept4 == 2){
                    if(kept1 == 3 || kept2 == 3 || kept3 == 3 || kept4 == 3){
                        if(kept1 == 4 || kept2 == 4 || kept3 == 4 || kept4 == 4){
                            score += d5 + d6;
                            if(d5 == 4 || d6 == 4)
                                check_four = 1;
                            if(d5 == 1 || d6 == 1)
                                check_one = 1;
                        }
                    }
                }
            }

        }
        printf("\n");
    }
    //Calculate the score according to the 'one' and 'four'
    if(check_four == 0 || check_one == 0){
        score = 0;
        printf("My score: 0\n");
    }
    else{
        score -= 5;
        printf("My score: %d\n", score);// I subtract by 5 because 1 and 4 shouldn't be added
    }

    return score;
}

int computer_strategy4(int check_one, int check_four, int kept1, int kept2, int kept3, int d1, int d2, int d3, int d4, int d5, int d6)
{
    int kept4 = 0, largest;
    //if there is no 'four' we check it first because 'one' already checked in strategy3
    if(check_four == 0){
        if(d1 == 4 && kept1 != 1 && kept2 != 1 && kept3 != 1){
            kept4 = 1;
            check_four = 1;
        }
        else if(d2 == 4 && kept1 != 2 && kept2 != 2 && kept3 != 2){
            kept4 = 2;
            check_four = 1;
        }
        else if(d3 == 4 && kept1 != 3 && kept2 != 3 && kept3 != 3){
            kept4 = 3;
            check_four = 1;
        }
        else if(d4 == 4 && kept1 != 4 && kept2 != 4 && kept3 != 4){
            kept4 = 4;
            check_four = 1;
        }
        else if(d5 == 4 && kept1 != 5 && kept2 != 5 && kept3 != 5){
            kept4 = 5;
            check_four = 1;
        }
        else if(d6 == 4 && kept1 != 6 && kept2 != 6 && kept3 != 6){
            kept4 = 6;
            check_four = 1;
        }
    }
    if(kept4 == 0){//if there is no four too we take largesr value again
        if(kept1 == 1 || kept2 == 1 || kept3 == 1){
            if(kept1 == 2 || kept2 == 2 || kept3 == 2){
                if(kept1 == 3 || kept2 == 3 || kept3 == 3)
                    largest = largest_finder3(d4, d5, d6);
                else if(kept1 == 4 || kept2 == 4 || kept3 == 4)
                    largest = largest_finder3(d3, d5, d6);
                else if(kept1 == 5 || kept2 == 5 || kept3 == 5)
                    largest = largest_finder3(d3, d4, d6);
                else if(kept1 == 6 || kept2 == 6 || kept3 == 6)
                    largest = largest_finder3(d3, d4, d5);
            }
            else if(kept1 == 3 || kept2 == 3 || kept3 == 3){
                if(kept1 == 4 || kept2 == 4 || kept3 == 4)
                    largest = largest_finder3(d2, d5, d6);
                else if(kept1 == 5 || kept2 == 5 || kept3 == 5)
                    largest = largest_finder3(d2, d4, d6);
                else if(kept1 == 6 || kept2 == 6 || kept3 == 6)
                    largest = largest_finder3(d2, d4, d5);
            }
            else if(kept1 == 4 || kept2 == 4 || kept3 == 4){
                if(kept1 == 5 || kept2 == 5 || kept3 == 5)
                    largest = largest_finder3(d2, d3, d6);
                else if(kept1 == 6 || kept2 == 6 || kept3 == 6)
                    largest = largest_finder3(d2, d3, d5);
            }
            else if(kept1 == 5 || kept2 == 5 || kept3 == 5){
                if(kept1 == 6 || kept2 == 6 || kept3 == 6)
                    largest = largest_finder3(d2, d3, d4);
            }
        }
        if(kept1 == 2 || kept2 == 2 || kept3 == 2){
            if(kept1 == 3 || kept2 == 3 || kept3 == 3){
                if(kept1 == 4 || kept2 == 4 || kept3 == 4)
                    largest = largest_finder3(d1, d5, d6);
                else if(kept1 == 5 || kept2 == 5 || kept3 == 5)
                    largest = largest_finder3(d1, d4, d6);
                else if(kept1 == 6 || kept2 == 6 || kept3 == 6)
                    largest = largest_finder3(d1, d4, d5);
            }
            else if(kept1 == 4 || kept2 == 4 || kept3 == 4){
                if(kept1 == 5 || kept2 == 5 || kept3 == 5)
                    largest = largest_finder3(d1, d3, d6);
                else if(kept1 == 6 || kept2 == 6 || kept3 == 6)
                    largest = largest_finder3(d1, d3, d5);
            }
            else if(kept1 == 5 || kept2 == 5 || kept3 == 5){
                if(kept1 == 6 || kept2 == 6 || kept3 == 6)
                    largest = largest_finder3(d1, d3, d4);
            }
        }
        if(kept1 == 3 || kept2 == 3 || kept3 == 3){
            if(kept1 == 4 || kept2 == 4 || kept3 == 4){
                if(kept1 == 5 || kept2 == 5 || kept3 == 5)
                    largest = largest_finder3(d1, d2, d6);
                else if(kept1 == 6 || kept2 == 6 || kept3 == 6)
                    largest = largest_finder3(d1, d2, d5);
            }
            else if(kept1 == 5 || kept2 == 5 || kept3 == 5){
                if(kept1 == 6 || kept2 == 6 || kept3 == 6)
                    largest = largest_finder3(d1, d2, d4);
            }
        }
        kept4 = assign_dicekept4(largest, kept1, kept2, kept3, d1, d2, d3, d4, d5, d6);
    }
    return kept4;
}

int computer_strategy3(int check_one, int check_four, int kept1, int kept2, int d1, int d2, int d3, int d4, int d5, int d6)
{
    //if there in no kept dice 'one' we take it first
    int kept3 = 0, largest;
    if(check_one == 0){
        if(d1 == 1 && kept1 != 1 && kept2 != 1){
            kept3 = 1;
            check_one = 1;
        }
        else if(d2 == 1 && kept1 != 2 && kept2 != 2){
            kept3 = 2;
            check_one = 1;
        }
        else if(d3 == 1 && kept1 != 3 && kept2 != 3){
            kept3 = 3;
            check_one = 1;
        }
        else if(d4 == 1 && kept1 != 4 && kept2 != 4){
            kept3 = 4;
            check_one = 1;
        }
        else if(d5 == 1 && kept1 != 5 && kept2 != 5){
            kept3 = 5;
            check_one = 1;
        }
        else if(d6 == 1 && kept1 != 6 && kept2 != 6){
            kept3 = 6;
            check_one = 1;
        }
    }
    else if(check_four == 0 && kept3 == 0){//This time we will take decision if there is no 'four'
        if(d1 == 4 && kept1 != 1 && kept2 != 1){
            kept3 = 1;
            check_four = 1;
        }
        else if(d2 == 4 && kept1 != 2 && kept2 != 2){
            kept3 = 2;
            check_four = 1;
        }
        else if(d3 == 4 && kept1 != 3 && kept2 != 3){
            kept3 = 3;
            check_four = 1;
        }
        else if(d4 == 4 && kept1 != 4 && kept2 != 4){
            kept3 = 4;
            check_four = 1;
        }
        else if(d5 == 4 && kept1 != 5 && kept2 != 5){
            kept3 = 5;
            check_four = 1;
        }
        else if(d6 == 4 && kept1 != 6 && kept2 != 6){
            kept3 = 6;
            check_four = 1;
        }
    }
    if(kept3 == 0){
            	if(kept1 == 1 || kept2 == 1){
                if(kept1 == 2 || kept2 == 2)
                    largest = largest_finder(d3, d4, d5, d6);
                else if(kept1 == 3 || kept2 == 3)
                    largest = largest_finder(d2, d4, d5, d6);
                else if(kept1 == 4 || kept2 == 4)
                    largest = largest_finder(d2, d3, d5, d6);
                else if(kept1 == 5 || kept2 == 5)
                    largest = largest_finder(d2, d3, d4, d6);
                else if(kept1 == 6 || kept2 == 6)
                    largest = largest_finder(d2, d3, d4, d5);
            }
            else if(kept1 == 2 || kept2 == 2){
                if(kept1 == 3 || kept2 == 3)
                    largest = largest_finder(d1, d4, d5, d6);
                else if(kept1 == 4 || kept2 == 4)
                    largest = largest_finder(d1, d3, d5, d6);
                else if(kept1 == 5 || kept2 == 5)
                    largest = largest_finder(d1, d3, d4, d6);
                else if(kept1 == 6 || kept2 == 6)
                    largest = largest_finder(d1, d3, d4, d5);
            }
            else if(kept1 == 3 || kept2 == 3){
                if(kept1 == 4 || kept2 == 4)
                    largest = largest_finder(d1, d2, d5, d6);
                else if(kept1 == 5 || kept2 == 5)
                    largest = largest_finder(d1, d2, d4, d6);
                else if(kept1 == 6 || kept2 == 6)
                    largest = largest_finder(d1, d2, d4, d5);
            }
            else if(kept1 == 4 || kept2 == 4){
                if(kept1 == 5 || kept2 == 5)
                    largest = largest_finder(d1, d2, d3, d6);
                else if(kept1 == 6 || kept2)
                    largest = largest_finder(d1, d2, d3, d5);
            }
            else if(kept1 == 5 || kept2 == 5){
                if(kept1 == 6 || kept2 == 6)
                    largest = largest_finder(d1, d2, d3, d4);
            }
        kept3 = assign_dice(largest, kept1, kept2, d1, d2, d3, d4, d5, d6);
    }
    return kept3;
}

int computer_strategy2(int check_one, int check_four, int kept1, int d1, int d2, int d3, int d4, int d5, int d6)
{
    int kept2 = 0, largest;
    if(check_one == 1 && check_four == 0){//This strategy will decide if there is no 'four' because 'one' checked first in kept1
        if(d1 == 4){
            kept2 = 1;
            check_four = 1;
        }
        else if(d2 == 4){
            kept2 = 2;
            check_four = 1;
        }
        else if(d3 == 4){
            kept2 = 3;
            check_four = 1;
        }
        else if(d4 == 4){
            kept2 = 4;
            check_four = 1;
        }
        else if(d5 == 4){
            kept2 = 5;
            check_four = 1;
        }
        else if(d6 == 4){
            kept2 = 6;
            check_four = 1;
        }
    }
    if(kept2 == 0){//if there is no 'four' again, we will take the largest value
        if(kept1 == 1)
            largest = largest_finder5(d2, d3, d4, d5, d6);
        else if(kept1 == 2)
            largest = largest_finder5(d1, d3, d4, d5, d6);
        else if(kept1 == 3)
            largest = largest_finder5(d1, d2, d4, d5, d6);
        else if(kept1 == 4)
            largest = largest_finder5(d1, d2, d3, d5, d6);
        else if(kept1 == 5)
            largest = largest_finder5(d1, d2, d3, d4, d6);
        else if(kept1 == 6)
            largest = largest_finder5(d1, d2, d3, d4, d5);

        kept2 = assign_dicefirst(largest, kept1, d1, d2, d3, d4, d5, d6);
    }
    return kept2;
}

int computer_strategy(int d1, int d2, int d3, int d4, int d5, int d6)
{
    int kept1 = 0;
    if(d1 == 1)//check 'one'
        kept1 = 1;
    else if(d2 == 1)
        kept1 = 2;
    else if(d3 == 1)
        kept1 = 3;
    else if(d4 == 1)
        kept1 = 4;
    else if(d5 == 1)
        kept1 = 5;
    else if(d6 == 1)
        kept1 = 6;

    if(kept1 == 0){//check 'four'
        if(d1 == 4)
            kept1 = 1;
        else if(d2 == 4)
            kept1 = 2;
        else if(d3 == 4)
            kept1 = 3;
        else if(d4 == 4)
            kept1 = 4;
        else if(d5 == 4)
            kept1 = 5;
        else if(d6 == 4)
            kept1 = 6;
    }
    if(kept1 == 0){//if there is no one or four, I give the largest value
        if(d1 >= d2 && d1 >= d3 && d1 >= d4 && d1 >= d5 && d1 >= d6)
            kept1 = 1;
        else if(d2 >= d1 && d2 >= d3 && d2 >= d4 && d2 >= d5 && d2 >= d6)
            kept1 = 2;
        else if(d3 >= d1 && d3 >= d2 && d3 >= d4 && d3 >= d5 && d3 >= d6)
            kept1 = 3;
        else if(d4 >= d1 && d4 >= d2 && d4 >= d3 && d4 >= d5 && d4 >= d6)
            kept1 = 4;
        else if(d5 >= d1 && d5 >= d2 && d5 >= d3 && d5 >= d4 && d5 >= d6)
            kept1 = 5;
        else if(d6 >= d1 && d6 >= d2 && d6 >= d3 && d6 >= d4 && d6 >= d5)
            kept1 = 6;
    }
    return kept1;
}

int largest_finder(int a, int b, int c, int d)
{
	if(a >= b && a >= c && a >= d)
		return a;
	else if(b >= a && b >= c && b >= d)
		return b;
	else if(c >= a && c >= b && c >= d)
		return c;
	else if(d >= a && d >= b && d >= c)
		return d;
}

int largest_finder5(int a, int b, int c, int d, int e)
{
    if(a >= b && a >= c && a >= d && a >= e)
        return a;
    else if(b >= a && b >= c && b >= d && b >= e)
        return b;
    else if(c >= a && c >= b && c >= d && c >= e)
        return c;
    else if(d >= a && d >= b && d >= c && d >= e)
        return d;
    else if(e >= a && e >= b && e >= c && e >= d)
        return e;
}

int largest_finder3(int a, int b, int c)
{
    if(a >= b && a >= c)
        return a;
    else if(b >= a && b >= c)
        return b;
    else if(c >= a && c >= b)
        return c;
}

int assign_dicefirst(int largest, int kept1, int d1, int d2,int d3, int d4, int d5, int d6)
{
    if(largest == d1 && kept1 != 1)
        return 1;
    else if(largest == d2 && kept1 != 2)
        return 2;
    else if(largest == d3 && kept1 != 3)
        return 3;
    else if(largest == d4 && kept1 != 4)
        return 4;
    else if(largest == d5 && kept1 != 5)
        return 5;
    else if(largest == d6 && kept1 != 6)
        return 6;
}

int assign_dicekept4(int largest, int kept1, int kept2, int kept3, int d1, int d2, int d3, int d4, int d5, int d6)
{
    if(largest == d1 && kept1 != 1 && kept2 != 1 && kept3 != 1)
        return 1;
    else if(largest == d2 && kept1 != 2 && kept2 != 2 && kept3 != 2)
        return 2;
    else if(largest == d3 && kept1 != 3 && kept2 != 3 && kept3 != 3)
        return 3;
    else if(largest == d4 && kept1 != 4 && kept2 != 4 && kept3 != 4)
        return 4;
    else if(largest == d5 && kept1 != 5 && kept2 != 5 && kept3 != 5)
        return 5;
    else if(largest == d6 && kept1 != 6 && kept2 != 6 && kept3 != 6)
        return 6;
}

int assign_dice(int largest, int kept1, int kept2, int d1, int d2, int d3, int d4, int d5, int d6)
{
	if(largest == d1 && kept1 != 1 && kept2 != 1)
		return 1;
	else if(largest == d2 && kept1 != 2 && kept2 != 2)
		return 2;
	else if(largest == d3 && kept1 != 3 && kept2 != 3)
		return 3;
	else if(largest == d4 && kept1 != 4 && kept2 != 4)
		return 4;
	else if(largest == d5 && kept1 != 5 && kept2 != 5)
		return 5;
	else if(largest == d6 && kept1 != 6 && kept2 != 6)
		return 6;
}

int play_user()
{
    char answer;
    int d1, d2, d3, d4, d5, d6, kept1 = 0, kept2 = 0, kept3 = 0, kept4 = 0, kept5 = 0, kept6 = 0, j, i, score = 0;
    int check_one = 0, check_four = 0;
    printf("Are you ready to play!\n");
    for(i = 0; i < 3; i++){
        do{//This part will ask the user until s/he say yes.
            fflush(stdin);
            printf("Shall I roll them for you (Y/N)? ");
            scanf("%c", &answer);
        }while(answer != 'Y');

        srand(time(NULL));
        d1 = roll_a_dice(); d2 = roll_a_dice(); d3 = roll_a_dice(); d4 = roll_a_dice(); d5 = roll_a_dice(); d6 = roll_a_dice();
        printf("You got -> ");
        for(j = 1; j <= 6; j++){
            if(j != kept1 && j != kept2 && j != kept3 && j != kept4){
                if(j == 1){
                    printf("[Dice %d]: %d ", j, d1);
                    if(kept5 == 0 && i == 2)
                        kept5 = 1;
                    else if(kept5 != 0 && i == 2)
                        kept6 = 1;
                }
                else if(j == 2){
                    printf("[Dice %d]: %d ", j, d2);
                    if(kept5 == 0 && i == 2)
                        kept5 = 2;
                    else if(kept5 != 0 && i == 2)
                        kept6 = 2;
                }
                else if(j == 3){
                    printf("[Dice %d]: %d ", j, d3);
                    if(kept5 == 0 && i == 2)
                        kept5 = 3;
                    else if(kept5 != 0 && i == 2)
                        kept6 = 3;
                }
                else if(j == 4){
                    printf("[Dice %d]: %d ", j, d4);
                    if(kept5 == 0 && i == 2)
                        kept5 = 4;
                    else if(kept5 != 0 && i == 2)
                        kept6 = 4;
                }
                else if(j == 5){
                    printf("[Dice %d]: %d ", j, d5);
                    if(kept5 == 0 && i == 2)
                        kept5 = 5;
                    else if(kept5 != 0 && i == 2)
                        kept6 = 5;
                }
                else if(j == 6){
                    printf("[Dice %d]: %d ", j, d6);
                    if(kept5 == 0 && i == 2)
                        kept5 = 6;
                    else if(kept5 != 0 && i == 2)
                        kept6 = 6;
                }
            }
            if(j == kept1 || j == kept2 || j == kept3 || j == kept4 || j == kept5 || j == kept6){
                if(j == 1){
                    if(d1 == 1)
                        check_one = 1;
                    if(d1 == 4)
                        check_four = 1;
                }
                else if(j == 2){
                    if(d2 == 1)
                        check_one = 1;
                    if(d2 == 4)
                        check_four = 1;
                }
                else if(j == 3){
                    if(d3 == 1)
                        check_one = 1;
                    if(d3 == 4)
                        check_four = 1;
                }
                else if(j == 4){
                    if(d4 == 1)
                        check_one = 1;
                    if(d4 == 4)
                        check_four = 1;
                }
                else if(j == 5){
                    if(d5 == 1)
                        check_one = 1;
                    if(d5 == 4)
                        check_four = 1;
                }
                else if(j == 6){
                    if(d6 == 1)
                        check_one = 1;
                    if(d6 == 4)
                        check_four = 1;
                }
            }
        }
        if(i == 0){
            printf("\nWhich ones you want to keep? ");
            scanf("%d %d", &kept1, &kept2);
            score += score_calculator(kept1, kept2, d1, d2, d3, d4, d5, d6);
        }
        else if(i == 1){
            printf("\nWhich ones you want to keep? ");
            scanf("%d %d", &kept3, &kept4);
            score += score_calculator(kept3, kept4, d1, d2, d3, d4, d5, d6);
        }
    }
    score += score_calculator(kept5, kept6, d1, d2, d3, d4, d5, d6);
    if(check_four == 0 || check_one == 0)
        score = 0;
    else
        score -= 5;//I subtract by 5 because 1 and 4 shouldn't be added
    printf("\nYour score: %d\n", score);


    return score;
}

int score_calculator(int kept1, int kept2, int d1, int d2, int d3, int d4, int d5, int d6)
{
    int i, score = 0;
    for(i = 1; i <= 6; i++){
        if(i == kept1 || i == kept2){
            if(i == 1)
                score += d1;
            else if(i == 2)
                score += d2;
            else if(i == 3)
                score += d3;
            else if(i == 4)
                score += d4;
            else if(i == 5)
                score += d5;
            else if(i == 6)
                score += d6;
        }
    }
    return score;
}

void scoresheet(int a, int b)
{
    printf("Our scoresheet:\n");
    printf("===========================\n");
    printf("My score\tYour score\n");
    printf("%d\t\t%d\n\n", a, b);
}

int roll_a_dice()
{
    return ((rand()%6) + 1);
}
