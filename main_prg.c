#include <stdio.h>   // Include standard input/output library for printing to console and taking input
#include <stdlib.h>  // Include standard library for using system() function to execute commands

int main() {
    int choice;  // Variable to store the user's choice

    // Display the menu options for the user to choose from
    printf("Please choose an option:\n");
    printf("1. Display Half Century\n");
    printf("2. Display Wickets\n");
    printf("3. Display All-Rounder\n");
    printf("4. Display Transpose Matrix\n");

    // Input loop to ensure the user enters a valid choice between 1 and 4
    while (1) {
        printf("Enter your choice (1-4): ");
        scanf("%d", &choice);  // Take input from the user and store it in 'choice'

        // Check if the input is valid (i.e., a number between 1 and 4)
        if (choice >= 1 && choice <= 4) {
            break;  // Exit the loop if the input is valid
        } else {
            printf("Invalid choice! Please enter a number between 1 and 4.\n");  // Display error message for invalid input
        }
    }

    // Execute the corresponding program based on the user's choice using the system() function
    switch (choice) {
        case 1:  // If user selects option 1
            // Compile and run the 'half_century.c' program
            system("gcc \"C:\\Users\\harsh\\OneDrive\\Desktop\\dsa mini 2\\half_century.c\" -o half_century.exe && half_century.exe");
            break;
        case 2:  // If user selects option 2
            // Compile and run the 'wickets.c' program
            system("gcc \"C:\\Users\\harsh\\OneDrive\\Desktop\\dsa mini 2\\2+_wickets.c\" -o wickets.exe && wickets.exe");
            break;
        case 3:  // If user selects option 3
            // Compile and run the 'all_rounder.c' program
            system("gcc \"C:\\Users\\harsh\\OneDrive\\Desktop\\dsa mini 2\\all_rounder.c\" -o all_rounder.exe && all_rounder.exe");
            break;
        case 4:  // If user selects option 4
            // Compile and run the 'transpose_matrix.c' program
            system("gcc \"C:\\Users\\harsh\\OneDrive\\Desktop\\dsa mini 2\\transpose_matrix.c\" -o transpose_matrix.exe && transpose_matrix.exe");
            break;
        default:
            // This section will never be reached because of the validation in the while loop
            break;
    }

    return 0;  // Return 0 to indicate successful execution of the program
}
