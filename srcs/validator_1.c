/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 18:33:30 by ssentine          #+#    #+#             */
/*   Updated: 2021/01/24 18:33:31 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void			validate_scene(t_scene *scene)
{
	check_resolution(&scene->resolution);
	check_light(scene->amb_light, scene->light_list);
	check_cam(scene->cam_list);
}

void			check_resolution(t_resolution *res)
{
	if (res->x <= 1 || res->y <= 1)
		handle_error("", "Invalid resolution.\n\n");
}

void			check_light(t_amb_light amb_light, t_list *light_list)
{
	if (amb_light.is_specified == 0 && ft_lstsize(light_list) == 0)
		handle_error("", "There is no light at all, add one.\n\n");
}

void			check_cam(t_list *cam_list)
{
	if (ft_lstsize(cam_list) == 0)
		handle_error("", "There is no camera, add one.\n\n");
}

unsigned char	check_color(char *line, int nbr)
{
	if (nbr < 0 || nbr > 255)
		handle_error(line, "Color is out of range\n\n");
	return (nbr);
}
