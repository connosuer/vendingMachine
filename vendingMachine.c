#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 3
#define COLS 3
#define MAX_NAME 20

//defining struct to represent each product in vending machine 
typedef struct {
    char name[MAX_NAME];
    char label[3];
    double price;
    int quantity;
    int is_empty;
} Item;

//creating a 2d array to display inventory
Item machine[ROWS][COLS];
double balance = 0.0; //tracking user balance
double totalSales = 0.0;//tracking total sales 

void initializeMachine() {
	//intializing 3 3d arrays 
    char labels[ROWS][COLS][3] = {{"A1", "A2", "A3"}, {"B1", "B2", "B3"}, {"C1", "C2", "C3"}};
    char names[ROWS][COLS][MAX_NAME] = {
        {"Coke", "Orange Soda", "Root Beer"},
        {"Water", "Grape Soda", "Coke Zero"},
        {"Cream Soda", "Lemonade", "Lime Soda"}
    };
    double prices[ROWS][COLS] = {{1.50, 1.50, 1.50}, {1.00, 1.50, 1.50}, {1.50, 1.25, 1.50}};
    
    //iterate throughe each position in the vending machine
    //for each position copy name to item, label, and assign price 
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            strcpy(machine[i][j].name, names[i][j]);
            strcpy(machine[i][j].label, labels[i][j]);
            machine[i][j].price = prices[i][j];
            machine[i][j].quantity = 5; //intial quantity 
            machine[i][j].is_empty = 0; //indicate that slot is not empty
        }
    }
}

void displayMenu() {
    printf("\n");
    //print item name or empty spaces
    for (int i = 0; i < ROWS; i++) { 
        for (int j = 0; j < COLS; j++) {
            if (machine[i][j].is_empty) {
                printf("|%-15s", ""); //if empty print 15 spaces
            } else {
                printf("|%-15s", machine[i][j].name); //else print item name
            }
        }
        printf("|\n");
	//print labels
	//prints even for empty slots
        for (int j = 0; j < COLS; j++) {
            printf("|%-15s", machine[i][j].label);
        }
        printf("|\n");
    }
    printf("\n[1] Insert money\n");
    printf("[2] Check balance\n");
    printf("[3] Check price\n");
    printf("[4] Purchase\n");
    printf("[5] Return change\n");
    printf("[6] Owner menu\n");
    printf("[7] Exit\n");
    printf("Please select an option: ");
}

void insertMoney() {
    double amount;
    //prompt user
    printf("Amount: ");
    if (scanf("%lf", &amount) == 1) { //validate input
        balance += amount;
        printf("$%.2f added to balance.\n", amount);
    } else {
        printf("Invalid input. Please enter a valid amount.\n");
        while (getchar() != '\n'); // Clear input buffer
    }
}

void checkBalance() {
    printf("Current balance: $%.2f\n", balance);
}

//prompt for item label
void checkPrice() {
    char label[3];
    printf("Label: ");
    scanf("%s", label);
    //search machine array and displays price if found 
    for (int i = 0; i < ROWS; i++) { 
        for (int j = 0; j < COLS; j++) {
            if (strcmp(machine[i][j].label, label) == 0 && !machine[i][j].is_empty) {
                printf("%s is $%.2f\n", machine[i][j].name, machine[i][j].price);
                return;
            }
        }
    }
    printf("Item not found.\n");
}

void purchase() {
    char label[3];
    //prompt user for label
    printf("Label: ");
    scanf("%s", label);
    //iterate through vending machine
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
		//check if current item label matches input and slot is empty
            if (strcmp(machine[i][j].label, label) == 0 && !machine[i][j].is_empty) {
                if (machine[i][j].quantity == 0) { //check if item is in stock
                    printf("Sorry, %s is out of stock.\n", machine[i][j].name);
                } else if (balance < machine[i][j].price) { //check if user has enough funds 
                    printf("Insufficient funds. You need $%.2f more.\n", machine[i][j].price - balance);
                } else { 
			//if both the checks pass
                    balance -= machine[i][j].price; //deduct item price from user fund
                    machine[i][j].quantity--; //decrease item quantity 
                    totalSales += machine[i][j].price; //add price to total sales
                    printf("You purchased %s for $%.2f\n", machine[i][j].name, machine[i][j].price);
                }
                return;
            }
        }
    } 
    //if there is no match
    printf("Item not found.\n");
}

void returnChange() {
    printf("$%.2f is returned\n", balance);
    balance = 0;
}

