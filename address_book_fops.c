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
	char buff[500];
	ContactInfo *contactNum;
	address_book->list = malloc(10 *sizeof(ContactInfo));
	contactNum = address_book->list;
	ret = access(DEFAULT_FILE, F_OK);
	int i = 0;
	address_book->count = 0;

	//if there are no issues, access should return 0
	if(ret == 0 ){
		/* 
		 * Do the neccessary step to open the file
		 * Do error handling
		 */
		address_book->fp = fopen(DEFAULT_FILE, "r");
		while(1)
		{
			if(fgets(buff, sizeof(buff), address_book->fp) != NULL)
			{
				contactNum->si_no = atoi(buff);
			}
			else
			{
				break;
			}
			if(fgets(buff, sizeof(buff), address_book->fp) != NULL)
			{
			    address_book->count++;
			    contactNum++;
			}
			else
			{
				break;
			}
		}
	}
	
	else
	{
		/*Create a file for adding entries*/
		address_book->fp = fopen(DEFAULT_FILE, "a");
	}

	fclose(address_book->fp);
	free(address_book->list);
	return e_success;
}

Status save_file(AddressBook *address_book)
{
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

	fclose(address_book->fp);

	return e_success;
}
