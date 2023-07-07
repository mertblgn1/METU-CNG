//Name: Mert Can Bilgin
//Student ID: 2453025

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct corona{
    char country[20];
    int deaths;
    int recovered;
    int active_case;
    int population;
    int total_case;
};

int Load_CoronavirusTable(char*, struct corona *);
void Display_CoronavirusTable(struct corona *, int);
int Search(struct corona*, int, char *);
struct corona *Sort(struct corona *, int, char);
int numberOfLines(FILE *, char *);


int main(int argc, char *argv[])
{
    int correct_filename = 1;
    char filename[20];
    strcpy(filename, argv[1]);
    //The file is opened here
    FILE *inFile;
    inFile = fopen(argv[1], "r");
    //If it cannot be opened, give error message, and ask again
    if(inFile == NULL){
        correct_filename = 0;
    }
    else
        printf("Coronavirus records file (corona.txt) has been successfully loaded!\n");

    while(correct_filename == 0){
        fflush(stdin);
        printf("This file does not exist, please enter again: ");
        scanf("%s", filename);
        inFile = fopen(filename, "r");
        if(inFile != NULL){
            printf("Coronavirus records file (corona.txt) has been successfully loaded!\n");
            correct_filename = 1;
        }
    }
    //Take the size of the lines by using this function
    int Size = numberOfLines(inFile, filename);

    //Dynamically create the structure
    struct corona *CoronavirusTable;
    CoronavirusTable = (struct corona*)malloc(sizeof(struct corona) * Size);
    if(CoronavirusTable == NULL){
        printf("Allocation failed!\n");
        exit(1);
    }

    //Populate the structure, and return the actual size
    int size = Load_CoronavirusTable(filename, CoronavirusTable);

    printf("Following records have been loaded:\n\n");
    Display_CoronavirusTable(CoronavirusTable, size);
    int exit = 0, option, correct_name = 0, sorttypeisok = 0;
    char name[20];
    char sorttype;

    do{
        printf("\nPress 1 for search, 2 for sort and 3 for exit: ");
        scanf("%d", &option);

        switch(option){
            case 1:
                do{
                    fflush(stdin);//Clean the buffer for safety because the user can choose this option more than one time
                    printf("Enter the name of the country: ");
                    scanf("%s", name);
                    correct_name = Search(CoronavirusTable, size, name);
                    //Ask the user until s/he enters appropriate name of country
                    if(correct_name == -1)
                        printf("That country is unknown! Please try again!\n");
                    else
                        printf("%s with %d population has %d total cases (%d deaths, %d recovered and %d active cases)\n", CoronavirusTable[correct_name].country, CoronavirusTable[correct_name].population, CoronavirusTable[correct_name].total_case, CoronavirusTable[correct_name].deaths, CoronavirusTable[correct_name].recovered, CoronavirusTable[correct_name].active_case);
                }while(correct_name == -1);
                break;
            case 2:
                do{
                    fflush(stdin);//Clean the buffer for safety because the user can choose this option more than one time
                    printf("Sort by (T: total cases, A: active cases): ");
                    scanf("%c", &sorttype);
                    //If the user enters inappropriate option ask again
                    if(sorttype == 'A' || sorttype == 'T')
                        sorttypeisok = 1;
                    else
                        printf("Please enter one of the options!\n");
                }while(sorttypeisok == 0);
                sorttypeisok = 0;
                CoronavirusTable = Sort(CoronavirusTable, size, sorttype);
                Display_CoronavirusTable(CoronavirusTable, size);
                break;
            case 3:
                printf("\nBye!\n");
                exit = 1;
                break;
            default:
                printf("Please pick up one of the options!\n");
                break;
        }

    }while(exit != 1);

    //close the file
    fclose(inFile);
    return 0;
}

