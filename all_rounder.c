#include <stdio.h>    // Standard input-output header for printf and other functions
#include <stdlib.h>   // For malloc and free functions
#include <string.h>   // For string manipulation functions (not directly used in the code)
#include <time.h>     // For clock and time functions to measure runtime

// Include the necessary header files (assumed to be custom headers for half century and wickets functionality)
#include "half_centuary.h"   // Header for parsing half-century data
#include "2+_wickets.h"      // Header for parsing wickets data

// Define the structure for a node in the all-rounder linked list
typedef struct AllRounderNode {
    int player;            // Player ID
    int match;             // Match ID
    int halfCentury;       // Number of half centuries by the player in the match
    int wickets;           // Number of wickets taken by the player in the match
    struct AllRounderNode* next;  // Pointer to the next node in the list
} AllRounderNode;

// Define the structure for a node in the all-rounder summary linked list
typedef struct AllRounderSummaryNode {
    int player;                   // Player ID
    int totalHalfCenturies;       // Total half centuries by the player
    int totalWickets;             // Total wickets taken by the player
    struct AllRounderSummaryNode* next;  // Pointer to the next node in the summary list
} AllRounderSummaryNode;

// Function to create a new node for all-rounders
AllRounderNode* createAllRounderNode(int player, int match, int halfCentury, int wickets) {
    AllRounderNode* newNode = (AllRounderNode*)malloc(sizeof(AllRounderNode));  // Dynamically allocate memory for a new node
    newNode->player = player;       // Set the player ID
    newNode->match = match;         // Set the match ID
    newNode->halfCentury = halfCentury;  // Set the number of half centuries
    newNode->wickets = wickets;     // Set the number of wickets
    newNode->next = NULL;           // Set the next pointer to NULL (end of list)
    return newNode;                 // Return the new node
}

// Function to insert a new all-rounder node
void insertAllRounderNode(AllRounderNode** head, int player, int match, int halfCentury, int wickets) {
    AllRounderNode* newNode = createAllRounderNode(player, match, halfCentury, wickets);  // Create a new all-rounder node
    if (*head == NULL) {               // If the list is empty
        *head = newNode;               // Set the head to the new node
    } else {                           // If the list is not empty
        AllRounderNode* temp = *head;  // Traverse to the last node
        while (temp->next != NULL) {
            temp = temp->next;         // Move to the next node
        }
        temp->next = newNode;          // Set the last node's next to the new node
    }
}

// Function to create a new summary node for all-rounders
AllRounderSummaryNode* createAllRounderSummaryNode(int player, int totalHalfCenturies, int totalWickets) {
    AllRounderSummaryNode* newNode = (AllRounderSummaryNode*)malloc(sizeof(AllRounderSummaryNode));  // Allocate memory for new summary node
    newNode->player = player;               // Set player ID
    newNode->totalHalfCenturies = totalHalfCenturies;  // Set total half centuries
    newNode->totalWickets = totalWickets;   // Set total wickets
    newNode->next = NULL;                   // Set the next pointer to NULL
    return newNode;                         // Return the new summary node
}

// Function to insert a new summary node into the all-rounder summary list
void insertAllRounderSummaryNode(AllRounderSummaryNode** head, int player, int totalHalfCenturies, int totalWickets) {
    AllRounderSummaryNode* newNode = createAllRounderSummaryNode(player, totalHalfCenturies, totalWickets);  // Create new summary node
    if (*head == NULL) {                  // If the list is empty
        *head = newNode;                  // Set the head to the new node
    } else {                              // If the list is not empty
        AllRounderSummaryNode* temp = *head;  // Traverse to the last node
        while (temp->next != NULL) {
            temp = temp->next;             // Move to the next node
        }
        temp->next = newNode;              // Set the last node's next to the new summary node
    }
}

