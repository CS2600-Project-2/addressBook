#include <stdio.h>
// #include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "address_book_fops.h"
// #include "abk_log.h"
#include "address_book_menu.h"
#include "address_book.h"

//USER INPUT PROCESSING
int get_option(int type, const char *msg)
{
	/*
	 * Mutilfuction user intractions like
	 * Just an enter key detection
	 * Read an number
	 * Read a charcter
	 */ 

	/* Fill the code to add above functionality */
	
}

Status save_prompt(AddressBook *address_book)
{
	char option;

	do
	{
		main_menu();

		option = get_option(CHAR, "\rEnter 'N' to Ignore and 'Y' to Save: ");

		if (option == 'Y')
		{
			save_file(address_book);
			printf("Exiting. Data saved in %s\n", DEFAULT_FILE);

			break;
		}
	} while (option != 'N');

	free(address_book->list);

	return e_success;
}

Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)
{
	address_book->fp = fopen(DEFAULT_FILE, "r'");
	ContactInfo currentEntry = *(address_book->list);

	for(int i = 0; i < address_book->count; i++){
		//look at the start pointer of list, move it x ContactInfo Down
		currentEntry = *(address_book->list + i*sizeof(ContactInfo));

		printf("%d\t: %s \t:",currentEntry.si_no, currentEntry.name);
		printf("%d\t: %s \t:\n", currentEntry.phone_numbers[0], currentEntry.email_addresses[0]);


		//if there are more rows for additional contacts
		for(int j = 1; j < 5; j++){
			if(currentEntry.phone_numbers[i] != NULL){
				printf("%d\t:", currentEntry.phone_numbers[i]);
			}
			if(currentEntry.email_addresses[i] != NULL){
				printf("%s\t:\n", currentEntry.email_addresses[i]);
			}
		}
	}


	return e_success;
}

void menu_header(const char *str)
{
	fflush(stdout);

	system("clear");

	printf("#######  Address Book  #######\n");
	if (*str != '\0')
	{
		printf("#######  %s\n", str);
	}
}

void main_menu(void)
{
	menu_header("Features:\n");

	printf("0. Exit\n");
	printf("1. Add Contact\n");
	printf("2. Search Contact\n");
	printf("3. Edit Contact\n");
	printf("4. Delete Contact\n");
	printf("5. List Contacts\n");
	printf("6. Save\n");
	printf("\n");
	printf("Please select an option: ");
}

//WE NEED TO CREATE MAIN where we load file
Status menu(AddressBook *address_book)
{
	ContactInfo backup;
	Status ret;
	int option;

	do
	{
		main_menu();

		option = get_option(NUM, "");

		//if we have no entries, you can't do anything but add entries
		if ((address_book-> count == 0) && (option != e_add_contact))
		{
			get_option(NONE, "No entries found!!. Would you like to add? Use Add Contacts");

			continue;
		}

		switch (option)
		{
			case e_add_contact:
				add_contacts(address_book);
				break;
			case e_search_contact:
				search_contact(address_book);
				break;
			case e_edit_contact:
				edit_contact(address_book);
				break;
			case e_delete_contact:
				delete_contact(address_book);
				break;
			case e_list_contacts:
				//list_contacts;
				break;
			case e_save:
				save_file(address_book);
				break;
			case e_exit:
				printf("GoodBye\n");
				break;
		}
	} while (option != e_exit);


	return e_success;
}

Status add_contacts(AddressBook *address_book)
{
	/* Add the functionality for adding contacts here */
	int option;
	int phoneEntry = 1;
	int emailEntry = 1;
	ContactInfo *newContact;
	newContact = address_book->list;
	for (int i = 0; i < address_book->count; i++)
	{
		newContact++;
	}

	menu_header("Add Contact:\n");
	printf("0. Back\n");
	printf("1. Name       :\n");
	printf("2. Phone No %i:\n", phoneEntry);
	printf("3. Email ID %i:\n", emailEntry);
	printf("\n");
	printf("Please select an option: ");
	option = get_option(NUM, "");

	while (option != e_first_opt && PHONE_NUMBER_COUNT < 5 && EMAIL_ID_COUNT < 5) {
		switch (option)
			{
				case e_first_opt:
					return e_back;
					break;
				case e_second_opt:
					printf("Enter the name: ");
					scanf("%s", &newContact->name[0]);
				case e_third_opt:
					printf("Enter Phone Number %i, [Please enter the same option of alternate Phone Number]:\n", phoneEntry);
					scanf("%s", &newContact->phone_numbers[phoneEntry]);
					phoneEntry++;
					break;
				case e_fourth_opt:
					printf("Enter Email ID %i, [Please enter the same option of alternate Email ID]:\n", emailEntry);
					scanf("%s", &newContact->email_addresses[emailEntry]);
					emailEntry++;
					break;
				case e_fifth_opt:
					break;
			}

		menu_header("Add Contact:\n");
		printf("0. Back\n");
		printf("1. Name       : %s\n", newContact->name[0]);
		printf("2. Phone No %i: %s\n", phoneEntry, newContact->phone_numbers[phoneEntry]);
		printf("3. Email ID %i: %s\n", emailEntry, newContact->email_addresses[emailEntry]);
		printf("\n");
		printf("Please select an option: ");
		option = get_option(NUM, "");
	}

	address_book->count++;
	
}
// under maintenance by: Nick
//(string to search, addressbook, ?, what field, ??, modes?)
Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	int i;
	//
	menu_header("Search Result:\n");
	printf("\n");
	printf("%.*s\n", 50, "########################");
	// printf(": S.No  :  Name")


}

