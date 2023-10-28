#ifndef DRA_DYNAMIC_ARRAY_H
#define DRA_DYNAMIC_ARRAY_H

#include <stdio.h>
#include <stdlib.h>

#define dynamic_array(type) struct {type *data; size_t length, capacity;}

#define ARR_CAST_PTR(type, x) ((dynamic_array(type)*)(x))

void dynamic_array_set_info(void *arr, void *ptr, size_t len, size_t cap)
{
	ARR_CAST_PTR(void,arr)->data = ptr;
	ARR_CAST_PTR(void,arr)->length = len;
	ARR_CAST_PTR(void,arr)->capacity = cap;
}

int dynamic_array_allocate_bytes(void *arr, size_t bytes)
{
	void *tmp = (void*)calloc(bytes, 1);
	dynamic_array_set_info(arr, tmp, 0, tmp == NULL? 0 : bytes);
	return tmp == NULL;
}

#define dynamic_array_allocate_elements_by_type(arr,type,count) dynamic_array_allocate_bytes(arr,sizeof(type) * count)

#define dynamic_array_allocate_elements(arr,count) dynamic_array_allocate_bytes(arr,sizeof(((*arr).data[0])) * count)

void dynamic_array_deallocate(void *arr)
{
	free(ARR_CAST_PTR(void,arr)->data);
	dynamic_array_set_info(arr,NULL,0,0);
}

#define dynamic_array_get_element_at(arr, idx) ((*arr).data[idx])
#define dynamic_array_get_element_at_by_type(arr, type, idx) (((type*)((*arr).data))[idx])

int dynamic_array_reallocate(void *arr, size_t new_cap) //maybe rename to _reallocate_bytes?
{
	void *temp_ptr = realloc(ARR_CAST_PTR(void, arr)->data, new_cap);
	if(temp_ptr == NULL)
	{
		return 1;
	}
	ARR_CAST_PTR(void,arr)->data = temp_ptr;
	ARR_CAST_PTR(void,arr)->capacity = new_cap;
	if(ARR_CAST_PTR(void,arr)->length > ARR_CAST_PTR(void,arr)->capacity)
	{
		ARR_CAST_PTR(void,arr)->length = ARR_CAST_PTR(void,arr)->capacity;
	}
	return 0;
}

int dynamic_array_has_to_reallocate(void *arr)
{
	return ARR_CAST_PTR(void, arr)->length >= ARR_CAST_PTR(void, arr)->capacity;
}


#define dynamic_array_push_internal(arr, elem) ((arr)->data[dynamic_array_get_length(arr)] = (elem), (arr)->length += sizeof(((arr)->data)[0]),  0)

#define dynamic_array_push_element(arr, elem)\
(dynamic_array_has_to_reallocate((arr)) ? (dynamic_array_reallocate((arr), (arr)->capacity * 2) == 0 ? dynamic_array_push_internal((arr), (elem)) : 1 ) : dynamic_array_push_internal((arr), (elem)))


#define dynamic_array_get_length(arr) (((arr)->length) / sizeof(((arr)->data)[0]))
#define dynamic_array_get_capacity(arr) (((arr)->capacity) / sizeof(((arr)->data)[0]))

#define dynamic_array_get_length_by_type(arr, type) (((arr)->length) / sizeof(type))
#define dynamic_array_get_capacity_by_type(arr, type) (((arr)->capacity) / sizeof(type))

#define dynamic_array_push_element_by_type(arr,type,elem)\
(dynamic_array_push_element(((dynamic_array(type) *) (arr)), elem))

#define dynamic_array_resize(arr, new_size) dynamic_array_reallocate((arr), new_size * sizeof( ((arr)->data)[0] ))

#define dynamic_array_resize_by_type(arr, type, new_size) dynamic_array_reallocate((arr), new_size * sizeof(type))

#endif
