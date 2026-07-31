#include <stdio.h>
#include <string.h>

#define MAX 10
#define VEHICLE_COUNT 7

// =====================================================
// STRUCTURES
// =====================================================

struct Customer
{
    char name[50];
    char email[50];
    char password[20];
    char phone[15];
};

struct Vehicle
{
    int id;
    char type[20];
    char model[40];
    float rate;
    char status[25];
};

struct Booking
{
    char vehicle[40];
    char startDate[15];
    char endDate[15];

    int rentalType;       // 1 = Per Hour, 2 = Per Day
    int hours;
    int days;

    float charge;

    char paymentStatus[20];
    char paymentMethod[20];
    char transactionID[30];
};


// =====================================================
// GLOBAL DATA
// =====================================================

struct Customer customers[MAX];
int customerCount = 0;


// 7 Vehicles
// 4 Available
// 2 Rented
// 1 Under Maintenance

struct Vehicle vehicles[VEHICLE_COUNT] =
{
    {1, "Car",  "Toyota Corolla",        3000,  "Available"},
    {2, "Car",  "Honda Civic",           2500,  "Available"},
    {3, "Bike", "Yamaha R15",            1000,  "Available"},
    {4, "SUV",  "Toyota Fortuner",       3200,  "Under Maintenance"},
    {5, "Car",  "Nissan X-Trail",        5000,  "Available"},
    {6, "Bike", "Suzuki Gixxer",         750,  "Rented"},
    {7, "SUV",  "Mitsubishi Outlander",  7000,  "Rented"}
};

struct Booking bookings[MAX];
int bookingCount = 0;


// =====================================================
// FUNCTION DECLARATIONS
// =====================================================

void mainMenu();

void customerRegistration();
void customerLogin();
void forgotPassword();
void customerMenu();

void viewVehicles();
void searchVehicle();
void bookVehicle();
void rentalCharges();
void makePayment();
void rentalHistory();

void adminLogin();
void adminMenu();
void trackAvailability();
void updateVehicle();
void generateReports();


// =====================================================
// CUSTOMER REGISTRATION
// =====================================================

void customerRegistration()
{
    if (customerCount >= MAX)
    {
        printf("\nCustomer limit reached!\n");
        return;
    }

    printf("\n========================================\n");
    printf("          CUSTOMER REGISTRATION\n");
    printf("========================================\n");

    printf("Name: ");
    scanf(" %[^\n]", customers[customerCount].name);

    printf("Email: ");
    scanf("%s", customers[customerCount].email);

    // Check duplicate email
    for (int i = 0; i < customerCount; i++)
    {
        if (strcmp(customers[i].email,
                   customers[customerCount].email) == 0)
        {
            printf("\nEmail already registered!\n");
            return;
        }
    }

    printf("Password: ");
    scanf("%s", customers[customerCount].password);

    printf("Phone: ");
    scanf("%s", customers[customerCount].phone);

    customerCount++;

    printf("\nAccount Created Successfully!\n");
}


// =====================================================
// CUSTOMER LOGIN
// =====================================================

void customerLogin()
{
    char email[50];
    char password[20];

    printf("\n========================================\n");
    printf("             CUSTOMER LOGIN\n");
    printf("========================================\n");

    printf("Email: ");
    scanf("%s", email);

    printf("Password: ");
    scanf("%s", password);

    for (int i = 0; i < customerCount; i++)
    {
        if (strcmp(email, customers[i].email) == 0 &&
            strcmp(password, customers[i].password) == 0)
        {
            printf("\nLogin Successful!\n");
            printf("Welcome, %s!\n", customers[i].name);

            customerMenu();

            return;
        }
    }

    printf("\nInvalid Login Details!\n");
    printf("Use Forgot Password if you forgot your password.\n");
}


// =====================================================
// FORGOT PASSWORD
// =====================================================

