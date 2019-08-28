/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 16:24:35 by jfelty            #+#    #+#             */
/*   Updated: 2019/08/28 13:39:06 by jfelty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <malloc/malloc.h>

int	ft_gnl(char **str, char **line, int fd)
{
	char *next;

	if (!(next = ft_strchr(str[fd], '\n')))
	{
		if (!*str[fd])
			return (0);
		*line = ft_strdup(str[fd]);
		str[fd] += ft_strlen(str[fd]);
		return (1);
	}
	next++;
	*line = ft_strsub(str[fd], 0, next - str[fd] - 1);
	str[fd] = next;
	return (1);
}

int	get_next_line(int const fd, char **line)
{
	int ret;
	char buff[BUFF_SIZE + 1];
	static char *str[4096];
	char *tmp;

	if (!line || fd < 0)
		return (-1);
	if (str[fd] == NULL)
	{
		while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
		{
			if (!str[fd])
				str[fd] = ft_strnew(1);
			buff[ret] = '\0';
			tmp = ft_strjoin(str[fd], buff);
			free(str[fd]);
			str[fd] = tmp;
		}
		tmp = NULL;
		free(tmp);
		if (ret < 0)
			return (-1);
	}
	return(ft_gnl(&*str, &*line, fd));
}


int	main(int ac, char **av)
{
    int fd;
	int tst;
	char *str;

    if (ac != 2)
	{
		ft_putstr("Usage: ./a.out test");
		return (0);
	}
	fd = open(av[1], O_RDONLY);

	while ((tst = get_next_line(fd, &str)) > 0)
	{
		printf("ret: %d: %s\n", tst, str);
		free(str);
	}
	return (0);
}
