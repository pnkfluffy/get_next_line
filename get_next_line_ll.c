/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_ll.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 09:57:19 by jfelty            #+#    #+#             */
/*   Updated: 2019/09/08 16:25:19 by jfelty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void    ft_cleanlist(t_fdlist *start, t_fdlist *curr)
{
    t_fdlist    *finder;

    finder = start;
    if (finder != curr)
        while (finder->next != curr)
            finder = finder->next;
    finder->next = curr->next;
    free(curr);
}

int        populate(t_fdlist *curr, int fd)
{
    int        ret;
    char    buff[BUFF_SIZE + 1];
    char    *tmp = NULL;

    curr->descriptor = fd;
    curr->content = ft_strnew(1);
    curr->next = NULL;
    while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
    {
        buff[ret] = '\0';
        tmp = curr->content;
        curr->content = ft_strjoin(curr->content, buff);
    }
    free(tmp);
    if (ret < 0)
        return (-1);
    else
        return (0);    
}

int        ft_gnl(t_fdlist *curr, char **line, t_fdlist *start)
{
    char    *next;

    if (!(next = ft_strchr(curr->content, '\n')))
    {
        if (!*curr->content)
        {
            ft_cleanlist(start, curr);        
            free(*line);
            return (0);
        }
        *line = ft_strdup(curr->content);
        curr->content += ft_strlen(curr->content);
        return (1);
    }
    next++;
    *line = ft_strsub(curr->content, 0, next - curr->content - 1);
    curr->content = next;
    return (1);
}

int        get_next_line(const int fd, char **line)
{
    static t_fdlist        *start = NULL;
    t_fdlist            *curr;
    
    if (start)
        printf("curr: %s\n", start->content);
    else
        printf("none\n");

    if (!line || fd < 0)
        return (-1);
    if (!start)
        if ((!(start = (t_fdlist *)ft_memalloc(sizeof(*start)))) ||
        populate(start, fd) == -1)
            return (-1);
    curr = start;
    while (curr->descriptor != fd || !curr)
        if (!curr)
        {
            if ((!(curr = (t_fdlist *)ft_memalloc(sizeof(*curr)))) ||
            populate(curr, fd) == -1)
                return (-1);
        }
        else
            curr = curr->next;
    return (ft_gnl(curr, line, start));
}

int    main(int ac, char **av)
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
//        printf("ret: %d: %s\n", tst, str);
        free(str);
    }
//	system("leaks a.out")
    return (0);
}

/*

typedef struct		s_fdlist
{
	int				descriptor;
	char			*content;
	struct s_fdlist	*next;
}					t_fdlist;

*/