void forgotPassword()
{
    char email[50];
    char phone[15];
    char newPassword[20];

    int found = -1;

    printf("\n========================================\n");
    printf("             FORGOT PASSWORD\n");
    printf("========================================\n");

    printf("Enter Registered Email: ");
    scanf("%s", email);

    for (int i = 0; i < customerCount; i++)
    {
        if (strcmp(email, customers[i].email) == 0)
        {
            found = i;
            break;
        }
    }

    if (found == -1)
    {
        printf("\nEmail not found!\n");
        return;
    }

    printf("Enter Registered Phone Number: ");
    scanf("%s", phone);

    if (strcmp(phone, customers[found].phone) == 0)
    {
        printf("\nIdentity Verified Successfully!\n");

        printf("Enter New Password: ");
        scanf("%s", newPassword);

        strcpy(customers[found].password, newPassword);

        printf("\nPassword Reset Successfully!\n");
        printf("You can now login with your new password.\n");
    }
    else
    {
        printf("\nPhone number does not match!\n");
        printf("Password was not changed.\n");
    }
}


// =====================================================
// CUSTOMER MENU
// =====================================================

void customerMenu()
{
    int choice;

    do
    {
        printf("\n========================================\n");
        printf("              CUSTOMER MENU\n");
        printf("========================================\n");

        printf("1. View Available Vehicles\n");
        printf("2. Search Vehicle\n");
        printf("3. Book and Rent Vehicle\n");
        printf("4. View Rental Charges\n");
        printf("5. Make Payment\n");
        printf("6. View Rental History\n");
        printf("7. Logout\n");

        printf("\nChoice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                viewVehicles();
                break;

            case 2:
                searchVehicle();
                break;

            case 3:
                bookVehicle();
                break;

            case 4:
                rentalCharges();
                break;

            case 5:
                makePayment();
                break;

            case 6:
                rentalHistory();
                break;

            case 7:
                printf("\nLogged out successfully!\n");
                break;

            default:
                printf("\nInvalid Choice!\n");
        }

    } while (choice != 7);
}


// =====================================================
// VIEW AVAILABLE VEHICLES
// =====================================================

void viewVehicles()
{
    int found = 0;

    printf("\n========================================\n");
    printf("          AVAILABLE VEHICLES\n");
    printf("========================================\n");

    for (int i = 0; i < VEHICLE_COUNT; i++)
    {
        if (strcmp(vehicles[i].status, "Available") == 0)
        {
            printf("\n----------------------------------------\n");

            printf("ID     : %d\n", vehicles[i].id);
            printf("Type   : %s\n", vehicles[i].type);
            printf("Model  : %s\n", vehicles[i].model);
            printf("Rate   : %.2f per day\n", vehicles[i].rate);
            printf("Rate   : %.2f per hour\n", vehicles[i].rate / 8);
            printf("Status : %s\n", vehicles[i].status);

            found = 1;
        }
    }

    if (found == 0)
    {
        printf("\nNo vehicles are currently available.\n");
    }
}


// =====================================================
// SEARCH VEHICLE
// =====================================================

void searchVehicle()
{
    char model[40];

    printf("\n========================================\n");
    printf("             SEARCH VEHICLE\n");
    printf("========================================\n");

    printf("Enter Vehicle Model: ");
    scanf(" %[^\n]", model);

    for (int i = 0; i < VEHICLE_COUNT; i++)
    {
        if (strcmp(model, vehicles[i].model) == 0)
        {
            printf("\nVehicle Found!\n");

            printf("----------------------------------------\n");
            printf("ID          : %d\n", vehicles[i].id);
            printf("Type        : %s\n", vehicles[i].type);
            printf("Model       : %s\n", vehicles[i].model);
            printf("Daily Rate  : %.2f\n", vehicles[i].rate);
            printf("Hourly Rate : %.2f\n",
                   vehicles[i].rate / 8);
            printf("Status      : %s\n", vehicles[i].status);

            return;
        }
    }

    printf("\nVehicle Not Found!\n");
}


// =====================================================
// BOOK AND RENT VEHICLE
// =====================================================

