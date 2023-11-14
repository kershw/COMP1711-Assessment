#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Define any additional variables here
FITNESS_DATA STEP_INTERVAL [1000]; //defines the array of structs
char filename[30];
int fileLength = 0;

// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
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
int getDataFromFile(char filename[30]) {
    FILE *file = fopen(filename, "r"); //opens file
    
    if (file == NULL) { //checks for no file error
        perror("Error, couldn't open the file.");
        return 1;
    }

    char temp[25];
    while (fgets(temp, 30, file))  { //finds the length of the file - for use with unseen files which may have varying lengths
        fileLength++;
    }

    rewind(file); //puts the file pointer back to 0 so fgets() can be run again
    //defining various variables to be used within the while loop
    char data[25]; 
    int count = 0; 
    //date length 11, time length 6, steps length 10; remember this or string formatting goes weird
    char OutputDate[11]; 
    char OutputTime[6];
    char OutputSteps[10];

    while (fgets(data, 30, file)) { //buffer = a few characters more than max length for safety
        tokeniseRecord(data, ",", OutputDate, OutputTime, OutputSteps); //runs tokenise record function to get data from each line
        strcpy(STEP_INTERVAL[count].date, OutputDate); //copies date to struct
        strcpy(STEP_INTERVAL[count].time, OutputTime); //copies time to struct
        STEP_INTERVAL[count].steps = atoi(OutputSteps); //copies steps to struct - use atoi to save as int
        count++;
    }

    fclose(file);
    return fileLength;

}


int calculations() { //in this function, calculate all the required values that the user may ask for (already have the file length though)
    char FewestStepsArray [2][11]; //index 0 = date, index 1 = time
    int FewestSteps = 1000000;
    char LargestStepsArray [2][11]; //index 0 = date, index 1 = time
    int LargestSteps = 0;
    int Sum = 0;
    char PeriodStart [2][11]; //index 0 = date, index 1 = time
    char PeriodEnd [2][11]; //index 0 = date, index 1 = time
    int Count = 0;
    int LongestPeriod = 0;
    
    //iterate through all data
    for (int i = 0; i < fileLength; i++) {
        //find fewest steps
        if (STEP_INTERVAL[i].steps < FewestSteps) {
            FewestSteps = STEP_INTERVAL[i].steps;
            strcpy(FewestStepsArray[0], STEP_INTERVAL[i].date);
            strcpy(FewestStepsArray[1], STEP_INTERVAL[i].time);
        }
        //find largest steps
        if (STEP_INTERVAL[i].steps > LargestSteps) {
            LargestSteps = STEP_INTERVAL[i].steps;
            strcpy(LargestStepsArray[0], STEP_INTERVAL[i].date);
            strcpy(LargestStepsArray[1], STEP_INTERVAL[i].time);
        }
        //calculate the sum of the values in order to calculate the mean
        Sum += STEP_INTERVAL[i].steps;
        //find the longest continuous period where step count > 500
        if (STEP_INTERVAL[i].steps > 500) {
            
        }
    }
    int mean = Sum / fileLength;

    printf("\n%d\n", mean);
    printf("%s\n%s\n", LargestStepsArray[0], LargestStepsArray[1]);

    return 0;
}
// Complete the main function
int main() {
    char choice;
    while (choice != 'Q') {
        printf("Select from the following options:\n");
        printf("A: Specify a filename to be imported\nB: Display the total number of records in the file\nC: Return the date and time of the timeslot with the fewest steps\n");
        printf("D: Return the date and time of the timeslot with the largest number of steps\nE: Calculate the mean step count of all the records in the file");
        printf("F: Find the longest continuous period where the step count is above 500 steps\nQ: Quit\n");

        scanf(" %c", &choice);
        switch (choice) {
            case 'A':
                printf("Input filename:\n");
                scanf(" %s", filename);
                int fileLength = getDataFromFile(filename);
                
                calculations();
                break;

            case 'B':
                printf("Total records: %d\n", fileLength);
                break;

            case 'C':
                break;
        }
    };

}