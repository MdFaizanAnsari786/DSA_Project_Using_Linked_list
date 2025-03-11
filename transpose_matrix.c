#include <stdio.h>      // Standard input/output library for printf, fopen, etc.
#include <stdlib.h>     // Standard library for malloc, free, atoi, etc.
#include <string.h>     // String library for strtok, etc.
#include <time.h>       // Library for measuring execution time

// Define the structure for a node in the linked list
typedef struct Node {
    int row;            // Row number in the sparse matrix
    int col;            // Column number in the sparse matrix
    int value;          // Non-zero value at the given row and column
    struct Node* next;  // Pointer to the next node in the linked list
} Node;

// Function to create a new node
Node* createNode(int row, int col, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // Allocate memory for the new node
    newNode->row = row;                          // Assign the row number
    newNode->col = col;                          // Assign the column number
    newNode->value = value;                      // Assign the non-zero value
    newNode->next = NULL;                        // Initialize the next pointer to NULL
    return newNode;                              // Return the new node
}

// Function to insert a node into the linked list
void insertNode(Node** head, int row, int col, int value) {
    Node* newNode = createNode(row, col, value); // Create a new node with given data
    if (*head == NULL) {                         // If the list is empty
        *head = newNode;                         // Make the new node the head
    } else {
        Node* temp = *head;                      // Start from the head of the list
        while (temp->next != NULL) {             // Traverse to the end of the list
            temp = temp->next;
        }
        temp->next = newNode;                    // Link the new node at the end
    }
}

// Function to parse a data file and create a sparse matrix linked list
void parseFileToSparseMatrix(const char* filename, Node** head) {
    FILE* file = fopen(filename, "r");           // Open the file for reading
    if (file == NULL) {                          // Check if the file is opened successfully
        return;                                  // If not, return without doing anything
    }

    char line[4096];                             // Buffer for reading lines from the file
    fgets(line, sizeof(line), file);             // Read and discard the header line

    int row = 0;                                 // Initialize row counter
    while (fgets(line, sizeof(line), file)) {    // Read each line until end of file
        row++;                                   // Increment row number
        char* token = strtok(line, "\t");        // Get the first token (column value)
        int col = 0;                             // Initialize column counter
        while (token != NULL) {                  // Process each token in the line
            col++;                               // Increment column number
            int value = atoi(token);             // Convert token to an integer
            if (value != 0) {                    // If the value is non-zero
                insertNode(head, row, col, value); // Insert into the linked list
            }
            token = strtok(NULL, "\t");          // Get the next token
        }
    }

    fclose(file);                                // Close the file after reading
}

// Function to transpose a sparse matrix represented by a linked list
Node* transposeSparseMatrix(Node* head) {
    Node* transposed = NULL;                     // Initialize a new list for transposed matrix
    Node* temp = head;                           // Start from the head of the original matrix

    while (temp != NULL) {                       // Traverse the original matrix
        insertNode(&transposed, temp->col, temp->row, temp->value); // Insert transposed data
        temp = temp->next;                       // Move to the next node
    }

    return transposed;                           // Return the transposed matrix
}

// Function to display a sparse matrix in tabular format
void displaySparseMatrix(Node* head, int rows, int cols, const char* title, const char* rowLabel, const char* colLabel) {
    printf("\n%s\n", title);                     // Print the matrix title
    printf("%-12s", rowLabel);                   // Print the row label
    for (int j = 1; j <= cols; j++) {            // Print column labels
        printf("%-3s%-2d", colLabel, j);
    }
    printf("\n");

    Node* temp = head;                           // Start from the head of the list
    for (int i = 1; i <= rows; i++) {            // Iterate through all rows
        printf("%-12d", i);                      // Print the row label
        for (int j = 1; j <= cols; j++) {        // Iterate through all columns
            if (temp != NULL && temp->row == i && temp->col == j) {
                printf("%-7d", temp->value);     // Print the value if present
                temp = temp->next;               // Move to the next node
            } else {
                printf("%-7d", 0);               // Print 0 for empty cells
            }
        }
        printf("\n");
    }
}

int main() {
    clock_t start, end;                          // Variables for timing execution
    double time_taken;                           // Variable for storing elapsed time

    Node* halfCenturies = NULL;                  // Linked list for half-centuries matrix
    Node* wickets = NULL;                        // Linked list for wickets matrix

    // File paths for the data
    const char* halfCenturiesFile = "half_centuries.txt"; // Input file for half-centuries
    const char* wicketsFile = "wickets.txt";             // Input file for wickets

    // Start timer for parsing files
    start = clock();
    parseFileToSparseMatrix(halfCenturiesFile, &halfCenturies); // Parse half-centuries file
    parseFileToSparseMatrix(wicketsFile, &wickets);            // Parse wickets file
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;     // Calculate elapsed time
    printf("Time taken to parse files and create sparse matrices: %f seconds\n", time_taken);

    // Start timer for transposing the sparse matrices
    start = clock();
    Node* halfCenturiesTranspose = transposeSparseMatrix(halfCenturies); // Transpose half-centuries
    Node* wicketsTranspose = transposeSparseMatrix(wickets);            // Transpose wickets
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;              // Calculate elapsed time
    printf("Time taken to transpose sparse matrices: %f seconds\n", time_taken);

    // Start timer for displaying sparse matrices
    start = clock();
    displaySparseMatrix(halfCenturies, 120, 74, "Half-Centuries Matrix (Original):", "P", "M"); // Display original half-centuries matrix
    displaySparseMatrix(halfCenturiesTranspose, 74, 120, "Half-Centuries Matrix (Transposed):", "M", "P"); // Display transposed half-centuries matrix
    displaySparseMatrix(wickets, 120, 74, "Wickets Matrix (Original):", "P", "M");            // Display original wickets matrix
    displaySparseMatrix(wicketsTranspose, 74, 120, "Wickets Matrix (Transposed):", "M", "P"); // Display transposed wickets matrix
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;                                     // Calculate elapsed time
    printf("Time taken to display sparse matrices: %f seconds\n", time_taken);

    return 0;                                           // Exit the program
}