void bookVehicle()
{
    int id;
    int rentalType;
    int hours;
    int days;

    if (bookingCount >= MAX)
    {
        printf("\nBooking limit reached!\n");
        return;
    }

    printf("\n========================================\n");
    printf("              BOOK VEHICLE\n");
    printf("========================================\n");

    printf("Enter Vehicle ID: ");
    scanf("%d", &id);

    for (int i = 0; i < VEHICLE_COUNT; i++)
    {
        if (vehicles[i].id == id)
        {
            // Check vehicle availability
            if (strcmp(vehicles[i].status, "Available") != 0)
            {
                printf("\nSorry! This vehicle is not available.\n");
                printf("Current Status: %s\n",
                       vehicles[i].status);
                return;
            }

            printf("\n----------------------------------------\n");
            printf("Vehicle       : %s\n",
                   vehicles[i].model);

            printf("Daily Rate    : %.2f\n",
                   vehicles[i].rate);

            printf("Hourly Rate   : %.2f\n",
                   vehicles[i].rate / 8);

            printf("----------------------------------------\n");

            printf("\nSelect Rental Type:\n");
            printf("1. Per Hour\n");
            printf("2. Per Day\n");

            printf("\nChoice: ");
            scanf("%d", &rentalType);


            // =========================================
            // PER HOUR
            // =========================================

            if (rentalType == 1)
            {
                printf("\nEnter Start Date: ");
                scanf("%s",
                      bookings[bookingCount].startDate);

                printf("Enter Number of Hours: ");
                scanf("%d", &hours);

                if (hours <= 0)
                {
                    printf("\nInvalid number of hours!\n");
                    return;
                }

                bookings[bookingCount].rentalType = 1;
                bookings[bookingCount].hours = hours;
                bookings[bookingCount].days = 0;

                bookings[bookingCount].charge =
                    hours * (vehicles[i].rate / 8);

                strcpy(bookings[bookingCount].endDate,
                       "N/A");
            }


            // =========================================
            // PER DAY
            // =========================================

            else if (rentalType == 2)
            {
                printf("\nEnter Start Date: ");
                scanf("%s",
                      bookings[bookingCount].startDate);

                printf("Enter End Date: ");
                scanf("%s",
                      bookings[bookingCount].endDate);

                printf("Enter Number of Days: ");
                scanf("%d", &days);

                if (days <= 0)
                {
                    printf("\nInvalid number of days!\n");
                    return;
                }

                bookings[bookingCount].rentalType = 2;
                bookings[bookingCount].days = days;
                bookings[bookingCount].hours = 0;

                bookings[bookingCount].charge =
                    days * vehicles[i].rate;
            }


            else
            {
                printf("\nInvalid Rental Type!\n");
                return;
            }


            // =========================================
            // STORE BOOKING INFORMATION
            // =========================================

            strcpy(bookings[bookingCount].vehicle,
                   vehicles[i].model);

            strcpy(bookings[bookingCount].paymentStatus,
                   "Pending");

            strcpy(bookings[bookingCount].paymentMethod,
                   "Not Selected");

            strcpy(bookings[bookingCount].transactionID,
                   "N/A");


            // Change vehicle status
            strcpy(vehicles[i].status, "Rented");

            bookingCount++;


            // =========================================
            // BOOKING CONFIRMATION
            // =========================================

            printf("\n========================================\n");
            printf("           BOOKING CONFIRMED!\n");
            printf("========================================\n");

            printf("Vehicle      : %s\n",
                   vehicles[i].model);

            if (rentalType == 1)
            {
                printf("Rental Type  : Per Hour\n");
                printf("Hours        : %d\n",
                       hours);

                printf("Hourly Rate  : %.2f\n",
                       vehicles[i].rate / 8);
            }
            else
            {
                printf("Rental Type  : Per Day\n");
                printf("Days         : %d\n",
                       days);

                printf("Daily Rate   : %.2f\n",
                       vehicles[i].rate);
            }

            printf("Start Date   : %s\n",
                   bookings[bookingCount - 1].startDate);

            printf("End Date     : %s\n",
                   bookings[bookingCount - 1].endDate);

            printf("Total Charge : %.2f\n",
                   bookings[bookingCount - 1].charge);

            printf("Payment      : Pending\n");
            printf("Vehicle Status: Rented\n");

            return;
        }
    }

    printf("\nVehicle ID not found!\n");
}


