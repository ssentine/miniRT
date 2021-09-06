/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 18:33:30 by ssentine          #+#    #+#             */
/*   Updated: 2021/01/24 18:33:31 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int				g_error;

static void		parse(char *line, t_scene *scene)
{
	if (line[0] != '\n' && line[0] != '\0')
		parse_line(line, scene);
	free(line);
	line = NULL;
}

static void		continue_parsing(t_scene *scene)
{
	if (!g_error)
		validate_scene(scene);
	if (!g_error)
		start_minirt(scene);
	else
	{
		free_scene(scene);
		free(scene);
	}
}

int				main(int ac, char **av)
{
	t_scene		*scene;
	int			result;
	char		*line;
	int			fd;

	g_error = 0;
	scene = (t_scene*)ft_calloc(1, sizeof(t_scene));
	if (correct_args(ac, av, scene))
	{
		if ((fd = open(av[1], O_RDONLY)) < 0)
			handle_error("", "Fail to open the file\n\n");
		line = NULL;
		while ((result = get_next_line(fd, &line)) > 0)
			parse(line, scene);
		parse(line, scene);
		close(fd);
	}
	else
		handle_error("", "Incorrect arguments\n\n");
	continue_parsing(scene);
	return (0);
}

void			parse_line(char *line, t_scene *scene)
{
	char **array;

	array = ft_split(line);
	if (ft_strcmp(array[0], "R") == 0)
		parse_resolution(array, scene, line);
	else if (ft_strcmp(array[0], "A") == 0)
		parse_amb_ligth(array, scene, line);
	else if (ft_strcmp(array[0], "c") == 0)
		add_cam(array, scene, line);
	else if (ft_strcmp(array[0], "l") == 0)
		add_ligth(array, scene, line);
	else if (ft_strcmp(array[0], "sp") == 0)
		add_sphere(array, scene, line);
	else if (ft_strcmp(array[0], "pl") == 0)
		add_plane(array, scene, line);
	else if (ft_strcmp(array[0], "sq") == 0)
		add_square(array, scene, line);
	else if (ft_strcmp(array[0], "cy") == 0)
		add_cylinder(array, scene, line);
	else if (ft_strcmp(array[0], "tr") == 0)
		add_triangle(array, scene, line);
	else
		handle_error(line, "There is no such a figure\n\n");
	free_array(array);
}

void			handle_error(char *line, char *message)
{
	g_error++;
	if (line[0] != '\0')
	{
		write(2, "Error while parsing at the line:\n", 33);
		write(2, &*line, ft_strlen(line));
		write(2, "\n", 1);
	}
	write(2, &*message, ft_strlen(message));
}
