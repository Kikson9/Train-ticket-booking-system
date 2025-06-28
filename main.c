#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "admin.h"
#include "user.h"

#define MAX_TRAINS 100

Train trains[MAX_TRAINS];
int trainCount = 0;

// ============================
// Function: loadTrains()
// Description: Reads train data from trains.txt file and populates the trains array.
// ============================

void loadTrains() {
    FILE *fp = fopen("data/trains.txt", "r");
    if (fp == NULL) {
        printf("Error loading trains.\n");
        return;
    }

    trainCount = 0;
    while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%[^,],%d\n",
                  &trains[trainCount].train_id,
                  trains[trainCount].name,
                  trains[trainCount].departure,
                  trains[trainCount].destination,
                  trains[trainCount].time,
                  &trains[trainCount].available_seats) == 6) {
        trainCount++;
    }

    fclose(fp);
}

int main() {
    int choice;

    srand(time(NULL));
    loadTrains();

    while (1) {
        printf("\n==== Train Ticket Booking System ====\n");
        printf("1. Admin Panel\n");
        printf("2. User Panel\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                adminMenu();
                break;
            case 2:
                userMenu();
                break;
            case 3:
                printf("Thank you for using the system.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
