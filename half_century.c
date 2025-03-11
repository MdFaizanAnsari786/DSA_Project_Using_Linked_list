#include "half_centuary.h"  // Include the header file for the half-century functions
#include <time.h>           // Include time.h for measuring runtime

int main() {
    // Declare the head of the linked list for storing half-century data (initially NULL)
    HalfCenturyNode* head = NULL;

    // Start measuring the time to parse the file
    clock_t startParse = clock();  // Record the start time for parsing

    // Specify the file path of the half-century data to be parsed
    const char* filename = "C:\\Users\\harsh\\OneDrive\\Desktop\\dsa mini 2\\half_centuries.txt";  // File path (can be replaced with your actual path)

    // Call the function to parse the file and populate the linked list
    parseHalfCenturyFile(filename, &head);

    // End measuring the time after parsing the file
    clock_t endParse = clock();  // Record the end time after parsing

    // Calculate and print the time taken for parsing
    double parseTime = ((double)(endParse - startParse)) / CLOCKS_PER_SEC;  // Convert clock ticks to seconds
    printf("Time taken to parse the file: %f seconds\n", parseTime);

    // Start measuring the time for displaying the list
    clock_t startDisplay = clock();  // Record the start time for displaying

    // Call the function to display the list of players and their matches with half-centuries
    displayHalfCenturyList(head);

    // End measuring the time after displaying the list
    clock_t endDisplay = clock();  // Record the end time after displaying

    // Calculate and print the time taken for displaying
    double displayTime = ((double)(endDisplay - startDisplay)) / CLOCKS_PER_SEC;  // Convert clock ticks to seconds
    printf("Time taken to display the list: %f seconds\n", displayTime);

    // Free the dynamically allocated memory for the linked list
    HalfCenturyNode* temp;  // Temporary pointer to traverse and free memory
    while (head != NULL) {
        temp = head;        // Store the current node in temp
        head = head->next;  // Move the head pointer to the next node
        free(temp);         // Free the memory allocated for the current node
    }

    return 0;  // Exit the program successfully
}
