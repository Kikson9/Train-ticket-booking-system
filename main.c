#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "admin.h"
#include "user.h"

Train *trains = NULL;
int trainCount = 0;
int trainCapacity = 0;

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

        // realloc if needed
        if (trainCount >= trainCapacity) {
            trainCapacity *= 2;
            trains = realloc(trains, trainCapacity * sizeof(Train));
            if (trains == NULL) {
                printf("Reallocation failed.\n");
                exit(1);
            }
        }

        trainCount++;
    }

    fclose(fp);
}

int main() {
    int choice;
    srand(time(NULL));

    trainCapacity = 10;
    trains = malloc(trainCapacity * sizeof(Train));

    if (trains == NULL) {
        printf("Memory allocation failed.\n");
    return 1;
        
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
                free(trains);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
