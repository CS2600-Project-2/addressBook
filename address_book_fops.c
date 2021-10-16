#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"

Status load_file(AddressBook *address_book)
{
	int ret;
	//we will use this for loops
	int i = 0;
	//buffers to store entire string
	char buff[500];
	//buffer that will be altered to desired field we store
	char workBuff[500],
	//pointers that will help us with string manipulation
	*ch, *chInbuff;

	//Allocating dynamic memory for the default 20 contacts
	address_book->list = malloc(MAX_CONTACTS *sizeof(ContactInfo));
	//Pointer of type contact pointing to the first contact
	ContactInfo *contactNum;
	contactNum = address_book->list;
	//Initialize count to 0
	address_book->count = 0;

	//if there are no issues, access should return 0
	ret = access(DEFAULT_FILE, F_OK);

	//file reading
	if(ret == 0 ){
		/* 
		 * Do the neccessary step to open the file
		 * Do error handling
		 */
		address_book->fp = fopen(DEFAULT_FILE, "r");
		//Read all lines from csv and store into ContactInfo struct
		while(1)
		{
			//Odd lines are serial numbers 
			//Break from loop if there is nothing to read
			if(fgets(buff, sizeof(buff), address_book->fp) != NULL)
			{
				contactNum->si_no = atoi(buff);
			}
			else
			{
				//Exit loop if there is no input
				break;
			}

			//Even lines will have fields name, phonenumbers, emailaddresses
			if(fgets(buff, sizeof(buff), address_book->fp) != NULL)
			{
				//Take original string and store name field in workBuff
				strcpy(workBuff, buff);
				//Pointer to the first occurance of ','
				ch = strchr(workBuff, ',');
				//Clear ',' and subsequent characters from workBuff
				if (ch)
					*ch = 0;
				//Copy the string int name component of ContactInfo struct
				strcpy(&contactNum->name[0][0], workBuff);
				
				//Saving phone numbers to ContactInfo struct
				//Setting chInbuff pointer to first char in buff(original string)
				chInbuff = buff;
				for(i = 0; i < 5; i++)
				{	
					//chInbuff points to index of the first character after ','
					chInbuff = strchr(chInbuff, ',');
					if (chInbuff)
						chInbuff++;
					//Copy new string with the previous field removed
					strcpy(workBuff,chInbuff);
					//Find first occurrence of ',' clear ',' and subsequent characters
					ch = strchr(workBuff, ',');
					if(ch)
						*ch = 0;
					//Copy the string into phone_number compnent of ContactInfo struct
					strcpy(&contactNum->phone_numbers[i][0], workBuff);
				}

				//Saving email addresses to ContactInfo struct
				for(i = 0; i < 5; i++)
				{
					//chInbuff points to index of the first character after ','
					chInbuff = strchr(chInbuff, ',');
					if (chInbuff)
						chInbuff++;
					//Copy new string with the previous field removed
					strcpy(workBuff,chInbuff);
					//Find first occurrence of ',' clear ',' and subsequent characters
					ch = strchr(workBuff, ',');
					if(ch)
						*ch = 0;
					//Copy the string into email_addresses compnent of ContactInfo struct
					strcpy(&contactNum->email_addresses[i][0], workBuff);
				}

				//Increase count of contacts
			    address_book->count++;
				//Move pointer to the next contact
			    contactNum++;
			}
			else
			{
				//Exit loop if there is no input
				break;
			}
		}
	}

	else
	{
		/*Create a file for adding entries*/
		address_book->fp = fopen(DEFAULT_FILE, "a");
	}

	//close file
	fclose(address_book->fp);
	return e_success;
}

Status save_file(AddressBook *address_book)
{
	//Pointer of type contact pointing to the first contact
	ContactInfo *contactNum;
	contactNum = address_book->list;
	//We will use this to loop through contacts
	int currentEntry;
	int totalEntries = address_book->count;
	//We will use these to loop through phone_numbers and email_addresses
	int phoneCount, emailCount;

	/*
	 * Write contacts back to file.
	 * Re write the complete file currently
	 */ 
	address_book->fp = fopen(DEFAULT_FILE, "w");

	if (address_book->fp == NULL)
	{
		return e_fail;
	}

	/* 
	 * Add the logic to save the file
	 * Make sure to do error handling
	 */ 
	//saving the contact info  back to csv file
	for(currentEntry = 0; currentEntry<totalEntries; currentEntry++)
	{
		//writing the serial number and newline 
		fprintf(address_book->fp, "%d\n", contactNum->si_no);
		//writing the name
		fprintf(address_book->fp, "%s,", &contactNum->name[0][0]);

		//writing phone numbers
		for(phoneCount = 0; phoneCount < 5; phoneCount++)
		{
			//if there is no phonenumber don't write
			if(&contactNum->phone_numbers[phoneCount][0]!=NULL)
			{
				fprintf(address_book->fp, "%s", &contactNum->phone_numbers[phoneCount][0]);
			}
			fprintf(address_book->fp,",");
		}

		//writing emails
		for(emailCount = 0; emailCount < 5; emailCount++)
		{
			if(&contactNum->email_addresses[emailCount][0]!=NULL)
			{
				//if there is no email don't write
				fprintf(address_book->fp, "%s", &contactNum->email_addresses[emailCount][0]);
			}
			fprintf(address_book->fp,",");
		}
		//new line for next contact 
		//don't print if it is last contact to be printed
		if(currentEntry<address_book->count-1)
		{
			fprintf(address_book->fp,"\n");
		}
		//move to the next contact
		contactNum++;

	}

	//close file
	fclose(address_book->fp);
	return e_success;
}
