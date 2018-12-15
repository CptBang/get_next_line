#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"
#include "get_next_line.h"
#define FD_MAX 5000

char	*ft_fstrjoin(char *s1, char *s2, int num)
{
	char *retval;

	retval = ft_strjoin(s1, s2);
	if (num == 0)
	{
		ft_strdel(&s1);
		ft_strdel(&s2);
	}
	else if (num == 1)
		ft_strdel(&s1);
	else if (num == 2)
		ft_strdel(&s2);
	return (retval);
}

static int	read_next_line(const int fd, char **thread)
{
	char	*buf;
	size_t	status;

	buf = ft_strnew(BUFF_SIZE);
	if (!buf)
		return (-1);
	status = 0;
	while (!ft_strchr(*thread, '\n') && (status = read(fd, buf, BUFF_SIZE)) > 0)
	{
		*thread = ft_fstrjoin(*thread, buf, 1);
		ft_strclr(buf);
	}
	ft_strdel(&buf);
	if (status < BUFF_SIZE)
		return (0);
	return (1);
}

static int	grab_line(char **thread, char **line)
{
	int	i;

	i = strchri(*thread, '\n');
	if (i == -1)
	{
		*line = ft_strdup(*thread);
		ft_strclr(*thread);
		return (0);
	}
	*line = ft_strnew(i);
	ft_memcpy(*line, *thread, i);
	ft_memmove(*thread, *thread + i + 1, ft_strlen(*thread) - i);
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static char	*threads[FD_MAX];
	size_t		status;
	size_t		readstatus;

	if (fd < 0 || fd >= FD_MAX)
		return (-1);
	if (read(fd, threads[fd], 0) == -1)
		return (-1);
	if (line == NULL)
		return (-1);
	if (!threads[fd])
	{
		threads[fd] = ft_strnew(BUFF_SIZE);
		if (!threads[fd] && !*line)
			return (-1);
	}
	readstatus = read_next_line(fd, &threads[fd]);
	status = grab_line(&threads[fd], line);
	if (readstatus == 0 && status == 0 && !**line)
	{
		ft_strdel(&threads[fd]);
		return (0);
	}
	else
		return (1);
}