#ifndef USER_H
#define USER_H

// ============================
// Struct Definitions (user.h)
// Used for managing train details and user orders.
// ============================

typedef struct {
    int train_id;
    char name[50];
    char departure[30];
    char destination[30];
    char time[20];
    int available_seats;
} Train;

typedef struct {
    int order_id;
    int train_id;
    char username[30];
    int tickets;
    char timestamp[30];
} Order;

// Declare the shared variables
extern Train *trains;
extern int trainCount;
extern int trainCapacity;

// Function declarations
void loadTrains();  // to allow other files to call it
void displayTrains();
void bookTicket();
void viewMyOrders();
void cancelTicket();
void downloadTicket();
void userMenu();

#endif

