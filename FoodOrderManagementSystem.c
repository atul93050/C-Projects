#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
FILE *file;
typedef struct
{
    char username[50];
    char email[50];
    char phone[15];
    char userid[12];
    char password[12];
} user;
user userdetail;

typedef struct
{
    char username[50];
    char password[12];
} admin;
admin admindetail;

typedef struct
{
    int itemId;
    char itemName[50];
    double price;
    char availability[3];
} foodItem;
foodItem food;

void main_menu();
void signUp();
void login();
void resetPassword();
void adminLogin();
void adminmenu();
void addFoodItem();
void editFoodItem();
void deleteFoodItem();
void displayMenu();
int main()
{
    adminRegister();
    int n;
start:
    printf("-----------Welcome to Food Managemet System-----------");
    printf("1. Admin Login\n");
    printf("2. User Login\n");
    printf("3. Exit");
    printf("Please Enter your choice: ");
    scanf("%d", &n);
    switch (n)
    {
    case 1:
        adminLogin();
        break;
    case 2:
        main_menu();
        break;
    case 3:
        printf("Thanks for visiting-----");
        break;
    default:
        printf("Please Enter a valid choice : ");
        goto start;
        break;
    }
    return 0;
}

void main_menu()
{
    int n;
start:
    printf("---------------Food Management System---------------\n");
    
    printf("1. Sign Up\n");
    printf("2. Login\n");
    printf("3. Reset Password\n");
    printf("4. Exit \n");
    printf("Please Enter your choice: ");
    scanf("%d", &n);

    // Clear input buffer after scanf

    while (getchar() != '\n')
        ;

    switch (n)
    {
   
    case 1:
        signUp();
        break;
    case 2:
        login();
        break;
    case 3:
        resetPassword();
        break;
    case 4:
        printf("Exiting...\n");
        break;
    default:
        printf("Please enter a valid choice!\n");
        goto start;
    }
}

void signUp()
{
    char name[100];
    char pwd[15];
start:
    printf("-------Sign Up here----------\n");
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; // Remove the newline character
    strcpy(userdetail.username, name);
    printf("Enter your email id: ");
    scanf("%s", userdetail.email);
    printf("Enter your Mobile number: ");
    scanf("%s", userdetail.phone);
    printf("Enter your password: ");
    scanf("%s", userdetail.password);
    printf("Confirm your password :");
    scanf("%s", pwd);
    if (strcmp(userdetail.password, pwd) == 0)
    {

        char id[20] = "3208";
        char end[10];

        srand(time(0));                             // Random number generate karne ke liye seed set karte hain
        int random_number = (rand() % 9000) + 1000; // 1000-9999 ke beech me random number generate hota hai
        sprintf(end, "%d", random_number);          // Random number ko string me convert karte hain
        strcpy(userdetail.userid, strcat(id, end));
        char filename[30];
        strcpy(filename, userdetail.userid);
        strcat(filename, ".dat");

        file = fopen(filename, "wb");
        if (file == NULL)
        {
            printf("Error creating file!...............\n");
            exit(1);
        }
        else
        {

            fwrite(&userdetail, sizeof(user), 1, file);
        }

        printf("Your UserId is : %s\n", userdetail.userid);
        printf("Your registeration is succesful");
        fclose(file);
        // Clear input buffer
        while (getchar() != '\n')
            ;
    }
    else
    {
        printf("Password do not match !!\n\n");
        goto start;
    }
}

void login()
{
    char id[20];
    char pass[15];
    char cpass[15];
start:
    printf("-------Login here----------\n");
    printf("Enter your userid :");
    scanf("%s", id);
    printf("Enter your password:");
    scanf("%s", pass);

    strcat(id, ".dat");
    file = fopen(id, "rb+");
    if (file == NULL)
    {
        printf("Sorry Your Account not found!\n");
        exit(1);
    }
    else
    {
        fread(&userdetail, sizeof(user), 1, file);
        if (strcmp(userdetail.password, pass) == 0)
        {
            printf("Welcome to food management system\n");
            printf("Hello %s", userdetail.username);
        }
        else
        {
            printf("Password do not match !!\n\n");
            goto start;
        }
    }
}

void resetPassword()
{
    char name[50];
    char id[10];
    char email[50];
    char phone[50];
    char pass[15];
    char cpass[15];
    printf("-------Reset Password here----------\n");
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; // Remove the newline character
    printf("Enter your userid ");
    scanf("%s", id);
    printf("Enter your email");
    scanf("%s", email);
    printf("Enter your phone no.");
    scanf("%s", phone);
    printf("Enter your new password");
    scanf("%s", pass);
    printf("Confirm your password");
    scanf("%s", cpass);
    if (strcmp(pass, cpass) == 0)
    {
        strcat(id, ".dat");
        file = fopen(id, "rb+");
        if (file == NULL)
        {
            printf("Sorry Your Account not found!\n");
            exit(1);
        }
        else
        {
            fread(&userdetail, sizeof(user), 1, file);
            if (strcmp(userdetail.email, email) == 0 && strcmp(userdetail.phone, phone) == 0)
            {
                strcpy(userdetail.password, pass);

                fseek(file, 0, SEEK_SET);

                fwrite(&userdetail, sizeof(user), 1, file);
                printf("Your password reset successfully!!\n");
                login();
            }
            else
            {
                printf("Your details do not matched\n");
            }
        }
    }
}

