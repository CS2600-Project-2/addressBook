#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"

//taken from stackOverflow: https://stackoverflow.com/questions/12911299/read-csv-file-in-c
const char* getfield(char* line, int num)
{
    const char* tok;
    for (tok = strtok(line, ",");
            tok && *tok;
            tok = strtok(NULL, ";\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

Status load_file(AddressBook *address_book)
{
	int ret;
	char fname[1024];

	//if there are no issues, access should return 0
	if(access(DEFAULT_FILE, F_OK) == 0 ){
		/* 
		 * Do the neccessary step to open the file
		 * Do error handling
		 */ 

		FILE* stream = fopen(DEFAULT_FILE, "r");
		char line[1024];
		while (fgets(line, 1024, stream))
		{
			//strdup means string duplicate. In this case, it duplicates the
			char* tmp = strdup(line);
			printf("Field 3 would be %s\n", getfield(tmp, 3));
			// NOTE strtok clobbers tmp
			free(tmp);
		}

		return e_success;
	}
	else
	{
		//if there is no file given, allocate 10 spaces and go back
		address_book = malloc(10 *sizeof(ContactInfo));
		return e_success;
	}

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