// =====================================================
// RENTAL CHARGES
// =====================================================

void rentalCharges()
{
    if (bookingCount == 0)
    {
        printf("\nNo Booking Found!\n");
        return;
    }

    printf("\n========================================\n");
    printf("             RENTAL CHARGES\n");
    printf("========================================\n");

    for (int i = 0; i < bookingCount; i++)
    {
        printf("\n----------------------------------------\n");

        printf("Vehicle : %s\n",
               bookings[i].vehicle);

        if (bookings[i].rentalType == 1)
        {
            printf("Type    : Per Hour\n");
            printf("Hours   : %d\n",
                   bookings[i].hours);
        }
        else
        {
            printf("Type    : Per Day\n");
            printf("Days    : %d\n",
                   bookings[i].days);
        }

        printf("Charge  : %.2f\n",
               bookings[i].charge);

        printf("Payment : %s\n",
               bookings[i].paymentStatus);
    }
}


// =====================================================
// MAKE PAYMENT
// =====================================================

void makePayment()
{
    int choice;

    char mobile[20];
    char cardNumber[30];
    char transactionID[30];

    if (bookingCount == 0)
    {
        printf("\nNo Booking Found!\n");
        return;
    }

    int last = bookingCount - 1;

    if (strcmp(bookings[last].paymentStatus, "Paid") == 0)
    {
        printf("\nPayment has already been completed.\n");
        return;
    }

    printf("\n========================================\n");
    printf("              MAKE PAYMENT\n");
    printf("========================================\n");

    printf("Vehicle : %s\n",
           bookings[last].vehicle);

    printf("Amount  : %.2f\n",
           bookings[last].charge);

    printf("\nSelect Payment Method:\n");

    printf("1. bKash\n");
    printf("2. Nagad\n");
    printf("3. Visa Card\n");
    printf("4. Cash\n");

    printf("\nChoice: ");
    scanf("%d", &choice);


    // =========================================
    // BKASH
    // =========================================

    if (choice == 1)
    {
        printf("\n========================================\n");
        printf("              bKASH PAYMENT\n");
        printf("========================================\n");

        printf("Enter bKash Number: ");
        scanf("%s", mobile);

        printf("Enter Transaction ID: ");
        scanf("%s", transactionID);

        strcpy(bookings[last].paymentMethod,
               "bKash");

        strcpy(bookings[last].transactionID,
               transactionID);

        strcpy(bookings[last].paymentStatus,
               "Paid");

        printf("\nPayment Successful through bKash!\n");
    }


    // =========================================
    // NAGAD
    // =========================================

    else if (choice == 2)
    {
        printf("\n========================================\n");
        printf("              NAGAD PAYMENT\n");
        printf("========================================\n");

        printf("Enter Nagad Number: ");
        scanf("%s", mobile);

        printf("Enter Transaction ID: ");
        scanf("%s", transactionID);

        strcpy(bookings[last].paymentMethod,
               "Nagad");

        strcpy(bookings[last].transactionID,
               transactionID);

        strcpy(bookings[last].paymentStatus,
               "Paid");

        printf("\nPayment Successful through Nagad!\n");
    }


    // =========================================
    // VISA CARD
    // =========================================

    else if (choice == 3)
    {
        printf("\n========================================\n");
        printf("             VISA CARD PAYMENT\n");
        printf("========================================\n");

        printf("Enter Visa Card Number: ");
        scanf("%s", cardNumber);

        printf("Enter Transaction ID: ");
        scanf("%s", transactionID);

        strcpy(bookings[last].paymentMethod,
               "Visa Card");

        strcpy(bookings[last].transactionID,
               transactionID);

        strcpy(bookings[last].paymentStatus,
               "Paid");

        printf("\nPayment Successful through Visa Card!\n");
    }


    // =========================================
    // CASH
    // =========================================

    else if (choice == 4)
    {
        printf("\n========================================\n");
        printf("               CASH PAYMENT\n");
        printf("========================================\n");

        printf("Please pay %.2f in cash.\n",
               bookings[last].charge);

        printf("Enter Cash Receipt ID: ");
        scanf("%s", transactionID);

        strcpy(bookings[last].paymentMethod,
               "Cash");

        strcpy(bookings[last].transactionID,
               transactionID);

        strcpy(bookings[last].paymentStatus,
               "Paid");

        printf("\nCash Payment Successful!\n");
    }


    else
    {
        printf("\nInvalid Payment Method!\n");
        return;
    }


    // =========================================
    // PAYMENT RECEIPT
    // =========================================

    printf("\n========================================\n");
    printf("             PAYMENT RECEIPT\n");
    printf("========================================\n");

    printf("Vehicle        : %s\n",
           bookings[last].vehicle);

    printf("Amount         : %.2f\n",
           bookings[last].charge);

    printf("Payment Method : %s\n",
           bookings[last].paymentMethod);

    printf("Transaction ID : %s\n",
           bookings[last].transactionID);

    printf("Payment Status : %s\n",
           bookings[last].paymentStatus);

    printf("========================================\n");
}


