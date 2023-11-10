#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	size_t n = 0;
	char *buffer = 0;

	printf("root$ ");
	getline(&buffer, &n, stdin);
	printf("%s", buffer);

	free(buffer);
	return (0);
}
