#ifndef CONTACT_H
#define CONTACT_H
// If CONTACT_H is not defined, define it
// This prevents multiple inclusion of this file

#define MAX_CONTACTS 100
// Maximum number of contacts allowed

// Structure to store one contact details
typedef struct {
    char name[50];     // Store name (max 49 characters + '\0')
    char phone[20];    // Store phone number
    char email[50];    // Store email
} Contact;

// Structure to store all contacts
typedef struct {
    Contact contacts[100];  // Array of contacts
    int contactCount;       // Number of contacts currently stored
} AddressBook;

// Function declarations

void createContact(AddressBook *addressBook);  // Create a new contact 
int searchContact(AddressBook *addressBook);  // Search a contact and return index
void editContact(AddressBook *addressBook);   // Edit existing contact 
void deleteContact(AddressBook *addressBook);   // Delete a contact
void listContacts(AddressBook *addressBook, int sortCriteria);  // Display all contacts
void initialize(AddressBook *addressBook);    // Initialize address book  
void saveContactsToFile(AddressBook *AddressBook);  // Save contacts to file

#endif  // End of header file
