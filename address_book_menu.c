#include <stdio.h>
// #include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

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
/*	title = WTF IS TITLE FOR????? THERE IS NO TITLE FOR THIS CHART
	index = ARRAY OF ENTRY INDEXES to list
	msg = end msg for response (press q to go back, enter number to delete or edit)
	Mode = what method is calling this? edit, add, delete, search?
		list, search, add
*/
Status list_contacts(AddressBook *address_book, int *index, Modes mode,const char *msg, int IndexLength)
{
	ContactInfo currentEntry = *(address_book->list);

	menu_header("Search Result:\n");
    printf("=================================================================================================\n"); 
	printf(": S.No\t: Name\t\t\t: Phone No\t\t\t: Email ID\t\t\t:\n");
    printf("=================================================================================================\n"); 
	if(mode == e_list){
		for(int i = 0; i < address_book->count; i++){
			//look at the start pointer of list, move it x ContactInfo Down
			currentEntry = address_book->list[i];

			printf(": %d\t: %s\t\t\t: %d\t\t\t: %s\t\t\t:\n",currentEntry.si_no, currentEntry.name,currentEntry.phone_numbers[0], currentEntry.email_addresses[0] );

			//if there are more rows for additional contacts
			for(int j = 1; j < 5; j++){
				printf(": \t\t\t: %d\t\t\t: %s\t\t\t:\n:", currentEntry.phone_numbers[i], currentEntry.email_addresses[i]);
			}
			printf("=================================================================================================\n");
		}
		//printf(msg);
		int option = get_option(CHAR,"");
		//assume 0 is the response for a "go back" input, q
		if(option == 0){
			return e_success;
		}

	//if we are listing after a search function call
	}else{
		for(int i = 0; i < IndexLength; i++){
			currentEntry = address_book->list[i];
			printf(": %d\t: %s\t\t\t: %d\t\t\t: %s\t\t\t:\n",currentEntry.si_no, currentEntry.name,currentEntry.phone_numbers[0], currentEntry.email_addresses[0] );

			//if there are more rows for additional contacts
			for(int j = 1; j < 5; j++){
				printf(": \t\t\t: %d\t\t\t: %s\t\t\t:\n:", currentEntry.phone_numbers[i], currentEntry.email_addresses[i]);
			}
			printf("=================================================================================================\n");
		}
	}
	print(msg);
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
	char nameChar[32];
	char phoneChar[32];
	char emailChar[32];
	ContactInfo newContact;
	newContact.si_no = address_book->list->si_no + 1;

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
					scanf("%s", &newContact.name[0]);
				case e_third_opt:
					printf("Enter Phone Number %i, [Please enter the same option of alternate Phone Number]:\n", phoneEntry);
					scanf("%s", &newContact.phone_numbers[phoneEntry]);
					phoneEntry++;
					break;
				case e_fourth_opt:
					printf("Enter Email ID %i, [Please enter the same option of alternate Email ID]:\n", emailEntry);
					scanf("%s", &newContact.email_addresses[emailEntry]);
					emailEntry++;
					break;
				case e_fifth_opt:
					break;
			}

		menu_header("Add Contact:\n");
		printf("0. Back\n");
		printf("1. Name       : %s\n", newContact.name[0]);
		printf("2. Phone No %i: %s\n", phoneEntry, newContact.phone_numbers[phoneEntry]);
		printf("3. Email ID %i: %s\n", emailEntry, newContact.email_addresses[emailEntry]);
		printf("\n");
		printf("Please select an option: ");
		option = get_option(NUM, "");
	}

	address_book->count++;
	// address_book->list
	
}


//(string to search, addressbook, # of contacts available to loop, what field (0,1,2), msg for user input, what mode to search)
Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	//point to first entry
	ContactInfo currentEntry;
	int index[MAX_CONTACTS];
	int indexLength = 0;
	
	switch(field){
		//for names
		case 0:
			for(int i = 0; i < loop_count;i++){
				currentEntry = address_book->list[i];
				if(strcmp(currentEntry.name, str)){
					index[indexLength] = currentEntry.si_no;
				}
			}
			break;
		//for phone numbers
		case 1:
			for(int i = 0; i < loop_count;i++){
				currentEntry = address_book->list[i];
				for(int j = 0; j < 5;j++){
					if(strcmp(currentEntry.phone_numbers[j], str)){
						index[indexLength] = currentEntry.si_no;
					}
				}
			}
				
			break;
		//for emails
		case 2:
			for(int i = 0; i < loop_count;i++){
				currentEntry = address_book->list[i];
				for(int j = 0; j < 5;j++){
					if(strcmp(currentEntry.email_addresses[j], str)){
						index[indexLength] = currentEntry.si_no;
					}
				}
			}
			break;
	}
	
	//Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)
	if(indexLength > 0){
		//char temp[] = "Temp Title";
		list_contacts(address_book, index, mode,msg, indexLength);
	}else{
		printf("There are no entries values which match. Sorry\n");
		return e_success;
	}
	
}


