#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Global file pointer declare kiya hai
FILE *file;

// Function declarations
void main_menu();
void sub_menu();

// Account struct banaya hai jisme user ka data store hoga
typedef struct {
    char fname[25];            // First name
    char lname[25];            // Last name
    long int Adhar;            // Aadhaar number
    long int phone;            // Phone number
    char account_no[20];       // Account number
    char password[10];         // Account password
    char check_password[10];   // Password confirm karne ke liye
} account;
account new;

// Money struct banaya hai jisme account balance, deposit aur withdraw amounts store honge
typedef struct {
    long long int balance;     // Account balance
    long long int deposit;     // Deposit amount
    long long int withdraw;    // Withdraw amount
} money;
money transaction;

// Function declarations
void create_account();
void user_login();
void deposit_money();
void withdraw_money();
void check_balance();
void transfer_money();
void delete_account();

int main() {
    main_menu(); // Main menu function ko call kiya hai
    return 0;
}

// Main menu function hai jisme user login, account creation, aur exit ke options hain
void main_menu() {
    int n;
start:
    printf("\n\n------------------Login-------------------- \n");
    printf("-------------------------------------------\n\n");

    printf("1. User login \n");
    printf("2. Create a new Account \n");
    printf("3. Exit \n\n");

    // User se choice input lene ka system
    printf("Enter your Choice :");
    scanf("%d", &n);

    switch (n) {
        case 1:
            user_login(); // User login function ko call kiya
            break;
        case 2:
            create_account(); // Account creation function ko call kiya
            break;
        case 3:
            printf("Thanks for visiting........\n");
            break;
        default:
            printf("Invalid input!\n Please enter a valid input..........");
            goto start; // Agar input galat hai to dubara input mangta hai
            break;
    }
}

// Submenu function jisme user different banking actions kar sakta hai
void sub_menu() {
    int n;
    printf("\n\n--------------------------Welcome to Atul Bank------------------------ \n");
    printf("----------------------------------------------------------------------\n\n");
start:
    printf("1. Deposit Money \n");
    printf("2. Withdraw Money \n");
    printf("3. Check Balance\n");
    printf("4. Transfer Money\n");
    printf("5. Delete your account\n");
    printf("6. Exit\n");
    printf("Enter your Choice :");
    scanf("%d", &n);
    switch (n) {
        case 1:
            deposit_money(); // Deposit money function ko call kiya
            goto start;
            break;
        case 2:
            withdraw_money(); // Withdraw money function ko call kiya
            goto start;
            break;
        case 3:
            check_balance(); // Check balance function ko call kiya
            goto start;
            break;
        case 4:
            transfer_money(); // Transfer money function ko call kiya
            goto start;
            break;
        case 5:
            delete_account(); // Account delete karne ka function call kiya
            break;
        case 6:
            printf("Thanks for visiting..........\n");
            break;
        default:
            printf("Invalid input.......\n Please enter a valid input\n");
            goto start; // Invalid input case me dubara input mangta hai
            break;
    }
}

// Account creation ka function
void create_account() {
start:
    printf("\n\n------------Create a new account----------  \n");
    printf("-------------------------------------------\n\n");

    // User se details input karayi ja rahi hain
    printf("Enter your First Name : ");
    scanf("%s", new.fname);
    printf("Enter your Last Name : ");
    scanf("%s", new.lname);
    printf("Enter your Aadhaar number : ");
    scanf("%ld", &new.Adhar);
    printf("Enter your Phone number : ");
    scanf("%ld", &new.phone);
    printf("Enter your 6 digit password : ");
    scanf("%s", new.password);
    printf("Confirm your 6 digit password : ");
    scanf("%s", new.check_password);

    // Password aur confirm password match kar rahe hain ya nahi, yeh check kiya ja raha hai
    if (strcmp(new.password, new.check_password) == 0) {
        // Account number generate kiya ja raha hai
        char acc[20] = "320810100";
        char end[10];
        srand(time(0));  // Random number generate karne ke liye seed set karte hain
        int random_number = (rand() % 9000) + 1000; // 1000-9999 ke beech me random number generate hota hai
        sprintf(end, "%d", random_number); // Random number ko string me convert karte hain
        strcpy(new.account_no, strcat(acc, end)); // Account number ko create karte hain

        // Account ka data file me save karne ke liye filename set kar rahe hain
        char filename[30];
        strcpy(filename, new.account_no);
        strcat(filename, ".dat");

        FILE *file = fopen(filename, "wb"); // Account data store karne ke liye file open karte hain
        if (file == NULL) {
            printf("Error creating file!...............\n");
            exit(1);
        } else {
            transaction.balance = 0; // Initial balance set kar rahe hain
            fwrite(&new, sizeof(account), 1, file); // Account details ko file me write karte hain
            fwrite(&transaction, sizeof(money), 1, file); // Initial balance ko file me write karte hain
        }

        printf("Your Account no is : %s\n", new.account_no); // Account number print karte hain
        printf("Your Balance is %lld.\n", transaction.balance); // Initial balance print karte hain
        fclose(file); // File close karte hain
    } else {
        printf("Passwords do not match.......\n");
        goto start; // Agar password match nahi karte to dubara input mangte hain
    }
}

