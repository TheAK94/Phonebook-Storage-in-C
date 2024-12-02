#include <stdio.h>
#include <string.h>

// structure
typedef struct Contacts
{
    char name[50];
    char phn_no[15];
    char email[50];
} cont;

// Function declarations
void displayMenu();
void addContact();
void viewContacts();
void searchContact(char *query);
void deleteContact(char *name);

// MAIN function
int main()
{
    int choice;
    char query[50];

    do 
    {
        displayMenu();
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addContact();
                break;

            case 2:
                viewContacts();
                break;

            case 3:
                printf("Enter name or phone to search: ");
                scanf("%s", query);
                searchContact(query);
                break;

            case 4:
                printf("Enter name to delete: ");
                scanf("%s", query);
                deleteContact(query);
                break;
        
            case 5:
                printf("Exiting...");
                break;

            default:
                printf("INVALID INPUT");
                break;
        }
    } while (choice != 5);
    return 0;
}

// Functions
void displayMenu()
{
    printf("-----------MAIN MENU-----------\n");
    printf("1. Add Contact\n");
    printf("2. View Contacts\n");
    printf("3. Search Contact\n");
    printf("4. Delete Contact\n");
    printf("5. EXIT\n");
}

void addContact()
{
    FILE *file = fopen("phonebook.csv", "a");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    cont newContact;
    printf("Enter Name: ");
    scanf("%s", newContact.name);
    printf("Enter Phone: ");
    scanf("%s", newContact.phn_no);
    printf("Enter Email: ");
    scanf("%s", newContact.email);

    fprintf(file, "%s,%s,%s\n", newContact.name, newContact.phn_no, newContact.email);
    fclose(file);

    printf("Contact added successfully!\n");
}

void viewContacts()
{
    FILE *file = fopen("phonebook.csv", "r");
    if (file == NULL)
    {
        printf("No contacts found.\n");
        return;
    }

    cont temp;
    char line[150];
    printf("\n--- Phonebook Contacts ---\n");
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%[^,],%s", temp.name, temp.phn_no, temp.email); // Parse CSV line into struct
        printf("Name: %s\nPhone: %s\nEmail: %s\n", temp.name, temp.phn_no, temp.email);
        printf("--------------------------\n");
    }

    fclose(file);
}

void searchContact(char *query)
{
    FILE *file = fopen("phonebook.csv", "r");
    if (file = NULL)
    {
        printf("No contacts found.\n");
        return;
    }

    cont temp;
    char line[150];
    int found = 0;

    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "%[^,],%[^,],%s", temp.name, temp.phn_no, temp.email);

        if (strcmp(temp.name, query)==1 || strcmp(temp.phn_no, query)==1)
        {
            printf("\nFound Contact:\n");
            printf("Name: %s\nPhone: %s\nEmail: %s\n", temp.name, temp.phn_no, temp.email);
            printf("--------------------------\n");
            found = 1;
            break;
        }
    }

    if (!found) printf("Contact not found.\n");

    fclose(file);
}

void deleteContact(char *name)
{
    FILE *file = fopen("phonebook.csv", "r");
    FILE *temp = fopen("temp.csv", "w");

    if (!file || !temp)
    {
        printf("Error opening file!\n");
        return;
    }

    cont tempContact;
    char line[150];
    int found = 0;

    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "%[^,],%[^,],%s", tempContact.name, tempContact.phn_no, tempContact.email);

        if (strcmp(tempContact.name, name) != 0)
        {
            fputs(line, temp);
        }
        else {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp);

    remove("phonebook.csv");
    rename("temp.csv", "phonebook.csv");

    if (found) printf("Contact deleted  successfully!\n");
    else printf("Contact not found.\n");
}