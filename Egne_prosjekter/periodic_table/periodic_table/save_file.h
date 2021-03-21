#ifndef SAVE_FILE_H
#define SAVE_FILE_H

#include <stdio.h>

#include "periodic_symbol.h"


void save_elements_to_file(char* file_name, periodic_element_t* elements, unsigned int number_of_elements);
void load_elements_from_file(char* file_name, periodic_element_t* elements, unsigned int* number_of_elements);
#endif