// =====================================================
// RENTAL HISTORY
// =====================================================

void rentalHistory()
{
    if (bookingCount == 0)
    {
        printf("\nNo Rental History Found!\n");
        return;
    }

    printf("\n========================================\n");
    printf("              RENTAL HISTORY\n");
    printf("========================================\n");

    for (int i = 0; i < bookingCount; i++)
    {
        printf("\n----------------------------------------\n");

        printf("Vehicle        : %s\n",
               bookings[i].vehicle);

        if (bookings[i].rentalType == 1)
        {
            printf("Rental Type    : Per Hour\n");
            printf("Hours          : %d\n",
                   bookings[i].hours);
        }
        else
        {
            printf("Rental Type    : Per Day\n");
            printf("Days           : %d\n",
                   bookings[i].days);
        }

        printf("Start Date     : %s\n",
               bookings[i].startDate);

        printf("End Date       : %s\n",
               bookings[i].endDate);

        printf("Charge         : %.2f\n",
               bookings[i].charge);

        printf("Payment Method : %s\n",
               bookings[i].paymentMethod);

        printf("Transaction ID : %s\n",
               bookings[i].transactionID);

        printf("Payment Status : %s\n",
               bookings[i].paymentStatus);
    }
}


// =====================================================
// ADMIN LOGIN
// =====================================================

void adminLogin()
{
    char user[20];
    char pass[20];

    printf("\n========================================\n");
    printf("          ADMINISTRATOR LOGIN\n");
    printf("========================================\n");

    printf("Username: ");
    scanf("%s", user);

    printf("Password: ");
    scanf("%s", pass);

    if (strcmp(user, "admin") == 0 &&
        strcmp(pass, "admin1234") == 0)
    {
        printf("\nAdmin Login Successful!\n");

        adminMenu();
    }
    else
    {
        printf("\nInvalid Admin Login!\n");
    }
}


// =====================================================
// ADMIN MENU
// =====================================================

void adminMenu()
{
    int choice;

    do
    {
        printf("\n========================================\n");
        printf("          ADMINISTRATOR MENU\n");
        printf("========================================\n");

        printf("1. Track Vehicle Availability\n");
        printf("2. Update Vehicle Information\n");
        printf("3. Generate Rental Reports\n");
        printf("4. Logout\n");

        printf("\nChoice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                trackAvailability();
                break;

            case 2:
                updateVehicle();
                break;

            case 3:
                generateReports();
                break;

            case 4:
                printf("\nAdmin Logged Out Successfully!\n");
                break;

            default:
                printf("\nInvalid Choice!\n");
        }

    } while (choice != 4);
}


