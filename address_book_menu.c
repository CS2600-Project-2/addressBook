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
	printf(msg);
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
	//Using this to store user input
	int option;
	int serialNum;
	//Field represents Name=0, Phone=1, or Email=2 
	int field;
	//Using these in a for loop to print avaliable names and phone numbers
	int phoneEntry;
	int emailEntry;
	//User input for name, number, email
	char searchFor[32];
	//Various pointers we will use to access fields and delete contacts
	ContactInfo *entry;
	ContactInfo *curEntry, *nextEntry;
	entry = address_book->list;

	/*Initial Menu Search Contact to Delete by*/
	menu_header("Search Contact to delete by:\n");
	printf("0. Back\n");
	printf("1. Name\n");
	printf("2. Phone No\n");
	printf("3. Email No\n"); 
	printf("4. Serial No\n");
	printf("\n");
	printf("Please select an option: ");

	//Get the user input option and use it for switch
	option = get_option(NUM, "");
	switch (option)
		{
			//Back to main menu
			case e_first_opt:
				return e_back;
			//Delete by name
			case e_second_opt:
				//Set appropriate field for name, search function will need it
				field = 0;
				//Get the name and store it in searchFor
				printf("Enter the Name: ");
				scanf("%s", searchFor);
				//Call the search function
				//Will print contacts with matching names and ask user to select 's' or quit 'q'
				search(searchFor, address_book, address_book->count, field,
						"Press: [s] = Select, [q] | Cancel: ", e_delete);
				//Store their option, return to menu if they chose to quit 'q'
				option = get_option(CHAR, "");
				if(option == 'q')
				{
					return e_back;
				}
				break;
			//Delete by phone number
			case e_third_opt:
				//Set appropriate field for phone number, search function will need it
				field = 1;
				//Get the phone number and store it in searchFor
				printf("Enter the Phone No: ");
				scanf("%s", searchFor);
				//Call the search function
				//Will print contacts with matching phone numbers and ask user to select 's' or quit 'q'
				search(searchFor, address_book, address_book->count, field,
						"Press: [s] = Select, [q] | Cancel: ", e_delete);
				//Store their option, return to menu if they chose to quit 'q'
				option = get_option(CHAR, "");
				if(option == 'q')
				{
					return e_back;
				}
				break;
			//Delete by email
			case e_fourth_opt:
				//Set appropriate field for email, search function will need it
				field = 2; 
				//Get the email and store it in searchFor
				scanf("%s", searchFor);
				//Call the search function
				//Will print contacts with matching phone numbers and ask user to select 's' or quit 'q'
				search(searchFor, address_book, address_book->count, field,
						"Press: [s] = Select, [q] | Cancel: ", e_delete);
				//Store their option, return to menu if they chose to quit 'q'
				option = get_option(CHAR, "");
				if(option == 'q')
				{
					return e_back;
				}
				printf("Enter the Email ID: ");
				break;
			//Delete by Serial Number will go straight to asking
			case e_fifth_opt:
				break;
		}
	//Confirm the serial number
	printf("Select a Serial Number (S.No) to Delete: ");
	serialNum = get_option(NUM, "");
	//Error handling for serial numbers out of range
	if(serialNum<0||serialNum>address_book->count) 
	{
		printf("Sorry that Serial Number is out of range... returning to main menu");
		return e_back;
	}
	//Increment the entry pointer to the right ContactInfo struct
	entry += (serialNum-1);


	/*Second Menu for Delete Contact*/
	//Displays the contacts name phone numbers and email addresses
	menu_header("Delete Contact:\n");
	printf("0. Back\n");
	//Print name of contact
	printf("1. Name       : %s\n", &entry->name[0][0]);
	//Printing out phone numbers
	printf("2. Phone No 1 : ");
	//Verify there is a string to print
	if(&entry->phone_numbers[0][0]!=NULL)
	{
		//Print first phone number and increment
		printf("%s", &entry->phone_numbers[0][0]);
		phoneEntry++;
	}
	//For loop to print phone entries after 1
	for(phoneEntry = 1; phoneEntry <= PHONE_NUMBER_COUNT; phoneEntry++)
	{	
		//Verify there is a string to print
		if(&entry->phone_numbers[phoneEntry-1][0]!=NULL)
		{
			printf("   Phone No %d : %s\n", phoneEntry, &entry->phone_numbers[phoneEntry-1][0]);
		}
	}
	//Printing out email addresses
	printf("3. Email ID 1 : "); 
	//Verify there is a string to print
	if(&entry->email_addresses[0][0]!=NULL)
	{  
		//Print first email address and increment
		printf("%s", &entry->email_addresses[0][0]);
		emailEntry++;
	}
	//For loop to print phone entries after 1
	for(emailEntry = 1; emailEntry <= EMAIL_ID_COUNT; emailEntry++)
	{	
		//Verify there is a string to print
		if(&entry->email_addresses[emailEntry-1][0]!=NULL)
		{
			printf("   Email ID %d : %s\n", emailEntry, &entry->email_addresses[emailEntry-1][0]);
		}
	}
	//After we print menu verify the user wants to delete
	printf("Enter 'Y' to delete. [Press any key to ignore]: ");
	option = get_option(CHAR,"");
	//Return to main menu if user does not pres 'y' or 'Y'
	if(option != 'Y'||option != 'y')
	{
		return e_back;
	}

	/*Deleting contacts*/
	//Delete the last contact
	if(serialNum == address_book->count)
	{
		//Setting all fields equal to null
		memset(entry,0,sizeof(ContactInfo));
	}
	else
	{	
		/*Shift contacts up one position delete the last contact*/
		//Pointer to contact we want to delete and subsequent contact
    	curEntry = entry;
		nextEntry = entry+1;
		//Loop starting at serial number looping to the end of count
		for(; serialNum < address_book->count; serialNum++)
		{	
			//Copy serial num of current to next contact
			nextEntry->si_no = curEntry->si_no;
			//Copy next contact with updated serial number to current contact
			memcpy(curEntry, nextEntry, sizeof(ContactInfo));
			//Increment pointer 
			curEntry++;
			//Check before we increment nextEntry on the last iteration of loop 
			//we don't want to increment the pointer because it may point out of bounds
			if (nextEntry->si_no < address_book->count)
				nextEntry = curEntry + 1;
			//Increment loop checker
			serialNum++;
		}
		//Setting all fields equal to null for last contact
		memset(curEntry,0,sizeof(ContactInfo));
	}
	//Decrementing count to update total contact count
	address_book->count--;
	return e_success;

}
