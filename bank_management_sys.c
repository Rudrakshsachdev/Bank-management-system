#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define name_length 1000
#define max_customers 1000

// Program for Bank_management_system!
typedef struct
{
    int Account_num;
    char name[name_length];
    float Account_bal;
} customer;

customer customers[max_customers]; // Declared a global array to store the customer records!
int count_customers = 0;

void login();
void add_customers();
void remove_customers(); // declaring functions for various kind of tasks!
void update_customers();
void view_customers();
void deposit_cash();
void withdraw_cash();
void load_customers();
void save_customers();

int main()
{
    int choice = 0;

    load_customers();

    login(); // calling the login function!

    printf("\nBank Management System\n");
    printf("1. Add Customer\n");
    printf("2. Remove Customer\n");
    printf("3. Update Customer\n"); // displaying a menu based system!
    printf("4. View Customer details\n");
    printf("5. Deposit Cash\n");
    printf("6. Withdraw Cash\n");
    printf("7. Exit\n");

    printf("Enter your choice:\n");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        add_customers();
        break;

    case 2:
        remove_customers();
        break;

    case 3:
        update_customers();
        break;

    case 4:
        view_customers();
        break;

    case 5:
        deposit_cash();
        break;

    case 6:
        withdraw_cash();
        break;

    case 7:
        printf("Exiting system!\n");
        exit(0);

    default:
        printf("Invalid choice! Please try again!\n");
    }

    save_customers();
    return 0;
}

void login()
{
    char username[50], password[50];
    char correct_username[] = "Admin";
    char correct_pass[] = "Password_x";

    printf("Input the Username:\n");
    scanf(" %[^\n]s", &username);

    printf("Input the Password:\n");
    scanf(" %[^\n]s", &password);

    if ((strcmp(correct_username, username) == 0) && (strcmp(correct_pass, password) == 0))
    {
        printf("Login Successfull!You've logged into the portal!\n");
    }
    else
    {
        printf("Invalid Username or Password!\n");
        exit(0);
    }
}

void add_customers()
{
    if (count_customers >= max_customers)
    {
        printf("Customers limit reached!Cannot add more customers");
    }

    customer new_customer;
    printf("Input the Account Number of the customer:\n");
    scanf("%d", &new_customer.Account_num);

    printf("Input the Name of the customer:\n");
    scanf(" %[^\n]s", &new_customer.name);

    new_customer.Account_bal = 0.0;
    customers[count_customers++] = new_customer;
    printf("Congratualations!Customer Added Successfully!\n");
}

void remove_customers()
{
    int account_num, found = 0;
    int i, j;

    printf("Input the Account number to remove:\n");
    scanf("%d", &account_num);

    for (i = 0; i < count_customers; i++)
    {
        if (customers[i].Account_num == account_num)
        {
            for (j = 1; j < count_customers - 1; j++)
            {
                customers[j] = customers[j + 1]; // if the element is found than shifting it to left side for removing!
            }
            count_customers--; // decrementing the size of customer_count by 1, as the element is removed!
            printf("Customer removed successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("Account Number doesnot exist!\n");
    }
}

void update_customers()
{
    int account_num, found = 0;
    int i, j;

    printf("Input the Account Number to update:\n");
    scanf("%d", &account_num);

    for (i = 0; i < count_customers; i++)
    {
        if (customers[i].Account_num == account_num)
        {
            printf("Input New Name of the Customer:\n");
            scanf(" %[^\n]s", customers[i].name);

            found = 1;
            printf("Customer Details Updated Successfully!\n");
            break;
        }
    }

    if (!found)
    {
        printf("Account number doesnot exist!\n");
    }
}

void view_customers()
{
    if (count_customers == 0)
    {
        printf("No customers are avalaible!\n");
    }

    printf("\nCustomer Details:\n");
    printf("Account Number\tName of Customer\tBank Balance\n");

    for (int i = 0; i < count_customers; i++)
    {
        printf("%d\t         %s\t           %f\n", customers[i].Account_num, customers[i].name, customers[i].Account_bal);
    }
}

void deposit_cash()
{
    int account_num;
    float cash;

    printf("Input the Account Number:\n");
    scanf("%d", &account_num);

    for (int i = 0; i < count_customers; i++)
    {
        if (customers[i].Account_num == account_num)
        {
            printf("Input the amount you want to Add in your Account:\n");
            scanf("%f", &cash);

            customers[i].Account_bal += cash; // Here, adding up the deposited cash into account balance!

            printf("%f amount deposited into your Account linked with Account Number %d\n", cash, account_num);
            return;
        }
    }
    printf("Account not found!\n");
}

void withdraw_cash()
{
    int account_num;
    float amount;
    printf("Input the Account Number:\n");
    scanf("%d", &account_num);

    for (int i = 0; i < count_customers; i++)
    {
        if (customers[i].Account_num == account_num)
        {
            printf("Input the Amount you want to withdraw from your Account:\n");
            scanf("%f", &amount);

            if (customers[i].Account_bal >= amount)
            {
                customers[i].Account_bal -= amount; // Subtracting the withdrawal amount from the account balance!
                printf("%f Amount successfully withdrawl from your Account linked with Account Number %d\n", amount, account_num);
            }
            else
            {
                printf("Insuffiecient balance in your account!\n");
            }
        }
    }
    return;
}

void load_customers()
{
    FILE *file = fopen("BMS.txt", "rb"); // BMS stands for bank managemwnt system!

    if (!file)
    {
        printf("No previous data was found!\n");
    }

    while (fread(&customers[count_customers], sizeof(customer), 1, file))
    {
        count_customers++; // trying to read all customers!
    }

    fclose(file);
}

void save_customers()
{
    FILE *file = fopen("BMS.txt", "wb");

    if (!file)
    {
        printf("Error in saving customers data!");
    }

    fwrite(customers, sizeof(customer), count_customers, file);

    fclose(file);
}
