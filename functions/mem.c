#include "main.h"

/**
 * _memcpy - copies information between void pointers.
 * @new: new pointer.
 * @ptr: original pointer.
 * @size: size of the new pointer
 *
 * Return: void
 */
void _memcpy(void *new, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_new = (char *)new;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_new[i] = char_ptr[i];
}

/**
 * _realloc - allocates a new block of memory
 * @ptr: pointer to the previously allocated memory
 * @current: size of the allocated space of memory
 * @update: new size, in bytes, of the new memory block.
 *
 * Return: pointer to the allocated space
 */
void *_realloc(void *ptr, unsigned int current, unsigned int update)
{
	void *new;

	if (ptr == NULL)
		return (malloc(update));

	if (update == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (update == current)
		return (ptr);

	new = malloc(update);
	if (new == NULL)
		return (NULL);

	if (update < current)
		_memcpy(new, ptr, update);
	else
		_memcpy(new, ptr, current);

	free(ptr);
	return (new);
}

/**
 * _reallocdp - _realloc for double pointers
 * @ptr: double pointer to the previously allocated memory
 * @current: size of the allocated space of ptr
 * @update: new size of the new memory block
 *
 * Return: pointer to the newly allocated space
 */
char **_reallocdp(char **ptr, unsigned int current, unsigned int update)
{
	char **new;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * update));

	if (update == current)
		return (ptr);

	new = malloc(sizeof(char *) * update);
	if (new == NULL)
		return (NULL);

	for (i = 0; i < current; i++)
		new[i] = ptr[i];

	free(ptr);

	return (new);
}
