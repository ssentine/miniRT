/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 18:33:30 by ssentine          #+#    #+#             */
/*   Updated: 2021/01/24 18:33:31 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double		check_ratio(char *line, double ratio)
{
	if (ratio < 0 || ratio > 1)
		handle_error(line, "Invalid ratio.\n\n");
	return (ratio);
}

double		check_unsigned(char *line, double d)
{
	if (d <= 0)
		handle_error(line, "Invalid side parameter.\n\n");
	return (d);
}

double		check_normalized(char *line, double d)
{
	if (d < -1 - MY_EPSILON || d > 1 + MY_EPSILON)
		handle_error(line, "Vector is not normalized.\n\n");
	return (d);
}

int			check_fov(char *line, int fov)
{
	if (fov < 0 || fov > 180)
		handle_error(line, "FOV is out of range.\n\n");
	return (fov);
}

void		check_zero_vec(char *line, t_vec3 v1)
{
	if (is_equal(v1.x, 0) && is_equal(v1.y, 0) && is_equal(v1.z, 0))
		handle_error(line, "Orientation vector is equal to zero.\n\n");
}
