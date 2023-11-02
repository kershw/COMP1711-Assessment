#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;

// Define any additional variables here



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

// Complete the main function
int main() {
    char filename [21] = "FitnessData_2023.csv"; //gets file
    FILE *file = fopen(filename, "r"); //opens file
    
    if (file == NULL) { //checks for no file error
        perror("There is no file, couldn't find data.");
        return 1;
    }

    char temp[25];
    int fileLength = 0;
    while (fgets(temp, 30, file))  { //finds the length of the file - for use with unseen files which may have varying lengths
        fileLength++;
    }

    rewind(file); //puts the file pointer back to 0 so fgets() can be run again
    FITNESS_DATA STEP_INTERVAL [fileLength]; //defines the array of structs
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

    printf("Number of records in file: %d\n", fileLength);
    for (int i=0; i<3; i++) {
        printf("%s/%s/%d\n", STEP_INTERVAL[i].date, STEP_INTERVAL[i].time, STEP_INTERVAL[i].steps);
    }

    /* iterating through struct array for debugging
    for (int i=0; i<fileLength; i++){
        printf("%d\n", STEP_INTERVAL[i].steps);
    }
    */


    fclose(file);
}