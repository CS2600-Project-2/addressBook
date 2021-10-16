#include <stdio.h>
// #include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>

#include "address_book.h"
#include "address_book_fops.h"
#include "address_book_menu.h"

int main(void)
{
	AddressBook address_book;
	Status ret;

	/* Load the file from .csv file if any */
	ret = load_file(&address_book);
	
	if (ret == e_success)
	{
		printf("WHOOOOOOOOOOOOOOOOOOOOOOOOOOO");
		/* Show all the available menu */
		ret = menu(&address_book);
		
		if (ret == e_success)
		{
			/* Save the entries*/
			save_prompt(&address_book);
		}
	}
}
/*
//Declare the variables

    int num;
	int c;

    // Input the integer

    printf("Enter the integer: ");

    scanf("%d", &num);
    // Display the integer

	printf("Entered integer is: %d", num);
    
	return 0;

//Code for Read a char

printf( "Enter a value :"); 
  	c = getchar( ); 
printf( "\nYou entered: ");
   putchar( c ); return 0; 
	
	return 0;*/