// Function to parse the half-century and wickets data and build the all-rounder list
void parseAllRounderFile(const char* halfCenturyFile, const char* wicketsFile, AllRounderNode** head, AllRounderSummaryNode** summaryHead) {
    HalfCenturyNode* halfCenturyHead = NULL;  // Initialize the head of the half-century list
    Node* wicketsHead = NULL;                 // Initialize the head of the wickets list

    // Parse half-century data
    parseHalfCenturyFile(halfCenturyFile, &halfCenturyHead);

    // Parse wickets data
    parseFileAndBuildList(wicketsFile, &wicketsHead);

    // Merge the two linked lists to identify all-rounders and build the summary list
    HalfCenturyNode* tempHalfCentury = halfCenturyHead;  // Traverse the half-century list
    while (tempHalfCentury != NULL) {
        Node* tempWickets = wicketsHead;  // Traverse the wickets list
        while (tempWickets != NULL) {
            if (tempHalfCentury->player == tempWickets->player && tempHalfCentury->match == tempWickets->match) {  // Check if the player and match match
                if (tempWickets->value >= 2) {  // Check if the player took 2 or more wickets
                    insertAllRounderNode(head, tempHalfCentury->player, tempHalfCentury->match, 1, tempWickets->value);  // Insert into the all-rounder list
                }
            }
            tempWickets = tempWickets->next;  // Move to the next wicket record
        }
        tempHalfCentury = tempHalfCentury->next;  // Move to the next half-century record
    }

    // Build the summary list by calculating total half-centuries and total wickets for each player
    AllRounderNode* temp = *head;  // Traverse the all-rounder list
    while (temp != NULL) {
        AllRounderSummaryNode* summaryTemp = *summaryHead;  // Traverse the summary list to check if the player is already added
        int found = 0;  // Flag to check if the player is found in the summary list
        while (summaryTemp != NULL) {
            if (summaryTemp->player == temp->player) {
                found = 1;  // Player is already in the summary list
                break;
            }
            summaryTemp = summaryTemp->next;  // Move to the next summary node
        }

        if (!found) {  // If the player is not found in the summary list
            int totalHalfCenturies = 0;  // Initialize total half-centuries count
            int totalWickets = 0;        // Initialize total wickets count
            HalfCenturyNode* tempHalfCentury = halfCenturyHead;  // Traverse the half-century list
            while (tempHalfCentury != NULL) {
                if (tempHalfCentury->player == temp->player) {
                    totalHalfCenturies++;  // Increment total half-centuries for the player
                }
                tempHalfCentury = tempHalfCentury->next;  // Move to the next half-century record
            }

            Node* tempWickets = wicketsHead;  // Traverse the wickets list
            while (tempWickets != NULL) {
                if (tempWickets->player == temp->player) {
                    totalWickets += tempWickets->value;  // Add total wickets for the player
                }
                tempWickets = tempWickets->next;  // Move to the next wicket record
            }

            if (totalHalfCenturies > 0 && totalWickets > 0) {  // If player has both half-centuries and wickets
                insertAllRounderSummaryNode(summaryHead, temp->player, totalHalfCenturies, totalWickets);  // Insert into the summary list
            }
        }
        temp = temp->next;  // Move to the next all-rounder node
    }
}

// Function to display the all-rounder summary list
void displayAllRounderSummary(AllRounderSummaryNode* head) {
    printf("\nAll-Rounder Summary (Player, Total Half-Centuries, Total Wickets)\n");
    printf("--------------------------------------------------------------\n");

    AllRounderSummaryNode* temp = head;  // Traverse the summary list
    while (temp != NULL) {
        printf("Player: %-7d  Half-Centuries: %-2d  Wickets: %-2d\n", temp->player, temp->totalHalfCenturies, temp->totalWickets);  // Display summary data
        temp = temp->next;  // Move to the next summary node
    }
    printf("\n");
}

// Main function to execute the program
int main() {
    AllRounderNode* allRounderHead = NULL;        // Head of the all-rounder list
    AllRounderSummaryNode* allRounderSummaryHead = NULL;  // Head of the all-rounder summary list

    clock_t start, end;  // Variables to measure runtime
    double totalTime;

    // Start timing the program
    start = clock();

    // Measure time for parsing the data files
    clock_t parseStart = clock();
    parseAllRounderFile("C:\\Users\\harsh\\OneDrive\\Desktop\\dsa mini 2\\half_centuries.txt", 
                        "C:\\Users\\harsh\\OneDrive\\Desktop\\dsa mini 2\\two_plus_wickets.txt", 
                        &allRounderHead, &allRounderSummaryHead);  // Parse the half-century and wickets data
    clock_t parseEnd = clock();
    printf("Time for parsing data files: %f seconds\n", (double)(parseEnd - parseStart) / CLOCKS_PER_SEC);

    // Measure time for displaying the all-rounder summary
    clock_t displayStart = clock();
    displayAllRounderSummary(allRounderSummaryHead);  // Display the all-rounder summary
    clock_t displayEnd = clock();
    printf("Time for displaying summary: %f seconds\n", (double)(displayEnd - displayStart) / CLOCKS_PER_SEC);

    // End timing the program
    end = clock();
    totalTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Total runtime of the program: %f seconds\n", totalTime);  // Print the total runtime

    return 0;
}
