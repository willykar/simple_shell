#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char str[100];
	int i = 0;
	char *buffer = NULL;
	size_t n = 0;
	size_t l;
	char delim[] = " ";
	char *trunks;

	printf("$: ");
	if((getline(&buffer, &n, stdin)) == -1)
	{
		perror("getline");
		exit(EXIT_FAILURE);
	}
	l = strlen(buffer);
	if (l > 0 && buffer[l -1] == '\n')
	{
		buffer[l -1] = '\0';
	}

	snprintf(str, sizeof(str), "%s", buffer);
	trunks = strtok(str, delim);
	while (trunks != NULL)
	{
		printf("%s\n", trunks);
		trunks = strtok(NULL, delim);
	}
	for (i = 0; i < l - 1; i++)
	{
		if (str[i] == '\0')
			printf("\\0");
		else
			printf("%c", str[i]);
	}
	return (0);
}