// User login ka function
void user_login() {
    char acc[20];
    char pwd[7];
    printf("Enter your account no :");
    scanf("%s", acc);
    printf("Enter your 6 digit password:");
    scanf("%s", pwd);
    strcat(acc, ".dat"); // Account number ko filename banane ke liye '.dat' add karte hain

    file = fopen(acc, "rb+"); // Account file ko read-write mode me open karte hain
    if (file == NULL) {
        printf("Sorry Your Account not found!\n");
        exit(1);
    } else {
        fread(&new, sizeof(account), 1, file); // Account details ko file se read karte hain
        fread(&transaction, sizeof(money), 1, file); // Transaction details ko file se read karte hain
    }
    if ((strcmp(pwd, new.password)) == 0) { // Password match check karte hain
        printf("Welcome to our Bank Management System...\n  %s Ji\n", new.fname, new.lname);
        printf("Adhar No is : %ld\n", new.Adhar);
        printf("Phone No is : %ld\n", new.phone);

        sub_menu(); // Submenu ko call karte hain agar login successful ho jaye
    } else {
        printf("Passwords do not match.......\n");
        fclose(file);
        user_login(); // Password match nahi hota to login dubara karne ke liye
    }
}

// Money deposit karne ka function
void deposit_money() {
    printf("Please Enter Deposit Amount :");
    scanf("%lld", &transaction.deposit); // Deposit amount input lete hain
    fwrite(&transaction, sizeof(money), 1, file); // Deposit amount file me write karte hain
    transaction.balance = transaction.balance + transaction.deposit; // Balance update karte hain
    fseek(file, sizeof(account), SEEK_SET); 
    /* 
    fseek() ka use file pointer ko kisi specific location par move karne ke liye kiya jata hai. 
    Yahan, account structure ke size ke barabar move kar rahe hain taki money structure par pahunch sakein.
    */
    fwrite(&transaction, sizeof(money), 1, file); // Updated balance ko file me write karte hain
    printf("Deposit Successful. Your New Balance is: %lld\n", transaction.balance);
}

// Money withdraw karne ka function
void withdraw_money() {
    printf("Please Enter Withdraw Amount :");
    scanf("%lld", &transaction.withdraw); // Withdraw amount input lete hain
    if (transaction.balance >= transaction.withdraw) { // Check karte hain balance sufficient hai ya nahi
        fwrite(&transaction, sizeof(money), 1, file); // Withdraw amount file me write karte hain
        transaction.balance = transaction.balance - transaction.withdraw; // Balance update karte hain
        fseek(file, sizeof(account), SEEK_SET); 
        /*
        fseek() se file pointer ko move karke money structure ke beginning par set karte hain
        takki updated balance ko waha par save kar sakein.
        */
        fwrite(&transaction, sizeof(money), 1, file); // Updated balance ko file me write karte hain
        printf("Money Withdraw Successful. \n Your New Balance is: %lld\n", transaction.balance);
    } else {
        printf("\nInsufficient Balance!..............\n"); // Agar balance sufficient nahi hai to message print karte hain
    }
}

// Balance check karne ka function
void check_balance() {
    printf("Your Current Balance is: %lld\n", transaction.balance); // Current balance print karte hain
}

// Money transfer karne ka function
void transfer_money() {
start:
    char recipient_acc[20];
    long long int transfer_amount;
    FILE *recipient_file;

    printf("Enter recipient account number: ");
    scanf("%s", recipient_acc);
    strcat(recipient_acc, ".dat"); // Recipient account number ko filename banate hain

    recipient_file = fopen(recipient_acc, "rb+"); // Recipient account file ko open karte hain
    if (recipient_file == NULL) {
        printf("Recipient account not found.\n");
        goto start; // Agar file nahi milti to dubara input mangte hain
    } else {
        printf("Enter amount to transfer: ");
        scanf("%lld", &transfer_amount); // Transfer amount input lete hain

        if (transaction.balance >= transfer_amount) { // Check karte hain balance sufficient hai ya nahi
            transaction.balance = transaction.balance - transfer_amount; // Sender ka balance update karte hain
            fseek(file, sizeof(account), SEEK_SET);
            /*
            fseek() se file pointer ko money structure ke beginning par move karte hain
            taa ki updated balance ko save kar sakein.
            */
            fwrite(&transaction, sizeof(money), 1, file); // Sender ke updated balance ko file me write karte hain

            // Recipient ka transaction read karte hain
            money recipient_transaction;
            fread(&recipient_transaction, sizeof(money), 1, recipient_file);

            // Recipient ka balance update karte hain
            recipient_transaction.balance += transfer_amount;
            fseek(recipient_file, sizeof(account), SEEK_SET);
            fwrite(&recipient_transaction, sizeof(money), 1, recipient_file); // Recipient ka updated balance save karte hain

            printf("Transfer Successful. Your New Balance is: %lld\n", transaction.balance);
        } else {
            printf("Insufficient balance for the transfer.\n"); // Agar balance sufficient nahi hai to message print karte hain
        }
        fclose(recipient_file); // Recipient file ko close karte hain
    }
}

// Account delete karne ka function
void delete_account() {
    char confirm;
    char filename[30];

    printf("Are you sure you want to delete your account? (y/n): ");
    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y') {
        strcpy(filename, new.account_no);
        strcat(filename, ".dat");

        fclose(file); // File ko close karte hain

        // File ko delete karte hain
        if (remove(filename) == 0) {
            printf("Account deleted successfully.\n");
        } else {
            printf("Error deleting account.\n"); // Agar account delete nahi hota to error message print karte hain
        }

        exit(0); // Program ko terminate karte hain
    } else {
        printf("Account deletion canceled.\n");
        sub_menu(); // Agar user delete nahi karna chahta to submenu me wapas le jate hain
    }
}
