#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"


void adminMenu() {
     int choice;
    while (1) {
        printf("\n--- Admin Panel ---\n");
        printf("1. View All Trains\n");
        printf("2. Add New Train\n");
        printf("3. Delete Train\n");
        printf("4. View All Orders\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayTrains(); break;
            case 2: addTrain(); break;
            case 3: deleteTrain(); break;
            case 4: viewAllOrders(); break;
            case 5: return;
            default: printf("Invalid choice. Try again.\n");
        }
    }
}

// ============================
// Function: addTrain()
// Description: Admin function to add a train and save it to trains.txt.
// ============================
void addTrain() {
    FILE *fp = fopen("data/trains.txt", "a");
    if (fp == NULL) {
        printf("Error opening train file.\n");
        return;
    }

    Train newTrain;
    printf("Enter Train ID: ");
    scanf("%d", &newTrain.train_id);
    printf("Enter Train Name: ");
    scanf(" %[^\n]", newTrain.name);
    printf("Enter Departure Station: ");
    scanf(" %[^\n]", newTrain.departure);
    printf("Enter Destination Station: ");
    scanf(" %[^\n]", newTrain.destination);
    printf("Enter Departure Time: ");
    scanf(" %[^\n]", newTrain.time);
    printf("Enter Available Seats: ");
    scanf("%d", &newTrain.available_seats);

    fprintf(fp, "%d,%s,%s,%s,%s,%d\n",
            newTrain.train_id,
            newTrain.name,
            newTrain.departure,
            newTrain.destination,
            newTrain.time,
            newTrain.available_seats);

    fclose(fp);
    printf("Train added successfully.\n");

    loadTrains(); // refresh in-memory data
    printf("Press Enter to return to menu...");
    getchar();  // Flush leftover newline
    getchar();  // Wait for actual Enter press
}

void deleteTrain() {
    int del_id;
    printf("Enter Train ID to delete: ");
    scanf("%d", &del_id);

    FILE *fp = fopen("data/trains.txt", "r");
    FILE *temp = fopen("data/temp.txt", "w");
    if (fp == NULL || temp == NULL) {
        printf("File error.\n");
        return;
    }

    int found = 0;
    Train tempTrain;

    while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%[^,],%d\n",
                  &tempTrain.train_id,
                  tempTrain.name,
                  tempTrain.departure,
                  tempTrain.destination,
                  tempTrain.time,
                  &tempTrain.available_seats) == 6) {

        if (tempTrain.train_id == del_id) {
            found = 1;
            continue; // Skip this train
        }

        fprintf(temp, "%d,%s,%s,%s,%s,%d\n",
                tempTrain.train_id,
                tempTrain.name,
                tempTrain.departure,
                tempTrain.destination,
                tempTrain.time,
                tempTrain.available_seats);
    }

    fclose(fp);
    fclose(temp);

    remove("data/trains.txt");
    rename("data/temp.txt", "data/trains.txt");

    loadTrains(); // refresh in-memory data

    if (found)
        printf("Train deleted successfully.\n");
    else
        printf("Train ID not found.\n");
}

void viewAllOrders() {
    FILE *fp = fopen("data/orders.txt", "r");
    if (fp == NULL) {
        printf("No orders found.\n");
        return;
    }

    printf("\n=== All Bookings ===\n");
    int order_id, train_id, tickets;
    char username[30], timeStr[30];

    while (fscanf(fp, "%d,%d,%[^,],%d,%[^\n]\n", &order_id, &train_id, username, &tickets, timeStr) == 5) {
        printf("Order ID: %d\nTrain ID: %d\nUser: %s\nTickets: %d\nTime: %s\n", order_id, train_id, username, tickets, timeStr);
        printf("-----------------------------\n");
    }

    fclose(fp);
}
