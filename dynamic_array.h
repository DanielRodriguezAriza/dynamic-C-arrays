#ifndef DRA_DYNAMIC_ARRAY_H
#define DRA_DYNAMIC_ARRAY_H

#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

#define dynamic_array(type) struct {type *data; size_t length, capacity;}


typedef dynamic_array(char) d_arr;
typedef dynamic_array(char) *d_arr_ptr;

typedef dynamic_array(int8_t) d_arr_i8;
typedef dynamic_array(uint8_t) d_arr_u8;

typedef dynamic_array(int16_t) d_arr_i16;
typedef dynamic_array(uint16_t) d_arr_u16;

typedef dynamic_array(int32_t) d_arr_i32;
typedef dynamic_array(uint32_t) d_arr_u32;

typedef dynamic_array(int64_t) d_arr_i64;
typedef dynamic_array(uint64_t) d_arr_u64;

typedef dynamic_array(float) d_arr_f32;
typedef dynamic_array(double) d_arr_f64;


void dynamic_array_set_info(void *arr, void *ptr, size_t len, size_t cap);
void dynamic_array_init(void *arr); /* used to initialize dynamic as empty arrays and make the first dynamic memory allocation when performing the first push operation */

int dynamic_array_allocate_bytes(void *arr, size_t bytes);
void dynamic_array_deallocate(void *arr);

int dynamic_array_reallocate(void *arr, size_t new_cap);
int dynamic_array_has_to_reallocate(void *arr);

#define dynamic_array_allocate_elements_by_type(arr,type,count) dynamic_array_allocate_bytes(arr,sizeof(type) * count)

#define dynamic_array_allocate_elements(arr,count) dynamic_array_allocate_bytes(arr,sizeof(((*arr).data[0])) * count)



#define dynamic_array_get_element_at(arr, idx) ((*arr).data[idx])
#define dynamic_array_get_element_at_by_type(arr, type, idx) (((type*)((*arr).data))[idx])

/* redundant macros that exist for eyecandy */
#define dynamic_array_get_element(arr, idx) dynamic_array_get_element_at(arr, idx)
#define dynamic_array_get_element_by_type(arr, type, idx) dynamic_array_get_element_at_by_type(arr, type, idx)



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

#define dynamic_array_get_data_pointer(arr) ((arr)->data)
#define dynamic_array_get_data_pointer_by_type(arr, type) ((type*)((arr)->data))



#ifdef DRA_DYNAMIC_ARRAY_IMPL

void dynamic_array_set_info(void *arr, void *ptr, size_t len, size_t cap)
{
	((d_arr_ptr)(arr))->data = ptr;
	((d_arr_ptr)(arr))->length = len;
	((d_arr_ptr)(arr))->capacity = cap;
}

void dynamic_array_init(void *arr)
{
	dynamic_array_set_info(arr,NULL,0,0);
}

int dynamic_array_allocate_bytes(void *arr, size_t bytes)
{
	void *tmp = (void*)calloc(bytes, 1);
	dynamic_array_set_info(arr, tmp, 0, tmp == NULL? 0 : bytes);
	return tmp == NULL;
}

void dynamic_array_deallocate(void *arr)
{
	free(((d_arr_ptr)(arr))->data);
	dynamic_array_set_info(arr,NULL,0,0);
}

int dynamic_array_reallocate(void *arr, size_t new_cap)
{
	void *temp_ptr = realloc(((d_arr_ptr)(arr))->data, new_cap);
	if(temp_ptr == NULL)
	{
		return 1;
	}
	((d_arr_ptr)(arr))->data = temp_ptr;
	((d_arr_ptr)(arr))->capacity = new_cap;
	if(((d_arr_ptr)(arr))->length > ((d_arr_ptr)(arr))->capacity)
	{
		((d_arr_ptr)(arr))->length = ((d_arr_ptr)(arr))->capacity;
	}
	return 0;
}

int dynamic_array_has_to_reallocate(void *arr)
{
	return (((d_arr_ptr)(arr))->length >= ((d_arr_ptr)(arr))->capacity) || (((d_arr_ptr)(arr))->capacity == 0);
}

#endif /* DRA_DYNAMIC_ARRAY_IMPL */


#endif /* DRA_DYNAMIC_ARRAY_H */
