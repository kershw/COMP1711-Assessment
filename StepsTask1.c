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
    char filename [21] = "FitnessData_2023.csv";
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
        perror("There is no file, couldn't find data.");
        return 1;
    }

    char data[20];
    int count = 0;
    char fitnessArray[60]; //need to make this 
    while (fgets(data, 60, file))  { //gets each row of data and puts it in fitnessArray.
        printf("%s\n", data);
        fitnessArray[count] = *data;
        count++;
    }

    printf("%d", fitnessArray[0]);
    for (int i=0; i<count; i++){
        char temp = fitnessArray[i];

        tokeniseRecord(temp, ",");

    }
    
    fclose(file);
}