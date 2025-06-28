#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "user.h"


void userMenu() {
   int choice;
    while (1) {
        printf("\n--- User Menu ---\n");
        printf("1. View Trains\n");
        printf("2. Book Ticket\n");
        printf("3. View My Orders\n");
        printf("4. Cancel Ticket\n");
        printf("5. Download Ticket\n");
        printf("6. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayTrains(); break;
            case 2: bookTicket(); break;
            case 3: viewMyOrders(); break;
            case 4: cancelTicket(); break;
            case 5: downloadTicket(); break;
            case 6: return;
            default: printf("Invalid choice. Try again.\n");
        }
    }
}


// ============================
// Function: displayTrains()
// Description: Shows all train information stored in memory.
// ============================

void displayTrains() {
    printf("\n=== Available Trains ===\n");
    for (int i = 0; i < trainCount; i++) {
        printf("Train ID        : %d\n", trains[i].train_id);
        printf("Train Name      : %s\n", trains[i].name);
        printf("Departure       : %s\n", trains[i].departure);
        printf("Destination     : %s\n", trains[i].destination);
        printf("Departure Time  : %s\n", trains[i].time);
        printf("Available Seats : %d\n", trains[i].available_seats);
        printf("-----------------------------------\n");
    }
}


// ============================
// Function: bookTicket()
// Description: Books tickets for a train. Updates seat count and saves to file.
// ============================
void bookTicket() {
    int id, tickets;
    char username[30];
    int found = 0;

    displayTrains();

    printf("Enter your name: ");
    scanf("%s", username);

    printf("Enter Train ID to book: ");
    scanf("%d", &id);

    for (int i = 0; i < trainCount; i++) {
        if (trains[i].train_id == id) {
            Train *t = &trains[i]; // pointer to selected train
            found = 1;

            printf("How many tickets do you want? ");
            scanf("%d", &tickets);

            if (tickets > t->available_seats) {
                printf("Not enough seats available.\n");
                return;
            }

            t->available_seats -= tickets;

            FILE *fp = fopen("data/orders.txt", "a");
            if (fp == NULL) {
                printf("Error opening orders file.\n");
                return;
            }

            time_t now = time(NULL);
            struct tm *tm = localtime(&now);
            char timeStr[30];
            strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M", tm);

            int order_id = rand() % 10000 + 1000;
            fprintf(fp, "%d,%d,%s,%d,%s\n", order_id, id, username, tickets, timeStr);
            fclose(fp);

            // Update trains.txt with new seat count
            FILE *tfp = fopen("data/trains.txt", "w");
            for (int j = 0; j < trainCount; j++) {
                fprintf(tfp, "%d,%s,%s,%s,%s,%d\n",
                        trains[j].train_id, trains[j].name,
                        trains[j].departure, trains[j].destination,
                        trains[j].time, trains[j].available_seats);
            }
            fclose(tfp);

            printf("Ticket booked successfully.\n");
            return;
        }
    }

    if (!found) {
        printf("Train ID not found.\n");
    }
}

void viewMyOrders() {
    char username[30];
    char line[256];

    printf("Enter your name to view your orders: ");
    scanf("%s", username);

    FILE *fp = fopen("data/orders.txt", "r");
    if (fp == NULL) {
        printf("Could not open orders file.\n");
        return;
    }

    printf("\n=== Your Orders ===\n");
    int found = 0;
    while (fgets(line, sizeof(line), fp)) {
        int order_id, train_id, tickets;
        char user[30], timeStr[30];

        sscanf(line, "%d,%d,%[^,],%d,%[^\n]", &order_id, &train_id, user, &tickets, timeStr);
        if (strcmp(user, username) == 0) {
            printf("Order ID: %d\nTrain ID: %d\nTickets: %d\nTime: %s\n", order_id, train_id, tickets, timeStr);
            printf("--------------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("No orders found for %s.\n", username);
    }

    fclose(fp);
}

void cancelTicket() {
    int cancel_id;
    printf("Enter Order ID to cancel: ");
    scanf("%d", &cancel_id);

    FILE *fp = fopen("data/orders.txt", "r");
    FILE *temp = fopen("data/temp.txt", "w");
    if (fp == NULL || temp == NULL) {
        printf("File error.\n");
        return;
    }

    int found = 0;
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        int order_id, train_id, tickets;
        char user[30], timeStr[30];

        sscanf(line, "%d,%d,%[^,],%d,%[^\n]", &order_id, &train_id, user, &tickets, timeStr);

        if (order_id == cancel_id) {
            found = 1;

            // Restore the cancelled tickets to trains
            for (int i = 0; i < trainCount; i++) {
                if (trains[i].train_id == train_id) {
                    trains[i].available_seats += tickets;
                    break;
                }
            }
            continue; // Skip writing this canceled order
        }

        fputs(line, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("data/orders.txt");
    rename("data/temp.txt", "data/orders.txt");

    // Update train file after seat restoration
    FILE *tfp = fopen("data/trains.txt", "w");
    for (int i = 0; i < trainCount; i++) {
        fprintf(tfp, "%d,%s,%s,%s,%s,%d\n",
                trains[i].train_id,
                trains[i].name,
                trains[i].departure,
                trains[i].destination,
                trains[i].time,
                trains[i].available_seats);
    }
    fclose(tfp);

    if (found)
        printf("Order cancelled successfully.\n");
    else
        printf("Order ID not found.\n");
}


void downloadTicket() {
    int search_id;
    printf("Enter your Order ID to download ticket: ");
    scanf("%d", &search_id);

    FILE *fp = fopen("data/orders.txt", "r");
    if (fp == NULL) {
        printf("Could not open orders file.\n");
        return;
    }

    int order_id, train_id, tickets;
    char username[30], timeStr[30];
    int found = 0;

    while (fscanf(fp, "%d,%d,%[^,],%d,%[^\n]\n",
                  &order_id, &train_id, username, &tickets, timeStr) == 5) {
        if (order_id == search_id) {
            found = 1;

            // Find the train info using the train ID
            for (int i = 0; i < trainCount; i++) {
                if (trains[i].train_id == train_id) {
                    printf("\n========== TRAIN TICKET ==========\n");
                    printf("Order ID       : %d\n", order_id);
                    printf("Passenger Name : %s\n", username);
                    printf("Train Name     : %s (ID: %d)\n", trains[i].name, trains[i].train_id);
                    printf("Route          : %s to %s\n", trains[i].departure, trains[i].destination);
                    printf("Departure Time : %s\n", trains[i].time);
                    printf("Tickets Booked : %d\n", tickets);
                    printf("Booking Time   : %s\n", timeStr);
                    printf("==================================\n");
                    break;
                }
            }

            break; // Stop searching after finding the order
        }
    }

    fclose(fp);

    if (!found) {
        printf("Order ID not found. Please check and try again.\n");
    }

    printf("Press Enter to return to menu...");
    getchar();  // flush newline
    getchar();  // wait for Enter
}



