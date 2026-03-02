#include <stdio.h>      // Includes standard input/output functions like printf()
#include <stdlib.h>     // Includes standard library functions like(exit)
#include <string.h>     // Includes string handling functions like strcmp(), strstr(), strcpy(), etc.

#include "contact.h"    // User-defined header file containing Contact structure definition
#include "file.h"       // User-defined header file for file handling related functions

// Function to list all contacts from the AddressBook
// AddressBook *addressBook -> Pointer to AddressBook structure
// int sortCriteria -> Variable to decide sorting method
void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    printf("\ncontact list\n");

    // Outer loop of Bubble Sort
    for(int i = 0; i < addressBook->contactCount - 1; i++) // Runs (contactCount - 1) times
    {
        // Inner loop of Bubble Sort
        for(int j = 0; j < addressBook->contactCount - i - 1; j++)// After every pass, largest element moves to end,// So inner loop reduces by i
        {
            // Compare two adjacent contact names using strcmp()
            // strcmp() returns:
            if(strcmp(addressBook->contacts[j].name,
                      addressBook->contacts[j+1].name) > 0)// > 0  → First word comes AFTER second word (dictionary order)
                                                          // < 0  → First word comes BEFORE second word
                                                         //  0   → Both words are SAME
            {
                // If name at j is greater than name at j+1
                // Swap the two Contact structures
                Contact temp = addressBook->contacts[j]; // Store current contact in temporary variable
                addressBook->contacts[j] = addressBook->contacts[j+1];  // Move next contact to current position
                addressBook->contacts[j+1] = temp;   // Place stored contact into next position
            }
        }
    }
    // Loop to print sorted contact details
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%d.Name:  %s\n  Phone: %s\n  Email: %s\n",
               i + 1,                              // Serial number (starting from 1)
               addressBook->contacts[i].name,     // Contact name
               addressBook->contacts[i].phone,   // Contact phone number
               addressBook->contacts[i].email); // Contact email
    }
}

void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


int validate_phone(AddressBook *addressBook, char *phone)
{
    int len = strlen(phone);   // Find length of phone number

    if(len != 10)              // Check if length is not 10
    {
        return 0;              // Invalid phone number
    }

    // Check if all characters are digits (0–9)
    for(int i = 0; i < len; i++)
    {
        if(phone[i] < '0' || phone[i] > '9')  // If not a digit
        {
            return 0;                       // Invalid phone number
        }
    }

    // Check if phone number already exists (duplicate check)
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0)
            return 0;                  // Number already exists
    }

    return 1;                      // Phone number is valid
}

int validate_email(AddressBook *addressBook, char *email)
{
    int at_count = 0;          // Count number of '@'
    int at_position = 0;       // Store position of '@'
    int dot_position = 0;      // Store position of '.'
    int len = strlen(email);   // Get length of email

    for(int i = 0; i < len; i++)
    {
        if(email[i] == ' ')    // Check if space exists
        {
            return 0;          // Invalid email
        }

        if(email[i] == '@')    // If '@' found
        {
            at_count++;        // Increase count
            at_position = i;   // Store its position
        }

        if(email[i] == '.')    // If '.' found
        {
            dot_position = i;  // Store its position
        }

        if(email[i] >= 'A' && email[i] <= 'Z')  // If capital letter found
        {
            return 0;          // Invalid email
        }
    }

    if(at_count != 1)          // Must contain exactly one '@'
    {
        return 0;
    }

    if(at_position == 0 || at_position == len - 1)  
    {
        return 0;              // '@' cannot be first or last
    }

    if(dot_position == -1 || dot_position < at_position)
    {
        return 0;              // '.' must come after '@'
    }

    if(dot_position == at_position + 1)
    {
        return 0;              // '.' cannot be immediately after '@'
    }

    if(dot_position == len - 1)
    {
        return 0;              // '.' cannot be last character
    }

    // Check if email already exists (duplicate check)
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].email, email) == 0)
            return 0;          // Email already exists
    }

    return 1;                  // Email is valid
}

