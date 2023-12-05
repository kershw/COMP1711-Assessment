#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Define the struct for the fitness data
FITNESS_DATA STEP_INTERVAL [1000]; //defines the array of structs
char fitnessDataFile[30];
int fileLength = 0;

// Function to tokenize a record
/*void tokeniseRecord(char *record, char delimiter, char *date, char *time, int *steps) {
    char *ptr = strtok(record, &delimiter);
    if (ptr != NULL) {
        strcpy(date, ptr);
        ptr = strtok(NULL, &delimiter);
        if (ptr != NULL) {
            strcpy(time, ptr);
            ptr = strtok(NULL, &delimiter);
            if (ptr != NULL) {
                *steps = atoi(ptr);
            }
        }
    }
}*/
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);

}

int bubbleSort() {
    FITNESS_DATA temp;

    for (int i = 0; i < fileLength; i++) {
        for (int j = 0; j < fileLength - i - 1; j++) {
            if (STEP_INTERVAL[j].steps > STEP_INTERVAL[j + 1].steps) {
                temp.steps = STEP_INTERVAL[j + 1].steps;
                strcpy(temp.date, STEP_INTERVAL[j + 1].date);
                strcpy(temp.time, STEP_INTERVAL[j + 1].time);

                STEP_INTERVAL[j + 1].steps = STEP_INTERVAL[j].steps;
                strcpy(STEP_INTERVAL[j + 1].date, STEP_INTERVAL[j].date);
                strcpy(STEP_INTERVAL[j + 1].time, STEP_INTERVAL[j].time);

                STEP_INTERVAL[j].steps = temp.steps;
                strcpy(STEP_INTERVAL[j].date, temp.date);
                strcpy(STEP_INTERVAL[j].time, temp.time);
            }
        }
    }

    for (int x = 0; x < fileLength; x++) {
        printf("%d", STEP_INTERVAL[x].steps);
    }
    return 9;
}

int main() {

    printf("Enter filename: ");
    scanf(" %s", fitnessDataFile);

    FILE *file = fopen(fitnessDataFile, "r"); //opens the fitnessdata file



    if (file == NULL) { //checks for no file error
        printf("Error: invalid file\n");
        return -1;
    }
    
    char temp[25];
    while (fgets(temp, 25, file))  { //finds the length of the file - for use with unseen files which may have varying lengths
        fileLength++;
    }



    //defining various variables to be used within the while loop
    rewind(file);
    char data[25];  
    int count = 0;
    //date length 11, time length 6, steps length 10; remember this or string formatting goes weird
    char outputDate[11]; 
    char outputTime[6];
    char outputSteps[10];

    while (fgets(data, 25, file)) { //buffer = a few characters more than max length for safety
        tokeniseRecord(data, ",", outputDate, outputTime, outputSteps); //runs tokenise record function to get data from each line
        strcpy(STEP_INTERVAL[count].date, outputDate); //copies date to struct
        strcpy(STEP_INTERVAL[count].time, outputTime); //copies time to struct
        STEP_INTERVAL[count].steps = atoi(outputSteps); //copies steps to struct - use atoi to save as int
        count++;

    fclose(file);

    bubbleSort();

    return 0;
    }

}