//Under maintanence: Ben, Nick
Status search_contact(AddressBook *address_book){
	int option;
	char input[32];
	menu_header("Search Contact By:\n");
	printf("0. Back\n");
	printf("1. Name\n");
	printf("2. Phone No\n");
	printf("3. Email ID\n\n");
	printf("Please select an option: ");
	option = get_option(NUM, "");

	while (option != e_first_opt) {
		switch (option){
			case e_first_opt:
				return e_back;
				break;
			case e_second_opt:
				printf("Enter a name to search: ");
				scanf("%s",input);
				search(input, address_book, address_book->count, 0, "Press [q] | Cancel: ", e_search);
				option = get_option(CHAR, "");
				if (option == "q")
				{
					return e_back;
				}
				break;
			case e_third_opt:
				printf("Enter Phone Number to search:");
				scanf("%s",input);
				search(input, address_book, address_book->count, 1, "Press [q] | Cancel: ", e_search);
				if (option == "q")
				{
					return e_back;
				}
				break;
			case e_fourth_opt:
				printf("Enter an email address to search: ");
				scanf("%s",input);
				search(input, address_book, address_book->count, 2, "Press [q] | Cancel: ", e_search);
				if (option == "q")
				{
					return e_back;
				}
				break;
			default:
				printf("Please enter a valid number.");
		}
	}
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */	
	int option;
	int serialNum;
	int field;
	char searchFor[32];
	int phoneEntry = 1;
	int emailEntry = 1;
	ContactInfo *entry;
	entry = address_book->list;

	menu_header("Search Contact to delete by:\n");

	printf("0. Back\n");
	printf("1. Name\n");
	printf("2. Phone No\n");
	printf("3. Email No\n"); 
	printf("4. Serial No\n");

	printf("\n");
	printf("Please select an option: ");
	option = get_option(NUM, "");

	switch (option)
		{
			case e_first_opt:
				return e_back;
				break;
			case e_second_opt:
				field = 0;
				printf("Enter the Name: ");
				scanf("%s", &searchFor);
				search(searchFor, address_book, address_book->count, field,
				"Press: [s] = Select, [q] | Cancel: ", e_delete);
				option = get_option(CHAR, "");
				if(option == 'q')
				{
					return e_back;
				}
				break;
			case e_third_opt:
				field = 1;
				printf("Enter the Phone No: ");
				scanf("%s", &searchFor);
				search(searchFor, address_book, address_book->count, field,
						"Press: [s] = Select, [q] | Cancel: ", e_delete);
				option = get_option(CHAR, "");
				if(option == 'q')
				{
					return e_back;
				}
				break;
			case e_fourth_opt:
				field = 2; 
				scanf("%s", &searchFor);
				search(searchFor, address_book, address_book->count, field,
						"Press: [s] = Select, [q] | Cancel: ", e_delete);
				option = get_option(CHAR, "");
				if(option == 'q')
				{
					return e_back;
				}
				printf("Enter the Email ID: ");
				break;
			case e_fifth_opt:
				break;
		}

	printf("Select a Serial Number (S.No) to Delete: ");
	serialNum = get_option(NUM, "");
	entry += (serialNum-1);
	
	menu_header("Delete Contact:\n");
	printf("0. Back\n");
	printf("1. Name       : %s\n", &entry->name[0][0]);

	//Printing out phone numbers
	printf("2. Phone No 1 : ");
	if(&entry->phone_numbers[0][0]!=NULL)
	{
		printf("%s", &entry->phone_numbers[0][0]);
		phoneEntry++;
	}

	for(; phoneEntry <= PHONE_NUMBER_COUNT; phoneEntry++);
	{	
		if(&entry->phone_numbers[phoneEntry-1][0]!=NULL)
		{
			printf("   Phone No %d : %s\n", phoneEntry, &entry->phone_numbers[phoneEntry-1][0]);
		}
	}

	//Printing out email addresses
	printf("3. Email ID 1 : "); 
	if(&entry->email_addresses[0][0]!=NULL)
	{
		printf("%s", &entry->email_addresses[0][0]);
		emailEntry++;
	}

	for(; emailEntry <= EMAIL_ID_COUNT; emailEntry++);
	{	
		if(&entry->email_addresses[emailEntry-1][0]!=NULL)
		{
			printf("   Email ID %d : %s\n", emailEntry, &entry->email_addresses[emailEntry-1][0]);
		}
	}
	


	printf("Enter 'Y' to delete. [Press any key to ignore]: ");
	option = get_option(CHAR,"");
	if(option != 'Y'||option != 'y')
	{
		return e_back;
	}

	

}