void createContact(AddressBook *addressBook)
{
    // Check if address book is already full
    if(addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("Addressbook is full\n");
        return;   // Stop function
    }

    // Get pointer to new contact position
    Contact *newContact = &addressBook->contacts[addressBook->contactCount];

    // Get name from user
    printf("Enter Name: ");
    scanf(" %[^\n]", newContact->name);

    // Get valid phone number
    while(1)
    {
        printf("Enter Phone (10 digit): ");
        scanf(" %s", newContact->phone);

        if(validate_phone(addressBook, newContact->phone)) //function call to validate Phone number
            break;   // Exit loop if valid

        printf("Invalid or Duplicate phone number! Try again.\n");
    }

    // Get valid email
    while(1)
    {
        printf("Enter Email: ");
        scanf(" %s", newContact->email);

        if(validate_email(addressBook, newContact->email)) //funtion call to validate Email
            break;   // Exit loop if valid

        printf("Invalid or Duplicate Email! Try again.\n");
    }

    addressBook->contactCount++;   // Increase contact count

    printf("Contact created successfully!\n");
}

int searchContact(AddressBook *addressBook) 
{
    int choice;          // Store search choice
    char search[50];     // Store search input

    // Display search menu
    printf("\nSearch Menu:\n");
    printf("1. Search by Name\n");
    printf("2. Search by Phone\n");
    printf("3. Search by Email\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    // Get value to search
    printf("Enter search value: ");
    scanf(" %[^\n]", search);

    // Loop through all contacts
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        Contact *c = &addressBook->contacts[i];  // Current contact

        // Check based on user choice
        if ((choice == 1 && strstr(c->name, search) != NULL) ||
            (choice == 2 && strstr(c->phone, search) != NULL) ||
            (choice == 3 && strstr(c->email, search) != NULL))
        {
            // If match found
            printf("\nContact Found:\n");
            printf("Name: %s\nPhone: %s\nEmail: %s\n",c->name, c->phone, c->email);

            return i;   // Return index of found contact
        }
    }

    printf("Contact not found\n");
    return -1;   // Return -1 if not found
}

void editContact(AddressBook *addressBook)
{
    // First search the contact
    int index = searchContact(addressBook);

    // If contact not found
    if(index == -1)
    {
        printf("cannot edit. Contact not found!\n");
        return;   // Stop function
    } 

    int choice;

    // Show edit menu
    printf("\nEdit Menu:\n");
    printf("1. Edit Name\n");
    printf("2. Edit Phone\n");
    printf("3. Edit Email\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    // Get pointer to selected contact
    Contact *c = &addressBook->contacts[index];

    // If user chooses to edit name
    if (choice == 1)
    {
        printf("Enter new name: ");
        scanf(" %[^\n]", c->name);   // Directly update name
        printf("Name updated successfully!\n");
    }
    
    // If user chooses to edit phone
    else if(choice == 2)
    {
        char newphone[20];   // Temporary variable

        while(1)
        {
            printf("Enter new Phone (10 digit): ");
            scanf("%s", newphone);

            // If user enters same phone number of same contact
            if(strcmp(newphone, c->phone) == 0)
            {
                printf("Phone updated successfully!\n");
                break;
            }

            // Validate new phone
            if(validate_phone(addressBook, newphone)) //function call for Phone number validation
            {
                strcpy(c->phone, newphone);   // Copy new phone number
                printf("Phone updated successfully!\n");
                break;
            }

            printf("Invalid or Duplicate phone number! Try again.\n");
        }
    }    

    // If user chooses to edit email
    else if (choice == 3)
    {
        char newemail[50];   // Temporary variable

        while(1)
        {
            printf("Enter new email: ");
            scanf(" %s", newemail);

            // If user enters same email
            if(strcmp(newemail, c->email) == 0)
            {
                printf("Email updated successfully!\n");
                break;
            }

            // Validate new email
            if(validate_email(addressBook, newemail)) // function call for Email validation
            {
                strcpy(c->email, newemail);   // Copy new email
                printf("Email updated successfully!\n");
                break;
            }

            printf("Invalid or Duplicate Email! Try again.\n");
        }
    }

    // If wrong menu choice
    else
    {
        printf("Invalid choice!\n");
    }
}
    


void deleteContact(AddressBook *addressBook)
{
    // First search the contact to delete
    int index = searchContact(addressBook);

    // If contact not found
    if(index == -1)
    {
        printf("cannot delete. Contact not found!\n");
        return;   // Stop function
    } 

    // Shift all contacts one position left
    // This removes the selected contact
    for (int i = index; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    // Reduce total contact count
    addressBook->contactCount--;

    printf("Contact deleted successfully!\n");
}
