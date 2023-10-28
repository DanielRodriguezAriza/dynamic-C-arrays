# Simple Dynamic Arrays in C

## Introduction
A simple generic dynamic array (also known as vector) implementation made in C.

## Features: Overview
- **Generic Dynamic Array struct:** A simple struct that allows you to create dynamic arrays that contain any data type.
- **Helper functions and macros**: A set of functions and macros to declare dynamic arrays and push elements into it.
- **Operations by element:** Perform operations by element on the vector. Will use the datatype which you defined for the vector.
- **Operations by type:** Perform operations by type on the vector. Ignore the data type originally defined for the vector and pack data of any type into it as you see fit.

## Features: Specific functions and macros
- **dynamic_array(type):** Create a dynamic array that stores elements of the datatype "type".
- **dynamic_array_allocate_elements(arr,count):** Allocate memory for a new dynamic array. Allocates enough bytes to store "count" elements of the data type for which the vector was defined.
- **dynamic_array_allocate_elements_by_type(arr,type,count):** Allocate memory for a new dynamic array. Allocates enough bytes to store "count" elements of the data type "type".
- **dynamic_array_get_element_at(arr, idx):** Retrieve the element at the index "idx". The return type of the element is the data type for which the array was defined.
- **dynamic_array_get_element_at_by_type(arr, type, idx):** Retrieve the element at the index "idx", reinterpreting the dynamic array's data as a buffer of elements of type "type".
- **dynamic_array_push_element(arr, elem):** Pushes an element of the type for which the vector was defined into the array. If there is not enough memory allocated, it attemps a memory reallocation.
- **dynamic_array_push_element_by_type(arr,type,elem):** Pushes an element of the type "type" into the array. If there is not enough memory allocated, it attempts a memory reallocation.
- **dynamic_array_get_length(arr):** Returns the length of the array, with the number of elements of the type for which the vector was defined that are currently stored inside of the array.
- **dynamic_array_get_length_by_type(arr, type):** Returns the length of the array, with the number of elements of the type "type" that are currently stored inside of the array.
- **dynamic_array_get_capacity(arr):** Returns the capacity of the array, with the number of elements of the type for which the vector was defined that can currently fit inside of the allocated memory.
- **dynamic_array_get_capacity_by_type(arr, type):** Returns the capacity of the array, with the number of elements of the type "type" that can currently fit inside of the allocated memory.
- **dynamic_array_resize(arr, new_size):** Resizes the dynamic array to fit the new size. Old elements are conserved.
- **dynamic_array_get_capacity_by_type(arr, type):** Resizes the dynamic array to fit the new size. Old elements are conserved. Reinterprets the dynamic array as one that contains elements of the specified type.

## Usage
Include the header file in your code (```#include "dynamic_array.h```). It's as simple as that.

## Implementation details
It is common for vectors to be implemented by storing a pointer to a certain datatype, a length which stores the number of stored elements and a capacity which stores the number of elements that the currently allocated memory segment can store.

In the case of this vector implementation, instead of storing the number of elements in the legnth and capacity variables, what is stored is the number of bytes. The reason why it is implemented in this unconventional manner is because this dynamic vector implementation allows users to pack any data type they want in the vector, if they desire to do so.