struct corona*Sort(struct corona *CoronavirusTable, int size, char sortType)
{
    int temp_death, temp_recovered, temp_ac, temp_population, temp_tc, i, j;
    char temp_name[20];
    if(sortType == 'A'){
        for(i = 0; i < size; i++){
            for(j = 0; j < size; j++){
                //check the active cases one by one and sort them by using temporary variables
                if(CoronavirusTable[j].active_case < CoronavirusTable[i].active_case){
                    strcpy(temp_name, CoronavirusTable[i].country);
                    temp_death = CoronavirusTable[i].deaths;
                    temp_recovered = CoronavirusTable[i].recovered;
                    temp_ac = CoronavirusTable[i].active_case;
                    temp_population = CoronavirusTable[i].population;
                    temp_tc = CoronavirusTable[i].total_case;

                    strcpy(CoronavirusTable[i].country, CoronavirusTable[j].country);
                    CoronavirusTable[i].deaths = CoronavirusTable[j].deaths;
                    CoronavirusTable[i].recovered = CoronavirusTable[j].recovered;
                    CoronavirusTable[i].active_case = CoronavirusTable[j].active_case;
                    CoronavirusTable[i].population = CoronavirusTable[j].population;
                    CoronavirusTable[i].total_case = CoronavirusTable[j].total_case;

                    strcpy(CoronavirusTable[j].country, temp_name);
                    CoronavirusTable[j].deaths = temp_death;
                    CoronavirusTable[j].recovered = temp_recovered;
                    CoronavirusTable[j].active_case = temp_ac;
                    CoronavirusTable[j].population = temp_population;
                    CoronavirusTable[j].total_case = temp_tc;

                }
            }
        }
    }
    else if(sortType == 'T'){
        for(i = 0; i < size; i++){
            for(j = 0; j < size; j++){
                //check the total cases this time, and sort them by using temporary variables
                if(CoronavirusTable[j].total_case < CoronavirusTable[i].total_case){
                    //assign ith variable to temporary variables
                    strcpy(temp_name, CoronavirusTable[i].country);
                    temp_death = CoronavirusTable[i].deaths;
                    temp_recovered = CoronavirusTable[i].recovered;
                    temp_ac = CoronavirusTable[i].active_case;
                    temp_population = CoronavirusTable[i].population;
                    temp_tc = CoronavirusTable[i].total_case;

                    //assign jth variables to ith variables
                    strcpy(CoronavirusTable[i].country, CoronavirusTable[j].country);
                    CoronavirusTable[i].deaths = CoronavirusTable[j].deaths;
                    CoronavirusTable[i].recovered = CoronavirusTable[j].recovered;
                    CoronavirusTable[i].active_case = CoronavirusTable[j].active_case;
                    CoronavirusTable[i].population = CoronavirusTable[j].population;
                    CoronavirusTable[i].total_case = CoronavirusTable[j].total_case;

                    //assign temporary variables to jth variables
                    strcpy(CoronavirusTable[j].country, temp_name);
                    CoronavirusTable[j].deaths = temp_death;
                    CoronavirusTable[j].recovered = temp_recovered;
                    CoronavirusTable[j].active_case = temp_ac;
                    CoronavirusTable[j].population = temp_population;
                    CoronavirusTable[j].total_case = temp_tc;
                }
            }
        }
    }
    return CoronavirusTable;
}

int Search(struct corona *CoronavirusTable, int size, char *name)
{
    int i, found = -1;
    for(i = 0; i < size; i++){
        //if the given strings are the same, the funtion will return its position. If it is not, it will return -1
        //also -1 means there is no country with this name
        if(strcmp(name, CoronavirusTable[i].country) == 0)
            found = i;
    }
    return found;
}

void Display_CoronavirusTable(struct corona *CoronavirusTable, int size)
{
    int i, j;
    //the space needed for country part is 7(becasue country is 7 letters) + 8
    //the space needed for deaths is 6 + 8
    //the space needed for recovered is 9 + 8
    //the space needed for active cases is 12 + 8
    //the space needed for population is 10 + 8
    printf("\nCountry\t\tDeaths\t\tRecovered\tActive Cases\t\tPopulation\t\tTotal Cases\n");
    for(i = 0; i < size; i++){
        printf("%-17s", CoronavirusTable[i].country);
        printf("%-15d", CoronavirusTable[i].deaths);
        printf("%-14d\t", CoronavirusTable[i].recovered);
        printf("%-17d\t", CoronavirusTable[i].active_case);
        printf("%-20d\t", CoronavirusTable[i].population);
        printf("%-18d\n", CoronavirusTable[i].total_case);
    }
}

int Load_CoronavirusTable(char *filename, struct corona *CoronavirusTable)
{
    FILE *inFile;

    //open the file
    inFile = fopen(filename, "r");
    //give error message and quit if it cannot be opened
    if(inFile == NULL){
        printf("Couldn't open the file!\n");
        exit(1);
    }


    char line[200];
    int i = 0;
    while(fgets(line, 200, inFile)){
        char *token;
        //get the first token
        token = strtok(line, " ");
        //set a flag
        int flag = 1;

        while(token != NULL){
            if(flag == 1){
                //first token is country name
                strcpy(CoronavirusTable[i].country, token);
            }
            else if(flag == 2){
                CoronavirusTable[i].deaths = atoi(token);
            }
            else if(flag == 3){
                CoronavirusTable[i].recovered = atoi(token);
            }
            else if(flag == 4){
                CoronavirusTable[i].active_case = atoi(token);
            }
            else{
                //remove the new line at the end of the string
                if(token[strlen(token)-1]=='\n')
        			token[strlen(token)-1] = '\0';
                CoronavirusTable[i].population = atoi(token);
            }
            token = strtok(NULL, " ");
            flag++;
        }
        if(flag > 5){
            CoronavirusTable[i].total_case = CoronavirusTable[i].deaths + CoronavirusTable[i].recovered + CoronavirusTable[i].active_case;
            i++;
        }

    }
    //close the file
    fclose(inFile);
    return i;
}

int numberOfLines(FILE *inFile, char *filename)
{
    // declare temporary variables in order to count the lines
    int counter = 0, a, b, c, d1;
    char trying[20];
    //open the file
    inFile = fopen(filename, "r");
    //give error message if it cannot be opened
    if(inFile == NULL){
        printf("Couldn't open the file!\n");
        exit(1);
    }
    while((fscanf(inFile, "%s %d %d %d %d", trying, &a, &b, &c, &d1)) != EOF)
        counter++;

    //close the file
    fclose(inFile);
    return counter;
}
