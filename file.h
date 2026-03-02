#ifndef FILE_H
#define FILE_H
// Prevents this file from being included multiple times

#include "contact.h" // Includes Contact and AddressBook structure definitions

void saveContactsToFile(AddressBook *addressBook);// Function declaration to save contacts into file
void loadContactsFromFile(AddressBook *addressBook); // Function declaration to load contacts from file

#endif
// End of FILE_H header file
