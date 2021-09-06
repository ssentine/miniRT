/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 18:33:30 by ssentine          #+#    #+#             */
/*   Updated: 2021/01/24 18:33:31 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_plane(char **array, t_scene *scene, char *line)
{
	t_plane	plane;
	t_plane	*plane_ptr;

	if (array[10] == 0)
	{
		plane.center.x = ft_atof(array[1]);
		plane.center.y = ft_atof(array[2]);
		plane.center.z = ft_atof(array[3]);
		plane.orientation.x = check_normalized(line, ft_atof(array[4]));
		plane.orientation.y = check_normalized(line, ft_atof(array[5]));
		plane.orientation.z = check_normalized(line, ft_atof(array[6]));
		check_zero_vec(line, plane.orientation);
		plane.color.x = check_color(line, ft_atoi(array[7])) / (float)255;
		plane.color.y = check_color(line, ft_atoi(array[8])) / (float)255;
		plane.color.z = check_color(line, ft_atoi(array[9])) / (float)255;
		plane_ptr = (t_plane *)ft_calloc(1, sizeof(t_plane));
		*plane_ptr = plane;
		ft_lstadd_back(&scene->plane_list, ft_lstnew(plane_ptr));
	}
	else
		handle_error(line, "Incorrect number of parametrs\n\n");
}

void	add_square(char **array, t_scene *scene, char *line)
{
	t_square	square;
	t_square	*square_ptr;

	if (array[11] == 0)
	{
		square.center.x = ft_atof(array[1]);
		square.center.y = ft_atof(array[2]);
		square.center.z = ft_atof(array[3]);
		square.orientation.x = check_normalized(line, ft_atof(array[4]));
		square.orientation.y = check_normalized(line, ft_atof(array[5]));
		square.orientation.z = check_normalized(line, ft_atof(array[6]));
		check_zero_vec(line, square.orientation);
		square.side = check_unsigned(line, ft_atof(array[7])) / 2;
		square.color.x = check_color(line, ft_atoi(array[8])) / (float)255;
		square.color.y = check_color(line, ft_atoi(array[9])) / (float)255;
		square.color.z = check_color(line, ft_atoi(array[10])) / (float)255;
		square_ptr = (t_square *)ft_calloc(1, sizeof(t_square));
		*square_ptr = square;
		ft_lstadd_back(&scene->square_list, ft_lstnew(square_ptr));
	}
	else
		handle_error(line, "Incorrect number of parametrs\n\n");
}

void	add_cylinder(char **array, t_scene *scene, char *line)
{
	t_cylinder	cylinder;
	t_cylinder	*cylinder_ptr;

	if (array[12] == 0)
	{
		cylinder.center.x = ft_atof(array[1]);
		cylinder.center.y = ft_atof(array[2]);
		cylinder.center.z = ft_atof(array[3]);
		cylinder.orientation.x = check_normalized(line, ft_atof(array[4]));
		cylinder.orientation.y = check_normalized(line, ft_atof(array[5]));
		cylinder.orientation.z = check_normalized(line, ft_atof(array[6]));
		check_zero_vec(line, cylinder.orientation);
		cylinder.radius = check_unsigned(line, ft_atof(array[7])) / 2;
		cylinder.height = check_unsigned(line, ft_atof(array[8]));
		cylinder.color.x = check_color(line, ft_atoi(array[9])) / (float)255;
		cylinder.color.y = check_color(line, ft_atoi(array[10])) / (float)255;
		cylinder.color.z = check_color(line, ft_atoi(array[11])) / (float)255;
		cylinder_ptr = (t_cylinder *)ft_calloc(1, sizeof(t_cylinder));
		*cylinder_ptr = cylinder;
		ft_lstadd_back(&scene->cylinder_list, ft_lstnew(cylinder_ptr));
	}
	else
		handle_error(line, "Incorrect number of parametrs\n\n");
}

void	add_triangle(char **array, t_scene *scene, char *line)
{
	t_triangle	triangle;
	t_triangle	*triangle_ptr;

	if (array[13] == 0)
	{
		triangle.a.x = ft_atof(array[1]);
		triangle.a.y = ft_atof(array[2]);
		triangle.a.z = ft_atof(array[3]);
		triangle.b.x = ft_atof(array[4]);
		triangle.b.y = ft_atof(array[5]);
		triangle.b.z = ft_atof(array[6]);
		triangle.c.x = ft_atof(array[7]);
		triangle.c.y = ft_atof(array[8]);
		triangle.c.z = ft_atof(array[9]);
		triangle.color.x = check_color(line, ft_atoi(array[10])) / (float)255;
		triangle.color.y = check_color(line, ft_atoi(array[11])) / (float)255;
		triangle.color.z = check_color(line, ft_atoi(array[12])) / (float)255;
		triangle_ptr = (t_triangle *)ft_calloc(1, sizeof(t_triangle));
		*triangle_ptr = triangle;
		ft_lstadd_back(&scene->triangle_list, ft_lstnew(triangle_ptr));
	}
	else
		handle_error(line, "Incorrect number of parametrs\n\n");
}
