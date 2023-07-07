// Name: Mert Can Bilgin
// Student ID: 2453025

#include <stdio.h>
#define LF 10

int main()
{
    int counter = 0, valid_digit = 0, exit_digit = 0, selection, base = 0, btw_control = 0, exit_btw = 0, input, lessthan8 = 0;
    char D0, D1, D2, D3, D4, D5, D6, D7, temp;
    int Y0 = 0, Y1 = 0, Y2 = 0, counter2 = 0, remainder;

    printf("Welcome to Octal to Binary Encoder!\n");
    printf("\n\t(1) Compute and Display the outputs\n");
    printf("\t(2) Quit\n");
    printf("You choose: ");
    scanf("%d", &selection);
    printf("You have chosen option %d\n", selection);

    if(selection == 1) //this part checks the quit or not
    {
        while(base != 2 && base != 10) //program asks the user which base he wants until the user enter correct base
        {
        printf("\nWhich base will you use to enter input(base 2 or base 10)? ");
        scanf("%d", &base);
        if(base != 2 && base != 10)
            printf("Invalid number in base 2/10\n");
        }

        if(base == 2)
        {
            while(valid_digit == 0)//according to my algorithm, program will not quit from the loop until the user enter 8 bits and binary.
            {
                printf("Please enter your input: ");
                scanf("\n%c", &temp);

                while(temp != LF && exit_digit == 0)//the program reads the input and assign values to D's.
                {
                    if(counter == 0)
                        D7 = temp;
                    else if(counter == 1)
                        D6 = temp;
                    else if(counter == 2)
                        D5 = temp;
                    else if(counter == 3)
                        D4 = temp;
                    else if(counter == 4)
                        D3 = temp;
                    else if(counter == 5)
                        D2 = temp;
                    else if(counter == 6)
                        D1 = temp;
                    else if(counter == 7)
                        D0 = temp;
                    else if(counter > 7)
                        exit_digit = 1;

                    counter++;
                    scanf("%c", &temp);
                }
    //These counter conditions checks if the user enter 8 bits or not.
                if(counter > 8)
                    {
                    printf("You entered more than 8 bits! Please try again!\n");
                    exit_digit = 0;
                    counter = 0;
                    D0 = 127, D1 = 127, D2 = 127, D3 = 127, D4 = 127, D5 = 127, D6 = 127, D7 = 127;//I assign D's 127 because D's needs to be cleared, 127 means DEL.
                    }
                else if(counter < 8 && counter > 0)
                    {
                    exit_digit = 0;
                    if(D0 > 49 || D1 > 49 || D2 > 49 || D3 > 49 || D4 > 49 || D5 > 49 || D6 > 49 || D7 > 49)//the program checks the digits bigger than 1. 49 means 1 according to ASCII.
                    {
                        if(D0 < 127 && D1 < 127 && D2 < 127 && D3 < 127 && D4 < 127 && D5 < 127 && D6 < 127 && D7 < 127)
                        {
                        printf("%c%c%c%c%c%c%c%c is not a valid number in base 2! Please try again!\n", D7, D6, D5, D4, D3, D2, D1, D0);
                        counter = 0;
                        lessthan8 = 1;//I created this variable for giving the correct error mesage firstly.
                        }


                    counter = 0;
                    }
                    if(lessthan8 == 0)
                        {
                        printf("You entered less than 8 bits! Please try again!\n");
                        counter = 0;
                        }

                    }

                else if(counter == 8)
                    {
                    valid_digit = 1;//if the input is 8 bits, it will left the loop.
                    exit_digit = 1;
                    }

                if(valid_digit == 1 && exit_digit == 1)//After checking digits, the program will check if it is binary or not.
                {
                    if(D0 > 49 || D1 > 49 || D2 > 49 || D3 > 49 || D4 > 49 || D5 > 49 || D6 > 49 || D7 > 49)
                    {
                        if(D0 < 127 && D1 < 127 && D2 < 127 && D3 < 127 && D4 < 127 && D5 < 127 && D6 < 127 && D7 < 127)
                            printf("%c%c%c%c%c%c%c%c is not a valid number in base 2! Please try again!\n", D7, D6, D5, D4, D3 ,D2, D1, D0);

                        valid_digit = 0;
                    }
                }
                lessthan8 = 0;

            }
            //accoring to the D's table, I assigned to Y values.
            if(D1 == 49 || D3 == 49 || D5 == 49 || D7 == 49)
                Y0 = 1;
            if(D2 == 49 || D3 == 49 || D6 == 49 || D7 == 49)
                Y1 = 1;
            if(D4 == 49 || D5 == 49 || D6 == 49 || D7 == 49)
                Y2 = 1;

            printf("Y2 is %d Y1 is %d Y0 is %d\n", Y2, Y1, Y0);
        }

        else if(base == 10)
        {
            while(btw_control == 0)//this part check the input whether it is between 0 and 255.
            {
                printf("Please enter your input: ");
                scanf("%d", &input);

                if(input >= 0 && input <= 255)
                    btw_control = 1;
                else
                    printf("Decimal %d cannot be presented with 8 bits. Please try again!\n", input);
            }
            while(counter2 < 8)//This part converts decimal number to binary, and assign values to D's as I did in base 2.
            {
                remainder = input % 2;
                if(counter2 == 0)
                {
                    if(remainder == 0)
                        D0 = 48;
                    else if(remainder == 1)
                        D0 = 49;
                }
                else if(counter2 == 1)
                {
                    if(remainder == 0)
                        D1 = 48;
                    else if(remainder == 1)
                        D1 = 49;
                }
                else if(counter2 == 2)
                {
                    if(remainder == 0)
                        D2 = 48;
                    else if(remainder == 1)
                        D2 = 49;
                }
                else if(counter2 == 3)
                {
                    if(remainder == 0)
                        D3 = 48;
                    else if(remainder == 1)
                        D3 = 49;
                }
                else if(counter2 == 4)
                {
                    if(remainder == 0)
                        D4 = 48;
                    else if(remainder == 1)
                        D4 = 49;
                }
                else if(counter == 5)
                {
                    if(remainder == 0)
                        D5 = 48;
                    else if(remainder == 1)
                        D5 = 49;
                }
                else if(counter == 6)
                {
                    if(remainder == 0)
                        D6 = 48;
                    else if(remainder == 1)
                        D6 = 49;
                }
                else if(counter == 7)
                {
                    if(remainder == 0)
                        D7 = 48;
                    else if(remainder == 1)
                        D7 = 49;
                }
                input /= 2;
                counter2++;

            }
            //This part assign Y values accordingt to the D's table.
            if(D4 == 49 || D5 == 49 || D6 == 49 || D7 == 49)
                Y2 = 1;
            if(D2 == 49 || D3 == 49 || D6 == 49 || D7 == 49)
                Y1 = 1;
            if(D1 == 49 || D3 == 49 || D5 == 49 || D7 == 49)
                Y0 = 1;

            printf("Y2 is %d Y1 is %d Y0 is %d\n", Y2, Y1, Y0);

        }
    }
    else if(selection == 2)
        printf("BYEE!!\n");



    return 0;


}
