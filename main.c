
#include "libft.h"
#include "get_next_line.h"

/*
int	main(void)
{
	int		fd;
	char	*arr = "err";


	if ((fd = open("butts.txt", O_RDONLY)) == -1)
		return (0);
	printf("read is: %d\n", get_next_line(fd, &arr));
	printf("string is:\n%s\n", arr);
	free(arr);
	printf("read is: %d\n", get_next_line(fd, &arr));
	printf("string is:\n%s\n", arr);
	free(arr);
	printf("read is: %d\n", get_next_line(fd, &arr));
	printf("string is:\n%s\n", arr);
	free(arr);
	printf("read is: %d\n", get_next_line(fd, &arr));
	printf("string is:\n%s\n", arr);
	free(arr);
	close(fd);
	printf("read is: %d\n", get_next_line(fd, &arr));
	printf("string is:\n%s\n", arr);
	//free(arr);
	return (0);
}*/



/*
** 2 lines via STDIN with 8 chars without Line Feed
*/

int				main(void)
{
	char		*line;
	int			fd;
	int			ret;
	int			count_lines;
	int			errors;

	fd = 0;
	count_lines = 0;
	errors = 0;
	line = NULL;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (count_lines == 0 && strcmp(line, "1234567") != 0)
			errors++;
		if (count_lines == 1 && strcmp(line, "abcdefgh") != 0)
			errors++;
		count_lines++;
		if (count_lines > 50)
			break ;
	}
	if (count_lines != 2)
		printf("-> must have returned '1' twice instead of %d time(s)\n", count_lines);
	if (errors > 0)
		printf("-> must have read \"1234567\" and \"abcdefgh\"\n");
	if (count_lines == 2 && errors == 0)
		printf("OK");
	return (0);
}
