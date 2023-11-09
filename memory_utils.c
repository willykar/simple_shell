#include "main.h"
/**
 * _memcpy - A function that copies information between pointers(void)
 * @newptr: the destination pointer.
 * @ptr: the source pointer.
 * @size: of the new pointer
 */
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int a;

	for (a = 0; a < size; a++)
		char_newptr[a] = char_ptr[a];
}

/**
 * _realloc - A function that reallocates a memory block
 * @ptr: a pointer to the previously allocated memory
 * @old_size: size of the allocated space of the pointer in bytes
 * @new_size: bytes of the new memory block
 * Return: (ptr) or NULL if malloc fails or
 * return ptr unchanged if new_size == old_size
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcpy(newptr, ptr, new_size);
	else
		_memcpy(newptr, ptr, old_size);

	free(ptr);
	return (newptr);
}

/**
 * _reallocdp - A function that reallocates a memory block of a double pointer
 * @ptr: A double pointer of the previously allocated  memory
 * @old_size: size of the allocated pointer in bytes.
 * @new_size: the size of the new memory block in bytes
 * Return: (ptr) (ptr) or NULL if malloc fails or
 * return ptr unchanged if new_size == old_size
 */
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int a;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for (a = 0; a < old_size; a++)
		newptr[a] = ptr[a];

	free(ptr);

	return (newptr);
}
