// main.c
#include <stdio.h>
#include <time.h>
#include "2+_wickets.h"  // Include the header file for linked list operations

// Main function
int main() {
    Node* head = NULL;                               // Initialize the linked list head to NULL
    clock_t start, end;                              // Variables for measuring time

    // File path for the input data
    const char* filename = "two_plus_wickets.txt";

    // Measure time for parsing the file and building the linked list
    start = clock();
    parseFileAndBuildList(filename, &head);          // Parse the file and build the list
    end = clock();
    double time_taken = ((double)end - start) / CLOCKS_PER_SEC; // Calculate time in seconds
    printf("Time for reading and processing the file: %f seconds\n", time_taken);

    // Measure time for displaying the linked list
    start = clock();
    printf("Linked List of Non-Zero Values Data:\n");
    displayLinkedListInRows(head);                   // Display the linked list
    end = clock();
    time_taken = ((double)end - start) / CLOCKS_PER_SEC; // Calculate time in seconds
    printf("Time for displaying the linked list: %f seconds\n", time_taken);

    return 0;                                        // Exit the program
}