#ifndef HALF_CENTURY_H  // If HALF_CENTURY_H is not defined, define it to avoid multiple inclusions
#define HALF_CENTURY_H

#include <stdio.h>   // Include standard input/output library for file operations and printing
#include <stdlib.h>  // Include standard library for memory allocation and conversion functions
#include <string.h>  // Include string library for string manipulation (e.g., strtok for tokenizing)


// Define the structure for a node in the linked list to store player, match, and value (half-century)
typedef struct HalfCenturyNode {
    int player;                   // Player number
    int match;                    // Match number
    int value;                    // Value (1 indicates a half-century)
    struct HalfCenturyNode* next; // Pointer to the next node in the linked list
} HalfCenturyNode;


// Function to create a new node for the linked list
HalfCenturyNode* createHalfCenturyNode(int player, int match, int value) {
    // Allocate memory for a new node
    HalfCenturyNode* newNode = (HalfCenturyNode*)malloc(sizeof(HalfCenturyNode));
    newNode->player = player;    // Set player number
    newNode->match = match;      // Set match number
    newNode->value = value;      // Set the value (1 for half-century)
    newNode->next = NULL;        // Set the next pointer to NULL initially
    return newNode;              // Return the created node
}


// Function to insert a new node into the linked list
void insertHalfCenturyNode(HalfCenturyNode** head, int player, int match, int value) {
    // Create a new node
    HalfCenturyNode* newNode = createHalfCenturyNode(player, match, value);
    
    // If the list is empty, set the new node as the head
    if (*head == NULL) {
        *head = newNode;
    } else {
        // Otherwise, traverse to the last node and insert the new node
        HalfCenturyNode* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode; // Add the new node at the end
    }
}


// Function to parse the input file and build the linked list of half-centuries
void parseHalfCenturyFile(const char* filename, HalfCenturyNode** head) {
    // Open the file in read mode
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        // If file can't be opened, print error message
        perror("Error opening file");
        return;
    }

    // Define a buffer for reading lines from the file
    char line[1024];
    
    // Skip the header line
    fgets(line, sizeof(line), file); 
    
    int player = 0; // Variable to track the player number
    
    // Read each line from the file
    while (fgets(line, sizeof(line), file)) {
        player++;  // Increment player number for each new line
        char* token = strtok(line, ",");  // Tokenize the line by commas (CSV format)
        int match = 0;  // Start match numbering from 0
        
        // Process each token (match data for the current player)
        while (token != NULL) {
            int value = atoi(token);  // Convert the token to an integer (value of the match)
            if (value == 1) {         // If the value is 1, it indicates a half-century
                // Insert the half-century data into the linked list
                insertHalfCenturyNode(head, player, match, value);
            }
            token = strtok(NULL, ",");  // Move to the next token (next match)
            match++;  // Increment match number
        }
    }

    // Close the file after processing
    fclose(file);
}


// Function to display the list of players and their matches with half-centuries
void displayHalfCenturyList(HalfCenturyNode* head) {
    // Print table header
    printf("Player  Matches with Half-Centuries\n");
    printf("----------------------------------\n");

    int currentPlayer = -1;  // Variable to track the current player being processed
    HalfCenturyNode* temp = head;  // Temporary pointer to traverse the linked list

    // Traverse the linked list and print each player and their half-century matches
    while (temp != NULL) {
        if (temp->player != currentPlayer) {
            // If we encounter a new player, print the player's number
            if (currentPlayer != -1) {
                printf("\n");  // Print a newline between players
            }
            currentPlayer = temp->player;  // Update current player
            printf("%-7d ", currentPlayer); // Print player number
        }
        // Print the match number for the current player
        printf("M%-2d ", temp->match);
        temp = temp->next;  // Move to the next node in the list
    }
    printf("\n");  // Print a newline after the last player's data
}

#endif // HALF_CENTURY_H  // End the header file definition guard
