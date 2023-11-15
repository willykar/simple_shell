/**
 * error_path_126 - A function that gives an error message
 * for the path and failure
 * @datas: data
 * Return: (error string)
 */
char *error_path_126(data_s *datas)
{
	int length;
	char *ver_str;
	char *error;

	ver_str = aux_itoa(datas->counter);
	length = _strlength(datas->argv[0]) + _strlength(ver_str);
	length += _strlength(datas->args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (error == NULL)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, datas->argv[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datas->args[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}
