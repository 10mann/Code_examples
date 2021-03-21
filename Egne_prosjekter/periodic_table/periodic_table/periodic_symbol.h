#ifndef PERIODIC_SYMBOL_H
#define PERIODIC_SYMBOL_H

#include <stdio.h>

#define SYMBOL_NAME_MAX_LENGTH 48
#define DEGREES_ASCRII_CHAR 248

// Struct used to define an element
typedef struct
{
	char name[SYMBOL_NAME_MAX_LENGTH];
	char symbol[3];
	int atomic_number;
	float atomic_weight;
	float density;
	float boiling_temp;
	float freezing_temp;
} periodic_element_t;

void print_rect();
void print_element(periodic_element_t* symbol);
void add_element(periodic_element_t* symbols, unsigned int* length);
void print_elements_menu(periodic_element_t* symbols, unsigned int length);
void edit_element(periodic_element_t* element);
#endif