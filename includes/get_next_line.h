/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 18:59:03 by ssentine          #+#    #+#             */
/*   Updated: 2021/02/27 18:59:06 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

typedef struct		s_buff
{
	char			ptr[32];
	int				len;
	int				start;
}					t_buff;

typedef struct		s_line
{
	char			*ptr;
	int				len;
	int				max_len;
}					t_line;
int					get_next_line(int fd, char **line);

#endif
