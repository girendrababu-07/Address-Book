/*
Name : ADDRESSBOOK-NEWDESIGN
Date : 28/02/2026
description : This Address Book program allows users to create, search, edit, delete, and list contacts with phone and email validation.
              It also saves contacts to a file and loads them back when the program starts.
Sample Input :1
              
            
Sample Output :

              Contact created successfully!

              contact list
              
              

              Saved 1 contacts to file.
*/

#include <stdio.h>
#include "contact.h"

int main() 
{
    int choice;                  // Stores user's menu choice
    AddressBook addressBook;     // This structure holds:
                                 // - Array of contacts
                                 // - Number of contacts currently stored
   
    initialize(&addressBook); /*Initialize the address book.      What initialize() does internally:
                                                                - Sets contactCount to 0
                                                                - Loads contacts from file (contacts.csv)
                                                                 */
                                                        

    
    do   //do-while loop is used because: - Menu must show at least once. 
    {
        
            //Display main menu to the user, These options correspond to core address book operations.        
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");      // Add new contact
        printf("2. Search contact\n");      // Search by name/phone/email
        printf("3. Edit contact\n");        // Modify existing contact
        printf("4. Delete contact\n");      // Remove contact
        printf("5. List all contacts\n");   // Display all contacts
        printf("6. Save contacts\n");       // Save current contacts to file
        printf("7. Exit\n");                // Exit program
        printf("Enter your choice: ");

        
        scanf("%d", &choice); //Read user input,   choice determines which function will be executed.
          


    
        switch (choice)  // switch-case is used to execute  different blocks of code based on user choice.
        {
                                            //Calls createContact(),    
            case 1:                         //- Takes addressBook pointer, - Adds new contact,- Performs validation, - Increases contactCount.       
                createContact(&addressBook); 
                break;

                                            //Calls searchContact()
            case 2:                         // - Asks search criteria, - Searches through contacts array, - Prints matching contact.   
                searchContact(&addressBook);     
                break;

                                            //Calls editContact()
            case 3:                         // - First searches contact, - Then allows modification, - Updates data inside structure. 
                editContact(&addressBook);
                break;

                                            //  Calls deleteContact()
            case 4:                         // - Searches contact, - Shifts array elements left, - Decreases contactCount. 
                deleteContact(&addressBook);
                break;

                                            //Calls listContacts()
            case 5:                         //Displays all contacts, - May include sorting depending on implementation
                listContacts(&addressBook, 0);
                break;

                                            //Saves current in-memory contacts to file.
            case 6:                         // If this is not called, newly created contacts will not available after program closes., 
                printf("Saving contacts...\n");
                saveContactsToFile(&addressBook);
                break;

            case 7:                         //Exit selected,  Program will leave loop.
                printf("Exiting program...\n");
                break;

                                            //Handles invalid input.
            default: 
               
                printf("Invalid choice. Please try again.\n");//If user enters number outside 1–7,this message will be shown.
        }

    } while (choice != 7);   // Continue until user selects Exit

    return 0;               //return 0 means successful execution.
}