// =====================================================
// TRACK VEHICLE AVAILABILITY
// =====================================================

void trackAvailability()
{
    printf("\n========================================\n");
    printf("          VEHICLE AVAILABILITY\n");
    printf("========================================\n");

    for (int i = 0; i < VEHICLE_COUNT; i++)
    {
        printf("\n----------------------------------------\n");

        printf("ID     : %d\n",
               vehicles[i].id);

        printf("Type   : %s\n",
               vehicles[i].type);

        printf("Model  : %s\n",
               vehicles[i].model);

        printf("Rate   : %.2f per day\n",
               vehicles[i].rate);

        printf("Hourly : %.2f per hour\n",
               vehicles[i].rate / 8);

        printf("Status : %s\n",
               vehicles[i].status);
    }
}


// =====================================================
// UPDATE VEHICLE INFORMATION
// =====================================================

void updateVehicle()
{
    int id;
    int choice;

    printf("\n========================================\n");
    printf("        UPDATE VEHICLE INFORMATION\n");
    printf("========================================\n");

    printf("Enter Vehicle ID: ");
    scanf("%d", &id);

    int found = -1;

    for (int i = 0; i < VEHICLE_COUNT; i++)
    {
        if (vehicles[i].id == id)
        {
            found = i;
            break;
        }
    }

    if (found == -1)
    {
        printf("\nVehicle ID not found!\n");
        return;
    }

    do
    {
        printf("\n----------------------------------------\n");

        printf("Vehicle ID     : %d\n",
               vehicles[found].id);

        printf("Vehicle Type   : %s\n",
               vehicles[found].type);

        printf("Vehicle Model  : %s\n",
               vehicles[found].model);

        printf("Daily Rate     : %.2f\n",
               vehicles[found].rate);

        printf("Hourly Rate    : %.2f\n",
               vehicles[found].rate / 8);

        printf("Vehicle Status : %s\n",
               vehicles[found].status);

        printf("----------------------------------------\n");

        printf("\nWhat do you want to update?\n");

        printf("1. Vehicle Type\n");
        printf("2. Vehicle Model\n");
        printf("3. Rental Rate\n");
        printf("4. Vehicle Status\n");
        printf("5. Update All Information\n");
        printf("6. Back\n");

        printf("\nChoice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:

                printf("\nEnter New Vehicle Type: ");
                scanf(" %[^\n]", vehicles[found].type);

                printf("\nVehicle Type Updated Successfully!\n");

                break;


            case 2:

                printf("\nEnter New Vehicle Model: ");
                scanf(" %[^\n]", vehicles[found].model);

                printf("\nVehicle Model Updated Successfully!\n");

                break;


            case 3:

                printf("\nEnter New Daily Rental Rate: ");
                scanf("%f", &vehicles[found].rate);

                if (vehicles[found].rate < 0)
                {
                    printf("\nInvalid Rate!\n");
                }
                else
                {
                    printf("\nRental Rate Updated Successfully!\n");
                    printf("Hourly Rate is now: %.2f\n",
                           vehicles[found].rate / 8);
                }

                break;


            case 4:

                printf("\nSelect New Status:\n");

                printf("1. Available\n");
                printf("2. Rented\n");
                printf("3. Under Maintenance\n");

                printf("\nChoice: ");
                scanf("%d", &choice);

                if (choice == 1)
                {
                    strcpy(vehicles[found].status,
                           "Available");

                    printf("\nStatus Updated to Available!\n");
                }
                else if (choice == 2)
                {
                    strcpy(vehicles[found].status,
                           "Rented");

                    printf("\nStatus Updated to Rented!\n");
                }
                else if (choice == 3)
                {
                    strcpy(vehicles[found].status,
                           "Under Maintenance");

                    printf("\nStatus Updated to Under Maintenance!\n");
                }
                else
                {
                    printf("\nInvalid Status Choice!\n");
                }

                break;


            case 5:

                printf("\nEnter New Vehicle Type: ");
                scanf(" %[^\n]", vehicles[found].type);

                printf("Enter New Vehicle Model: ");
                scanf(" %[^\n]", vehicles[found].model);

                printf("Enter New Daily Rental Rate: ");
                scanf("%f", &vehicles[found].rate);

                if (vehicles[found].rate < 0)
                {
                    printf("\nInvalid Rate!\n");
                    break;
                }

                printf("\nSelect New Status:\n");

                printf("1. Available\n");
                printf("2. Rented\n");
                printf("3. Under Maintenance\n");

                printf("Choice: ");
                scanf("%d", &choice);

                if (choice == 1)
                {
                    strcpy(vehicles[found].status,
                           "Available");
                }
                else if (choice == 2)
                {
                    strcpy(vehicles[found].status,
                           "Rented");
                }
                else if (choice == 3)
                {
                    strcpy(vehicles[found].status,
                           "Under Maintenance");
                }
                else
                {
                    printf("\nInvalid Status!\n");
                    break;
                }

                printf("\nAll Vehicle Information Updated Successfully!\n");

                break;


            case 6:

                printf("\nReturning to Admin Menu...\n");

                break;


            default:

                printf("\nInvalid Choice!\n");
        }

    } while (choice != 6);
}