void addFoodItem()
{
    char foodname[50];
    printf("Add Food Items \n");
    printf("Enter item id: ");
    scanf("%d", &food.itemId);

    while (getchar() != '\n')
        ;

    printf("Enter Food Name: ");
    fgets(foodname, sizeof(foodname), stdin);
    foodname[strcspn(foodname, "\n")] = 0;
    strcpy(food.itemName, foodname);
    printf("Enter food price :");
    scanf("%lf", &food.price);
    printf("Enter food availibility:(y/n)");
    scanf("%c", &food.availability);

    file = fopen("foodItem.dat", "ab");
    if (file == NULL)
    {
        printf("Error to file opening");
        exit(1);
    }
    else
    {
        fwrite(&food, sizeof(foodItem), 1, file);
        printf("Food item added successfully!\n");
        fclose(file);
    }
}
void editFoodItem()
{
    int id;
    char newName[50];
    double newPrice;
    char newAvailability[3];
    printf("Enter food id : ");
    scanf("%d", &id);

    file = fopen("foodItem.dat", "rb+");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    else
    {

        while (fread(&food, sizeof(foodItem), 1, file))
        {
            if (food.itemId == id)
            {

                printf("Editing Food Item ID %d:\n", id);
                printf("Enter new food name : ");
                while (getchar() != '\n')
                    ;

                fgets(newName, sizeof(newName), stdin);
                newName[strcspn(newName, "\n")] = 0;
                strcpy(food.itemName, newName);
                printf("Enter new price ");
                scanf("%lf", &newPrice);
                food.price = newPrice;

                while (getchar() != '\n')
                    ; // Clear input buffer

                printf("Enter food is available or not (y/n)");

                scanf("%s", &newAvailability);

                strcpy(food.availability, newAvailability);

                fseek(file, -sizeof(foodItem), SEEK_CUR);
                fwrite(&food, sizeof(foodItem), 1, file);
                printf("Food item updated successfully!\n");
            }
            else
            {
                printf("Food item not found!!");
            }
        }
    }

    fclose(file);
}

void displayMenu()
{
    file = fopen("foodItem.dat", "rb+");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    printf("------------------------------------------------------\n");
    printf("|    ID    |   Food Name  |  Price  | Availability  |\n");
    printf("------------------------------------------------------\n");

    while (fread(&food, sizeof(foodItem), 1, file))
    {
        printf("|   %-7d|   %-10s|  %-6.2lf|    %c|\n", food.itemId, food.itemName, food.price, food.availability);
    }

    printf("------------------------------------------------------\n");
    fclose(file);
}
void adminRegister()
{
    char username[50] = "admin", password[12] = "1234";

    strcpy(admindetail.username, username);
    strcpy(admindetail.password, password);

    file = fopen("admin.dat", "wb");
    if (file == NULL)
    {
        printf("Error in file openning!!");
        exit(1);
    }
    else
    {
        fwrite(&admindetail, sizeof(admin), 1, file);
        fclose(file);
    }
}

void adminLogin()
{
    char adminId[50], adminPass[12];
    printf("Enter your Admin ID: ");
    scanf("%s", adminId);
    printf("Enter your password: ");
    scanf("%s", adminPass);

    file = fopen("admin.dat", "rb");
    if (file == NULL)
    {
        printf("Admin credentials file not found!\n");
        exit(1);
    }
    else
    {
        fread(&admindetail, sizeof(admin), 1, file);
        if (strcmp(admindetail.username, adminId) == 0 && strcmp(admindetail.password, adminPass) == 0)
        {
            printf("Admin login successful!\n");
            adminmenu();
        }
        else
        {
            printf("Invalid Admin ID or Password!\n");
        }
        fclose(file);
    }
}
void adminmenu(){
    int n;

    printf("Welcome to admin Zone-----\n\n");
    printf("1. Display Menu\n");
    printf("2. Add a food item\n");
    printf("3. Edit a food item\n");
    printf("4. Delete a food item\n");
    printf("5. exit\n");
    printf("Choose any option : ");
    scanf("%d",&n);

    switch(n){
        case 1:
        displayMenu();
        break;
        case 2:
        addFoodItem();
        break;
        case 3:
        editFoodItem();
        break;
        case 4:
        deleteFoodItem();
        break;
        default:
        printf("Please enter a valid choice ");
        break;

    }
}
void deleteFoodItem(){
    printf("Deleted success fully");
}