void ownerMenu() {
    int choice;
    do {
        printf("\nOwner Menu\n");
        printf("[1] Add a new type of item\n");
        printf("[2] Restock\n");
        printf("[3] Check quantity\n");
        printf("[4] Take down a type of item\n");
        printf("[5] Check total sales\n");
        printf("[6] Exit owner menu\n");
        printf("Please select an option: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        
        switch(choice) {
		
	//add new item
            case 1: {
                char name[MAX_NAME];
                double price;
                char label[3];
		//prompt user
                printf("Item name: ");
                scanf("%s", name);
                printf("Item price: ");
		//validate price input
		//if valid cancel and clear input buffer
                if (scanf("%lf", &price) != 1) {
                    printf("Invalid price. Operation cancelled.\n");
                    while (getchar() != '\n'); // Clear input buffer
                    break;
                }
                
                int found = 0;
		//search for empty slot
                for (int i = 0; i < ROWS; i++) {
                    for (int j = 0; j < COLS; j++) {
			//if slot found 
                        if (machine[i][j].name[0] == '\0') {
				//populate with new item details
                            strcpy(machine[i][j].name, name); 
                            machine[i][j].price = price;
                            machine[i][j].quantity = 0;
                            machine[i][j].is_empty = 0; //mark as not empty
                            printf("%s is added to %s with price of $%.2f\n", name, label, price);
                            found = 1;
                            break;
                        }
                    }
                    if (found) break;
                }
                if (!found) {
                    printf("Invalid label. Item not added.\n");
                }
                break;
            }
	//restock
            case 2: {
                char label[3];
                int quantity;
		//prompt user
                printf("Label: ");
                scanf("%s", label);
                printf("Quantity: ");
		//validate quantity
		//if valid cancel and clear input buffer
                if (scanf("%d", &quantity) != 1) {
                    printf("Invalid quantity. Operation cancelled.\n");
                    while (getchar() != '\n'); // Clear input buffer
                    break;
                }
		//search for item and add necessary info
                int found = 0;
                for (int i = 0; i < ROWS; i++) {
                    for (int j = 0; j < COLS; j++) {
                        if (strcmp(machine[i][j].label, label) == 0 && !machine[i][j].is_empty) {
                            machine[i][j].quantity += quantity;
                            printf("%d %s is restocked\n", quantity, machine[i][j].name);
                            found = 1;
                            break;
                        }
                    }
                    if (found) break;
                }
                if (!found) {
                    printf("Item not found.\n");
                }
                break;
            }
	    //check quantity 
            case 3: {
                char label[3];
		//prompt user
                printf("Label: ");
                scanf("%s", label);
                int found = 0;
		//search for item
		//if found print
                for (int i = 0; i < ROWS; i++) {
                    for (int j = 0; j < COLS; j++) {
                        if (strcmp(machine[i][j].label, label) == 0 && !machine[i][j].is_empty) {
                            printf("The stock of %s is %d\n", machine[i][j].name, machine[i][j].quantity);
                            found = 1;
                            break;
                        }
                    }
                    if (found) break;
                }
                if (!found) {
                    printf("Item not found.\n");
                }
                break;
            }
	    
   	    //take down item
            case 4: {
                char label[3];
		//prompt user
                printf("Label: ");
                scanf("%s", label);
                int found = 0;
		//search item
                for (int i = 0; i < ROWS; i++) {
                    for (int j = 0; j < COLS; j++) {
			    //if found print confirm message, reset item details, and mark the slot as empty
                        if (strcmp(machine[i][j].label, label) == 0 && !machine[i][j].is_empty) {
                            printf("%s is taken down\n", machine[i][j].name);
                            machine[i][j].name[0] = '\0';
                            machine[i][j].price = 0;
                            machine[i][j].quantity = 0;
                            machine[i][j].is_empty = 1;
                            found = 1;
                            break;
                        }
                    }
                    if (found) break;
                }
                if (!found) {
                    printf("Item not found.\n");
                }
                break;
            }
	    
	    //check total sales
            case 5:
                printf("Total sales: $%.2f\n", totalSales);
                break;
	    
	    //exit owner menu
            case 6:
                printf("Exiting owner menu.\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (choice != 6);
}

int main() {
    initializeMachine();
    int choice;
    do {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        switch(choice) {
            case 1:
                insertMoney();
                break;
            case 2:
                checkBalance();
                break;
            case 3:
                checkPrice();
                break;
            case 4:
                purchase();
                break;
            case 5:
                returnChange();
                break;
            case 6:
                ownerMenu();
                break;
            case 7:
                printf("Thank you for using the vending machine. Goodbye!\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (choice != 7);
    
    return 0;
}
