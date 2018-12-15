/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschroed <mschroed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 15:23:19 by mschroed          #+#    #+#             */
/*   Updated: 2018/12/14 19:33:48 by mschroed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "get_next_line.h"

char	*strjoin_del(char *s1, char *s2, int num)
{
	char *new_str;

	new_str = ft_strjoin(s1, s2);
	if (num == 0)
	{
		ft_strdel(&s1);
		ft_strdel(&s2);
	}
	else if (num == 1)
		ft_strdel(&s1);
	else if (num == 2)
		ft_strdel(&s2);
	return (new_str);
}

int		f_read(const int fd, char **oflo)
{
	//char	*tmp;
	int		ret;
	char	*buf;

	buf = ft_strnew(BUFF_SIZE);
	if (!buf)
		return (-1);
	while(!ft_strchr(*oflo, '\n') && (ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		*oflo = strjoin_del(*oflo, buf, 1);
		ft_strclr(buf);
	}
	ft_strdel(&buf);
	if (ret < BUFF_SIZE)
		return (0);
	return (1);
}

int		f_oflo(char **oflo, char **line)
{
	int		i;

	i = strchri(*oflo, '\n');
	if (i == -1)
	{
		*line = ft_strdup(*oflo);
		ft_strclr(*oflo);
		return (0);
	}
	*line = ft_strnew(i);
	ft_memcpy(*line, *oflo, i);
	ft_memmove(*oflo, *oflo + i + 1, ft_strlen(*oflo) - i);
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char		*oflo[FD];
	int				read_stat;
	int				oflo_stat;

	if (fd < 0 || fd >= FD || line == NULL || read(fd, oflo[fd], 0) == -1)
		return (-1);
	if (!oflo[fd])
	{
		oflo[fd] = ft_strnew(BUFF_SIZE);
		if (!oflo[fd] && !*line)
			return (-1);
	}
	read_stat = f_read(fd, &oflo[fd]);
	oflo_stat = f_oflo(&oflo[fd], line);
	if (read_stat == 0 && oflo_stat == 0 && !**line)
	{
		ft_strdel(&oflo[fd]);
		return (0);
	}
	else
		return (1);
}
