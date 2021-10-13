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
	/* 
	 * Add code to list all the contacts availabe in address_book.csv file
	 * Should be menu based
	 * The menu provide navigation option if the entries increase the page size
	 */ 

	return e_success;
}

void menu_header(const char *str)
{
	fflush(stdout);

	system("clear");

	printf("#######  Address Book  #######\n");
	if (str != '\0')
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
				list_contacts;
				break;
			case e_save:
				save_file(address_book);
				break;
			case e_exit:
				break;
		}
	} while (option != e_exit);

	return e_success;
}

Status add_contacts(AddressBook *address_book)
{
	AddressBook newPerson;
	int option;

	printf("0. Back\n");
	printf("1. Name       :\n");
	printf("2. Phone No %i:\n", len(newPerson.list->phone_numbers));
	printf("3. Email ID %i:\n", len(newPerson.list->email_addresses));
	printf("\n");
	printf("Please select an option: ");
	scanf("%i", &option);

	do {
		int len_phone = len(newPerson.list->phone_numbers);
		int len_email = len(newPerson.list->email_addresses);

		if (option == 1) {
			printf("Enter the name: ");
			scanf("%s", &newPerson.list->name);
		}
		else if (option == 2) {
			
			printf("Enter Phone Number %i, [Please enter the same option of alternate Phone Number]:\n", len_phone);
			scanf("%s", &newPerson.list->phone_numbers[len_phone]);
			len_phone++;
		}
		else if (option == 3) {
			printf("Enter Email ID %i, [Please enter the same option of alternate Email ID]:\n", len_email);
			scanf("%s", &newPerson.list->email_addresses[len_email]);
			len_email++;
		}

		printf("0. Back\n");
		printf("1. Name       : %s\n", newPerson.list->name);
		printf("2. Phone No %i: %s\n", len_phone, newPerson.list->phone_numbers[len_phone]);
		printf("3. Email ID %i: %s\n", len_email, newPerson.list->email_addresses[len_email]);
		printf("\n");
		printf("Please select an option: ");
		scanf("%i", &option);

	} while (option != 0);

	newPerson.count = address_book->count + 1;
	newPerson.list->si_no = newPerson.count;
	
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	/* Add the functionality for adding contacts here */
}

Status search_contact(AddressBook *address_book)
{
	/* Add the functionality for search contacts here */
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
	
	menu_header("Delete Contact:\n");
	printf("0. Back\n");
	printf("1. Name       : %s\n", address_book->list[serialNum-1].name);

	printf("2. Phone No 1 : %s\n", address_book->list[serialNum-1].phone_numbers[0]);
	for(; phoneEntry < PHONE_NUMBER_COUNT; phoneEntry++);
	{
		printf("   Phone No %d : %s\n", phoneEntry, address_book->list[serialNum-1].phone_numbers[phoneEntry-1]);
	}

	printf("3. Email No 1 : %s\n", address_book->list[serialNum-1].phone_numbers[0]); 
	for(; emailEntry < PHONE_NUMBER_COUNT; emailEntry++);
	{
		printf("   Phone No %d : %s\n", emailEntry, address_book->list[serialNum-1].phone_numbers[emailEntry-1]);
	}
	
	printf("Enter 'Y' to delete. [Press any key to ignore]: ");
	option = get_option(CHAR,"");
	if(option != 'Y'||option != 'y')
	{
		return e_back;
	}

	

}
