/*
	Example usage of the dynamic_array's functionality.
*/

#include <stdio.h>
#include "dynamic_array.h"

void print_all(void *arrin)
{
	dynamic_array(int) *arr = arrin;
	printf("arr (len = %zu, cap = %zu) = [ ", dynamic_array_get_length(arr), dynamic_array_get_capacity(arr));
	for (size_t i = 0; i < dynamic_array_get_length(arr); ++i)
	{
		printf("%d ", dynamic_array_get_element_at(arr, i));
	}
	printf("]\n");
}

int main()
{
	dynamic_array(int) arr;
	dynamic_array_allocate_elements(&arr, 10);

	dynamic_array_push_element(&arr, 10);
	dynamic_array_push_element(&arr, 20);
	dynamic_array_push_element(&arr, 30);
	dynamic_array_push_element(&arr, 40);
	dynamic_array_push_element(&arr, 50);
	dynamic_array_push_element(&arr, 60);
	dynamic_array_push_element(&arr, 70);
	dynamic_array_push_element(&arr, 80);
	dynamic_array_push_element(&arr, 90);
	dynamic_array_push_element(&arr, 100);
	dynamic_array_push_element(&arr, 110);
	
	print_all(&arr);
	
	dynamic_array_push_element_by_type(&arr,unsigned char,255);
	dynamic_array_push_element_by_type(&arr,unsigned char,255);
	dynamic_array_push_element_by_type(&arr,unsigned char,255);
	dynamic_array_push_element_by_type(&arr,unsigned char,255);
	
	dynamic_array_resize(&arr, 5);
	dynamic_array_resize(&arr, 10);
	
	dynamic_array_push_element(&arr, 69);
	dynamic_array_push_element(&arr, 420);
	dynamic_array_push_element(&arr, 34);
	dynamic_array_push_element(&arr, 6969);
	dynamic_array_push_element(&arr, 1138);
	dynamic_array_push_element(&arr, 42);
	dynamic_array_push_element(&arr, 88);
	dynamic_array_push_element(&arr, 1);
	dynamic_array_push_element(&arr, 2);
	dynamic_array_push_element(&arr, 3);
	dynamic_array_push_element(&arr, 4);
	dynamic_array_push_element(&arr, 5);
	dynamic_array_push_element(&arr, 6);
	dynamic_array_push_element(&arr, 7);
	dynamic_array_push_element(&arr, 8);
	dynamic_array_push_element(&arr, 9);
	dynamic_array_push_element(&arr, 10);
	
	printf("This array can fit %zu bytes.\n", dynamic_array_get_capacity_by_type(&arr,char));
	printf("arr (len = %zu, cap = %zu) = [ ", dynamic_array_get_length(&arr), dynamic_array_get_capacity(&arr));
	for (size_t i = 0; i < dynamic_array_get_length(&arr); ++i)
	{
		printf("%d ", dynamic_array_get_element_at(&arr, i));
	}
	printf("]\n");


	return 0;
}
