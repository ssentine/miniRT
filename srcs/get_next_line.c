/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 15:57:31 by ssentine          #+#    #+#             */
/*   Updated: 2021/02/27 15:57:34 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		is_newline(t_buff *buff)
{
	if (buff->start < buff->len)
		return (buff->ptr[buff->start] == '\n');
	return (0);
}

static int		reallocate_line(t_line *line, int size)
{
	int		new_max_len;
	char	*new_ptr;
	int		i;

	new_max_len = line->max_len ? line->max_len : 32;
	while (new_max_len < size)
		new_max_len *= 2;
	new_ptr = (char *)malloc(new_max_len + 1);
	if (new_ptr)
	{
		i = -1;
		while (++i < (int)line->len)
			new_ptr[i] = line->ptr[i];
		if (line->ptr)
			free(line->ptr);
		line->ptr = new_ptr;
		line->max_len = new_max_len;
		line->ptr[line->len] = '\0';
	}
	return (new_ptr != NULL);
}

static int		add_line(t_line *line, t_buff *buff)
{
	int		len;
	int		is_read;
	int		new_line_len;
	char	*new_line_ptr;

	is_read = 1;
	if (buff->start <= buff->len)
	{
		new_line_ptr = buff->ptr + buff->start;
		new_line_len = buff->len - buff->start;
		len = 0;
		while (len < new_line_len && new_line_ptr[len] != '\n')
			len++;
		if (!line->max_len || line->max_len - line->len < len)
			is_read = reallocate_line(line, line->len + len);
		if (is_read)
		{
			len = 0;
			while (len < new_line_len && new_line_ptr[len] != '\n')
				line->ptr[line->len++] = new_line_ptr[len++];
			line->ptr[line->len] = '\0';
			buff->start += len;
		}
	}
	return (is_read);
}

static int		read_line(t_line *line, t_buff *buff, int fd)
{
	int result;

	line->len = 0;
	result = add_line(line, buff);
	while (result > 0 && !is_newline(buff))
	{
		result = read(fd, buff->ptr, 32);
		if (result > 0)
		{
			buff->start = 0;
			buff->len = result;
			result = add_line(line, buff);
		}
	}
	if (is_newline(buff))
	{
		if (!result && line->len > 0)
			result = 1;
		buff->start++;
	}
	return (result);
}

int				get_next_line(int fd, char **line)
{
	static t_buff	buff;
	t_line			new_line;
	int				result;

	new_line.max_len = 0;
	new_line.ptr = NULL;
	result = read_line(&new_line, &buff, fd);
	*line = 0;
	if (result >= 0)
		*line = new_line.ptr;
	else if (new_line.ptr)
		free(new_line.ptr);
	return (result);
}
