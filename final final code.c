
#include <stdio.h>
#include <ctype.h>
    float CashPaid;

// Structure to display movies and payment
struct Movie {
    char *MovieName;
    char *price;
    char *payment;
};
// Global variables for movie details
struct Movie movie1, movie2, movie3;

// Global variable to represent the seating arrangement
char seats[5][6] = {
    {'_', '_', '_', '_', '_', '_'},
    {'_', '_', '_', '_', '_', '_'},
    {'_', '_', '_', '_', '_', '_'},
    {'_', '_', '_', '_', '_', '_'},
    {'_', '_', '_', '_', '_', '_'}
};

// Function to print the current seating arrangement
void printSeats() {
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 6; j++) {
            printf("%c ", seats[i][j]);
        }
        printf("\n");
        
    }
}

// Function to book the seat
void bookSeat(int row, char seat) {
    int seatIndex = seat - 'A'; 
    seats[row - 1][seatIndex] = 'X'; 
}

// Function to process cash payment
void Cash(float amount) {


    printf("Enter the amount of cash paid: EGP");
    scanf("%f", &CashPaid);

    // Check if the cash paid is sufficient
    if (CashPaid >= amount) {
        float change = CashPaid - amount;
        printf("Payment successful. Your change is EGP%.2f.\n", change);
    } else {
        printf("Insufficient cash. Payment failed.\n");
    }
}

// Function to process Visa payment
void Visa(float amount) {
    printf("Please pay EGP%.2f with Visa.\n", amount);
}

// Function to write transaction history to a file
void receipt(int totalAmount, float CashPaid) {
    FILE *file = fopen("transaction_history.txt", "a"); // Open file in append mode
    if (file != NULL) {
        fprintf(file, "Transaction: EGP%d\n", totalAmount);
        fprintf(file, "Amount Paid in cash: EGP%.2f\n", CashPaid);
        fclose(file);
    } else {
        printf("Error: Could not open the file for writing.\n");
    }
}

int main() {
    int num, row;
    float amount = 120;
    char seat;

    // Initialize movie details
    movie1.MovieName = "1. Batman";
    movie2.MovieName = "2. Me Before You";
    movie3.MovieName = "3. John Wick 4";
    movie1.price = "Ticket price is 120EGP\n";
    movie1.payment = "For Visa press 1\nFor Cash press 2\n";

    printf("%s\n", movie1.MovieName);
    printf("%s\n", movie2.MovieName);
    printf("%s\n", movie3.MovieName);
    printf("Enter the number of your chosen movie: ");
    scanf("%d", &num);

    // Displaying the chosen movie
    switch (num) {
        case 1:
            printf("Your chosen movie is Batman\n");
            break;
        case 2:
            printf("Your chosen movie is Me Before You\n");
            break;
        case 3:
            printf("Your chosen movie is John Wick 4\n");
            break;
        default:
            printf("Invalid selection\n");
            return 0;
    }

    // Booking seats
    int x = 1;
    int sum = 0;
    while (x == 1) {
        printf("Please book a seat\n");
        printf("Seats Arrangement\n");
        printSeats();
        printf("A B C D E F\n");
        printf("Enter seat letter (A-F) and row number (1-5): ");
        scanf(" %c %d", &seat, &row);
        seat = toupper(seat);

        // Cinema hall limitation
        if (row < 1 || row > 5 || seat < 'A' || seat > 'F') {
            printf("Invalid input!\n");
            continue;
        }

        // Booking confirmation
        if (seats[row - 1][seat - 'A'] == 'X') {
            printf("Sorry, the seat is already booked.\n");
        } else {
            bookSeat(row, seat);
            printf("\nSeat %c%d booked successfully!\n", seat, row);
            sum += amount; // Accumulate payment
        }

        // Displaying updated seats arrangement
        printf("Updated Seats Arrangement\n");
        printSeats();
 printf("A B C D E F\n");
 
 
        printf("Do you want to book another seat? (1 for yes, 0 for no): ");
        scanf("%d", &x);
    }
//To cancel booking
    printf("For cancellation press 0\nPress 1 to proceed\n");
    int choice;
    scanf("%d", &choice);
    if (choice == 0) {
        while (choice == 0) {
            printf("Choose your booked seat:");
            scanf(" %c %d", &seat, &row);
            seat = toupper(seat);
           
            if (seats[row - 1][seat - 'A'] == 'X') {
                seats[row - 1][seat - 'A'] = '_';
                printf("Seat %c%d has been cancelled.\n", seat, row);
                // Deduct the price of the cancelled seat from the total amount
                sum -= amount;
            } else {
                printf("This seat is not booked\n");
            }
            
            // Display updated seats arrangement
            printf("Updated Seats Arrangement after cancellation\n");
            printSeats();
             printf("A B C D E F\n");
             
        //if the user wants to cancel more than one seat
            printf("For more cancellations press 0\nPress 1 to proceed with payment\n");
            scanf("%d", &choice);
        }
    } 

    // Displaying the ticket price
    printf("%s", movie1.price);

    // Displaying the total amount
    printf("Total amount: EGP%d\n", sum);

    // Payment process
    printf("Please choose your payment method\n%s", movie1.payment);
    scanf("%d", &num);

    // Process user's choice
    switch (num) {
        case 1:
            Visa(sum);
            break;
        case 2:
            Cash(sum);
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }

    // receipt function calling
    receipt(sum, CashPaid); // cash paid is equal to the total amount paid in cash

    return 0;
}