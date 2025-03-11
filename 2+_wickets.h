// linkedlist.h
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define the structure for a node in the linked list
typedef struct Node {
    int player;             // Player number
    int match;              // Match number
    int value;              // Non-zero value for the match
    struct Node* next;      // Pointer to the next node in the list
} Node;

// Function to create a new node with given data
Node* createNode(int player, int match, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // Allocate memory for the node
    newNode->player = player;                   // Assign player number
    newNode->match = match;                     // Assign match number
    newNode->value = value;                     // Assign value
    newNode->next = NULL;                       // Initialize the next pointer to NULL
    return newNode;                             // Return the new node
}

// Function to insert a new node into the linked list
void insertNode(Node** head, int player, int match, int value) {
    Node* newNode = createNode(player, match, value); // Create a new node
    if (*head == NULL) {                              // If the list is empty
        *head = newNode;                              // Make the new node the head
    } else {
        Node* temp = *head;                           // Start from the head
        while (temp->next != NULL) {                  // Traverse to the end of the list
            temp = temp->next;
        }
        temp->next = newNode;                         // Link the new node at the end
    }
}

// Function to parse the input file and build a linked list
void parseFileAndBuildList(const char* filename, Node** head) {
    FILE* file = fopen(filename, "r");                // Open the file for reading
    if (file == NULL) {                               // Check if the file opened successfully
        perror("Error opening file");                 // Print an error message if it failed
        return;                                       // Exit the function
    }

    char line[1024];                                  // Buffer for reading lines from the file
    fgets(line, sizeof(line), file);                  // Read and discard the header line

    int player = 0;                                   // Initialize player counter
    while (fgets(line, sizeof(line), file) && player < 120) { // Process up to 120 players
        player++;                                     // Increment player number
        char* token = strtok(line, "\t");             // Get the first token (player number)
        int match = 0;                                // Initialize match counter

        while ((token = strtok(NULL, "\t")) != NULL) { // Parse match values
            match++;                                  // Increment match number
            int value = atoi(token);                  // Convert token to integer
            if (value != 0) {                         // Check for non-zero values
                insertNode(head, player, match, value); // Insert into the linked list
            }
        }
    }

    fclose(file);                                     // Close the file
}

// Function to display the linked list in rows per player
void displayLinkedListInRows(Node* head) {
    printf("Player  Matches with Non-Zero Values\n"); // Header for output
    printf("-----------------------------------\n");

    int currentPlayer = -1;                          // Track the current player
    Node* temp = head;                               // Start from the head of the list

    while (temp != NULL) {                           // Traverse the linked list
        if (temp->player != currentPlayer) {         // If the player changes
            if (currentPlayer != -1) {               // If not the first player
                printf("\n");                        // End the row for the previous player
            }
            currentPlayer = temp->player;            // Update to the new player
            printf("%-7d ", currentPlayer);          // Print the player number
        }
        printf("M%-2d(%d) ", temp->match, temp->value); // Print match and value
        temp = temp->next;                           // Move to the next node
    }
    printf("\n");                                    // End the last row
}

#endif