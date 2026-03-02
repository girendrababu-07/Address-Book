#include <stdio.h>
#include<stdlib.h>
#include "file.h"

#include <stdio.h>
#include <stdlib.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fptr;   // File pointer

    // Open file in write mode
    fptr = fopen("contacts.csv", "w");

    // If file not opened
    if(fptr == NULL)
    {
        printf("Error in Opening file: contact.csv\n");
        return;
    }

    // Write each contact to file
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fptr,"%s,%s,%s\n",   // Save in CSV format
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }
    
    fclose(fptr);   // Close file

    printf("Saved %d contacts to file.\n", addressBook->contactCount);

    exit(0);   // Stop program
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fptr;   // File pointer

    addressBook->contactCount = 0;   // Start with 0 contacts

    // Open file in read mode
    fptr = fopen("contacts.csv", "r");

    // If file does not exist
    if (fptr == NULL)
    {
        printf("File not found. Starting with empty address book.\n");
        return;
    }

    // Read contacts from file
    for (int i = 0; i < MAX_CONTACTS; i++)
    {
        // Read name, phone and email separated by comma
        if (fscanf(fptr, "%[^,],%[^,],%[^\n]\n",
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email) != 3)
        {
            break;   // Stop if file ends
        }

        addressBook->contactCount++;   // Increase count
    }

    fclose(fptr);   // Close file

    printf("Loaded %d contacts from file.\n", addressBook->contactCount);
}
