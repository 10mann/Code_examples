#include "save_file.h"

#define FILE_READ_SUCCESS 0
#define FILE_READ_ERROR -1


void save_elements_to_file(char* file_name, periodic_element_t* elements, unsigned int number_of_elements)
{
	FILE* save_file = fopen(file_name, "w");

	fprintf(save_file, "%i\n", number_of_elements);

	for (int i = 0; i < number_of_elements; ++i)
	{
		fprintf(save_file, "%s %s %i %0.3f %0.3f %0.1f %0.1f\n",
			elements[i].name, elements[i].symbol, elements[i].atomic_number,
			elements[i].atomic_weight, elements[i].density, elements[i].boiling_temp,
			elements[i].freezing_temp);
	}

	fclose(save_file);

}

void load_elements_from_file(char* file_name, periodic_element_t* elements, unsigned int* number_of_elements)
{
	FILE* save_file = fopen(file_name, "r");
	if (save_file == NULL)
	{
		return;
	}
	
	(void)fscanf(save_file, "%i", number_of_elements);

	for (int i = 0; i < (*number_of_elements); ++i)
	{
		(void)fscanf(save_file, "%s %s %i %f %f %f %f",
			elements[i].name, elements[i].symbol, &elements[i].atomic_number,
			&elements[i].atomic_weight, &elements[i].density, &elements[i].boiling_temp,
			&elements[i].freezing_temp);
	}

	fclose(save_file);
}