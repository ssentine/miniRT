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

void		parse_resolution(char **array, t_scene *scene, char *line)
{
	if (array[3] == 0)
	{
		if (!scene->resolution.is_specified)
		{
			scene->resolution.x = ft_atof(array[1]);
			scene->resolution.y = ft_atof(array[2]);
			scene->resolution.is_specified = 1;
		}
		else
			handle_error(line, "Resolution is already specified\n\n");
	}
	else
		handle_error(line, "Incorrect number of parametrs\n\n");
}

void		parse_amb_ligth(char **array, t_scene *scene, char *line)
{
	float q;

	q = 255;
	if (array[5] == 0)
	{
		if (!scene->amb_light.is_specified)
		{
			scene->amb_light.ratio = check_ratio(line, ft_atof(array[1]));
			scene->amb_light.color.x = check_color(line, ft_atoi(array[2])) / q;
			scene->amb_light.color.y = check_color(line, ft_atoi(array[3])) / q;
			scene->amb_light.color.z = check_color(line, ft_atoi(array[4])) / q;
			scene->amb_light.is_specified = 1;
		}
		else
			handle_error(line, "Ambient ligth is already specified\n\n");
	}
	else
		handle_error(line, "Incorrect number of parametrs\n\n");
}

void		add_cam(char **array, t_scene *scene, char *line)
{
	t_cam	new_cam;
	t_cam	*cam_ptr;

	if (array[8] == 0)
	{
		new_cam.position.x = ft_atof(array[1]);
		new_cam.position.y = ft_atof(array[2]);
		new_cam.position.z = ft_atof(array[3]);
		new_cam.orientation.x = check_normalized(line, ft_atof(array[4]));
		new_cam.orientation.y = check_normalized(line, ft_atof(array[5]));
		new_cam.orientation.z = check_normalized(line, ft_atof(array[6]));
		check_zero_vec(line, new_cam.orientation);
		new_cam.fov = check_fov(line, ft_atoi(array[7]));
		cam_ptr = (t_cam *)ft_calloc(1, sizeof(t_cam));
		*cam_ptr = new_cam;
		ft_lstadd_back(&scene->cam_list, ft_lstnew(cam_ptr));
	}
	else
		handle_error(line, "Incorrect number of parametrs\n\n");
}

void		add_ligth(char **array, t_scene *scene, char *line)
{
	t_light	new_light;
	t_light	*light_ptr;

	if (array[8] == 0)
	{
		new_light.light_point.x = ft_atof(array[1]);
		new_light.light_point.y = ft_atof(array[2]);
		new_light.light_point.z = ft_atof(array[3]);
		new_light.ratio = check_ratio(line, ft_atof(array[4]));
		new_light.color.x = check_color(line, ft_atoi(array[5])) / (float)255;
		new_light.color.y = check_color(line, ft_atoi(array[6])) / (float)255;
		new_light.color.z = check_color(line, ft_atoi(array[7])) / (float)255;
		light_ptr = (t_light *)ft_calloc(1, sizeof(t_light));
		*light_ptr = new_light;
		ft_lstadd_back(&scene->light_list, ft_lstnew(light_ptr));
	}
	else
		handle_error(line, "Incorrect number of parametrs\n\n");
}

void		add_sphere(char **array, t_scene *scene, char *line)
{
	t_sphere	sphere;
	t_sphere	*sphere_ptr;

	if (array[8] == 0)
	{
		sphere.center.x = ft_atof(array[1]);
		sphere.center.y = ft_atof(array[2]);
		sphere.center.z = ft_atof(array[3]);
		sphere.radius = check_unsigned(line, ft_atof(array[4])) / 2;
		sphere.color.x = check_color(line, ft_atoi(array[5])) / (float)255;
		sphere.color.y = check_color(line, ft_atoi(array[6])) / (float)255;
		sphere.color.z = check_color(line, ft_atoi(array[7])) / (float)255;
		sphere_ptr = (t_sphere *)ft_calloc(1, sizeof(t_sphere));
		*sphere_ptr = sphere;
		ft_lstadd_back(&scene->sphere_list, ft_lstnew(sphere_ptr));
	}
	else
		handle_error(line, "Incorrect number of parametrs\n\n");
}
