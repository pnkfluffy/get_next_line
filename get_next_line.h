/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 16:24:50 by jfelty            #+#    #+#             */
/*   Updated: 2019/08/27 17:56:33 by jfelty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>

//DELETE
# include <stdio.h>

# define BUFF_SIZE 4
# define MAX_FD 256

int		get_next_line(int const fd, char **line);
int		ft_gnl(char **str, char **line, int fd);

#endif