// =====================================================
// GENERATE RENTAL REPORTS
// =====================================================

void generateReports()
{
    float totalRevenue = 0;

    printf("\n========================================\n");
    printf("             RENTAL REPORT\n");
    printf("========================================\n");

    if (bookingCount == 0)
    {
        printf("\nNo rental records found.\n");
    }
    else
    {
        for (int i = 0; i < bookingCount; i++)
        {
            printf("\n----------------------------------------\n");

            printf("Vehicle        : %s\n",
                   bookings[i].vehicle);

            if (bookings[i].rentalType == 1)
            {
                printf("Rental Type    : Per Hour\n");
                printf("Hours          : %d\n",
                       bookings[i].hours);
            }
            else
            {
                printf("Rental Type    : Per Day\n");
                printf("Days           : %d\n",
                       bookings[i].days);
            }

            printf("Start Date     : %s\n",
                   bookings[i].startDate);

            printf("End Date       : %s\n",
                   bookings[i].endDate);

            printf("Charge         : %.2f\n",
                   bookings[i].charge);

            printf("Payment Method : %s\n",
                   bookings[i].paymentMethod);

            printf("Transaction ID : %s\n",
                   bookings[i].transactionID);

            printf("Payment Status : %s\n",
                   bookings[i].paymentStatus);

            if (strcmp(bookings[i].paymentStatus, "Paid") == 0)
            {
                totalRevenue += bookings[i].charge;
            }
        }
    }

    printf("\n========================================\n");
    printf("Total Paid Revenue: %.2f\n",
           totalRevenue);

    printf("========================================\n");
}


// =====================================================
// MAIN MENU
// =====================================================

void mainMenu()
{
    int choice;

    do
    {
        printf("\n========================================\n");
        printf("         VEHICLE RENTAL SYSTEM\n");
        printf("========================================\n");

        printf("1. Customer Registration\n");
        printf("2. Customer Login\n");
        printf("3. Forgot Password\n");
        printf("4. Administrator Login\n");
        printf("5. Exit\n");

        printf("\nChoice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                customerRegistration();
                break;

            case 2:
                customerLogin();
                break;

            case 3:
                forgotPassword();
                break;

            case 4:
                adminLogin();
                break;

            case 5:
                printf("\nSystem Closed. Thank You!\n");
                break;

            default:
                printf("\nInvalid Choice!\n");
        }

    } while (choice != 5);
}


// =====================================================
// MAIN FUNCTION
// =====================================================

int main()
{
    mainMenu();

    return 0;
}