//Under maintanence: Ben
Status search_contact(AddressBook *address_book){
	char input[32];
	int option = -1;
	do{
		menu_header("Search Contact By:\n");
		printf("0. Back\n");
		printf("1. Name\n");
		printf("2. Phone No\n");
		printf("3. Email ID\n\n");
		printf("Please select an option: ");
		int option = get_option(NUM, "");
		
		
		switch (option){
			case e_first_opt:
				break;
			case e_second_opt:
				printf("Enter a name to search: ");
				scanf("%s",&input);
				search(input, address_book,address_book->count,0, "Press: [q] | Cancel: ",e_search);
				break;
				//
			case e_third_opt:
				printf("Enter Phone Number to search:");
				scanf("%s",&input);
				search(input, address_book,address_book->count,1, "Press: [q] | Cancel: ",e_search);
				break;
			case e_fourth_opt:
				printf("Enter an email address to search: ");
				scanf("%s",&input);
				search(input, address_book,address_book->count,2, "Press: [q] | Cancel: ",e_search);
				break;
		}
		option = get_option(CHAR,"");
		if(option == e_back){
			return e_back;
		}
	}while(option != e_first_opt);
	return e_back;
}

Status edit_contact(AddressBook *address_book)
{
	int option = -1;
	char input[32];
	do{
		menu_header("Edit Contact By:\n");
		printf("0. Back\n");
		printf("1. Name\n");
		printf("2. Phone No\n");
		printf("3. Email ID\n\n");
		printf("Please select an option: ");
		bool proceed = true;
		int option = get_option(NUM, "");

		switch (option){
			case e_first_opt:
				proceed = false;
				break;
			case e_second_opt:
				printf("Enter a name to edit: ");
				scanf("%s",&input);
				search(input, address_book,address_book->count,0, "Press: [s] = Select. [q] | Cancel: ",e_edit);
				break;
				//
			case e_third_opt:
				printf("Enter Phone Number to edit:");
				scanf("%s",&input);
				search(input, address_book,address_book->count,1, "Press: [s] = Select. [q] | Cancel:",e_edit);
				break;
			case e_fourth_opt:
				printf("Enter an email address to edit: ");
				scanf("%s",&input);
				search(input, address_book,address_book->count,2, "Press: [s] = Select. [q] | Cancel:",e_edit);
				break;
		}
		if(proceed){	
			option = get_option(CHAR,"");
			if(option == e_edit){
				printf("Select a Serial Number (S.No) to Delete: ");
				int serialNum = get_option(NUM, "");
				ContactInfo CurrentEntry = address_book->list[serialNum -1];
				int phoneEntry = 1;
				int emailEntry = 1;
				

				menu_header("Edit Contact:\n");
				printf("0. Back\n");
				printf("1. Name\t\t: %s\n", CurrentEntry.name);

				printf("2. Phone No 1\t: %s\n", CurrentEntry.phone_numbers[0]);
				for(; phoneEntry < PHONE_NUMBER_COUNT; phoneEntry++);
				{
					//if there is something in the phone Number slots
					if(CurrentEntry.phone_numbers[phoneEntry-1] != NULL){
						printf("\t\t%d : %s\n", CurrentEntry.phone_numbers[phoneEntry-1]);
					}
				}

				printf("3. Email No 1 : %s\n", CurrentEntry.phone_numbers[0]); 
				for(; emailEntry < PHONE_NUMBER_COUNT; emailEntry++);
				{
					//if there is something in the email slots
					if(CurrentEntry.phone_numbers[emailEntry-1] != NULL){
						printf("\t\t%d : %s\n", emailEntry, CurrentEntry.phone_numbers[emailEntry-1]);
					}
				}
				
				printf("Please select an option: ");
				option = get_option(NUM, "");
				switch(option){
					case 0:
						break;
					case 1:
						printf("Enter a New Name: ");
						scanf("%s", CurrentEntry.name);
						break;
					case 2:
						printf("Enter Phone Number index to be changed[Max 5]: ");
						option = get_option(NUM, "");
						printf("Enter Phone Number %d: [Just enter removes the entry]:");
						scanf("%s", CurrentEntry.phone_numbers[option]);
						break;
					case 3:
						printf("Enter email address index to e changed[Max 5]: ");
						printf("Enter email address %d: [Just enter removes the entry]:");
						scanf("%s", CurrentEntry.email_addresses[option]);
						break;
				}

			}else if(option == e_back){
				return e_back;
			}
		}
	}while(option != e_first_opt);
	return e_back;
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
