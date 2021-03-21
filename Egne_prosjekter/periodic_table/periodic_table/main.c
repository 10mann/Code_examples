#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "periodic_symbol.h"
#include "save_file.h"

#define MAX_LIST_SIZE 200
#define SAVE_FILE_NAME "save_file.txt"

//unsigned int number_of_elements = 0;

// Check if user input is valid, must be integer value
// Valid inputs are between dec 48 and dec 57, ie. '0' - '9'
// Negative integers are not allowed
bool valid_input(char* input, int length)
{
	for (int i = 0; i < length; ++i)
	{
		if (input[i] < 48 || input[i] > 57)
		{
			return false;
		}
	}

	return true;
}

// Very simple string to integer conversion, needed because of user input check
// The user can only input positive integers and the conversion is therefore easy to do
int string_to_int(char* input, int length)
{
	int number = input[length - 1] - 48;

	for (int i = 1; i < length; ++i)
	{
		int temp = input[length - i - 1] - 48;
		for (int j = 0; j < i; ++j)
		{
			temp *= 10;
		}

		number += temp;
	}

	return number;
}

// Calculates the length of a string by finding the null terminating character: '\0'
int string_length(char* string)
{
	int i;

	for (i = 0; string[i] != '\0'; ++i) {}

	return i;
}

//periodic_symbol_t helium =
//{
//	"Helium",
//	"He",
//	2,
//	4.0026,
//	0.1785,
//	-269,
//	0
//};

int main()
{
	// Init variables
	char user_input[5] = { 0 };
	periodic_element_t test[MAX_LIST_SIZE];
	unsigned int number_of_elements = 0;

	// Init list of elements from file
	load_elements_from_file(SAVE_FILE_NAME, test, &number_of_elements);

	for (;;)
	{
		int input = -1;
		//printf("0. Show Elements\n1. Add Element\n2. Exit\n");
		printf("\n");
		print_elements_menu(test, number_of_elements);
		printf("%i. Add element\n", number_of_elements);
		printf("%i. Exit\n", number_of_elements + 1);
		(void)scanf("%s", user_input);
		int string_len = string_length(user_input);

		if (!valid_input(user_input, string_len))
		{
			printf("Must enter integer value\n");
		}
		else
		{
			input = string_to_int(user_input, string_len);

			if (input < number_of_elements)
			{
				//print_element(&test[input]);
				edit_element(&test[input]);

			}
			else if (input == number_of_elements)
			{
				add_element(test, &number_of_elements);
			}
			else 
			{
				break;
			}
		}
	}

	save_elements_to_file(SAVE_FILE_NAME, test, number_of_elements);
	return 0;
}


