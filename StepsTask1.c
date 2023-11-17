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
    char outputDate[11]; 
    char outputTime[6];
    char outputSteps[10];

    while (fgets(data, 30, file)) { //buffer = a few characters more than max length for safety
        tokeniseRecord(data, ",", outputDate, outputTime, outputSteps); //runs tokenise record function to get data from each line
        strcpy(STEP_INTERVAL[count].date, outputDate); //copies date to struct
        strcpy(STEP_INTERVAL[count].time, outputTime); //copies time to struct
        STEP_INTERVAL[count].steps = atoi(outputSteps); //copies steps to struct - use atoi to save as int
        count++;
    }

    fclose(file);
    return fileLength;

}


int calculations(int* fewestStepsIndex, int* mostStepsIndex, int* mean, int* periodStart, int* periodEnd) { //in this function, calculate all the required values that the user may ask for (already have the file length though)

    int tempPeriodStart;
    int fewestSteps = 1000000;
    int mostSteps = 0;
    int sum = 0;
    int count = 0;
    int longestPeriod = 0;
    
    //iterate through all data
    for (int i = 0; i < fileLength; i++) {
        //find fewest steps
        if (STEP_INTERVAL[i].steps < fewestSteps) {
            fewestSteps = STEP_INTERVAL[i].steps;
            *fewestStepsIndex = i;
        }
        
        //find largest steps
        if (STEP_INTERVAL[i].steps > mostSteps) {
            mostSteps = STEP_INTERVAL[i].steps;
            *mostStepsIndex = i;
        }
        //calculate the sum of the values in order to calculate the mean
        Sum += STEP_INTERVAL[i].steps;
        //find the longest continuous period where step count > 500

        if (STEP_INTERVAL[i].steps <= 500) {
            if (count > longestPeriod) {
                longestPeriod = count;
                *periodStart = tempPeriodStart;

                *periodEnd = i;
            }
            Count = 0;
        }

        if (STEP_INTERVAL[i].steps > 500) {
            if (count == 0) {
                tempPeriodStart = i;
            }
            Count++;
        }

        //first check if its over 500
        //if its over it, then increment count and check for count = 0
        //then, if count = 0 then we first check to see if count was greater than longestperiod
        //if it is, then we save tempperiodstart and the current date in the array to the variables for the longest period start/end
        //if not, then continue 
        //if count is > 0

    }
    int temp = (sum / fileLength);
    mean = temp;

    return 0;
}

// Complete the main function
int main() {
    char choice;
    while (choice != 'Q') {
        printf("Select from the following options:\n");
        printf("A: Specify a filename to be imported\nB: Display the total number of records in the file\nC: Return the date and time of the timeslot with the fewest steps\n");
        printf("D: Return the date and time of the timeslot with the largest number of steps\nE: Calculate the mean step count of all the records in the file\n");
        printf("F: Find the longest continuous period where the step count is above 500 steps\nQ: Quit\n");
        scanf(" %c", &choice);
        switch (choice) {
            case 'A':
                printf("Input filename:\n");
                scanf(" %s", filename);
                int fileLength = getDataFromFile(filename);

                int fewestStepsIndex = 0;
                int mostStepsIndex = 0;
                int mean = 0;
                int longestPeriodStartIndex = 0;
                int longestPeriodEndIndex = 0;
                calculations(&fewestStepsIndex, &mostStepsIndex, &mean, &longestPeriodStartIndex, &longestPeriodEndIndex);
                
                break;

            case 'B':
                printf("Total records: %d\n", fileLength);
                break;

            case 'C':
                printf("%s %s\n", STEP_INTERVAL[fewestStepsIndex].date, STEP_INTERVAL[fewestStepsIndex].time);
                break;

            case 'D':
                printf("%s %s\n", STEP_INTERVAL[mostStepsIndex].date, STEP_INTERVAL[mostStepsIndex].time);
                break;

            case 'E':
                break;
        }
    };

}