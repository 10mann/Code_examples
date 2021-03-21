#include "periodic_symbol.h"



void print_rect()
{
	char rect[5][10] =
	{
		"+--------+",
		"|        |",
		"|        |",
		"|        |",
		"+--------+"
	};

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			printf("%c", rect[i][j]);
		}
		printf("\n");
	}
}

// Function for printing element information
void print_element(periodic_element_t* element)
{
	printf("\n%s\n\tSymbol: %s\n\tAtomic number: %i\n\tAtomic weight: %0.3fu\n\tDensity: %0.3fkg/m^3\n\tBoiling temperature: %0.1f%cC\n\tFreezing temperature: %0.1f%cC\n\n", 
		element->name, element->symbol, element->atomic_number, element->atomic_weight, element->density, element->boiling_temp, DEGREES_ASCRII_CHAR, element->freezing_temp, DEGREES_ASCRII_CHAR);
}

void add_element(periodic_element_t* symbols, unsigned int* length)
{
	char symbol_name[SYMBOL_NAME_MAX_LENGTH];
	printf("Enter name of element\n");
	(void)scanf("%s", symbol_name);

	strcpy(symbols[(*length)].name, symbol_name);
	strcpy(symbols[(*length)].symbol, "");
	symbols[(*length)].atomic_number = -1;
	symbols[(*length)].atomic_weight = 0;
	symbols[(*length)].density = 0;
	symbols[(*length)].boiling_temp = 0;
	symbols[(*length)].freezing_temp = 0;
	//printf("Element added: %s\n", symbol_name);

	(*length)++;
}

void print_elements_menu(periodic_element_t* symbols, unsigned int length)
{
	for (unsigned int i = 0; i < length; ++i)
	{
		printf("%i. %s\n", i, symbols[i].name);
	}
}

void edit_element(periodic_element_t* element)
{
	int input = -1;
	char input_string[SYMBOL_NAME_MAX_LENGTH];
	int input_integer;
	float input_float;

	for (;;)
	{
		input = -1;
		print_element(element);
		
		printf("\nWhat do you want to edit?\n0. Name\n1. Symbol\n2. Atomic number\n3. Atomic weight\n4. Density\n5. Boiling temperature\n6. Freezing temperature\n7. Back\n");
		(void)scanf("%d", &input);

		switch (input)
		{
		case 0:
			printf("Enter new name\n");
			(void)scanf("%s", input_string);
			strcpy(element->name, input_string);
			break;

		case 1:
			printf("Enter new symbol\n");
			(void)scanf("%s", input_string);
			strcpy(element->symbol, input_string);
			break;

		case 2:
			printf("Enter atomic number\n");
			(void)scanf("%i", &input_integer);
			element->atomic_number = input_integer;
			break;

		case 3:
			printf("Enter atomic weight\n");
			(void)scanf("%f", &input_float);
			element->atomic_weight = input_float;
			break;

		case 4: 
			printf("Enter density\n");
			(void)scanf("%f", &input_float);
			element->density = input_float;
			break;

		case 5:
			printf("Enter boiling temperature\n");
			(void)scanf("%f", &input_float);
			element->boiling_temp = input_float;
			break;

		case 6:
			printf("Enter freezing temperature\n");
			(void)scanf("%f", &input_float);
			element->freezing_temp = input_float;
			break;

		case 7:
			return;
		}
	}
}