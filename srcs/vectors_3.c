/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 18:33:06 by ssentine          #+#    #+#             */
/*   Updated: 2021/01/24 18:33:08 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

t_vec3		vec3_divide(t_vec3 v1, double n)
{
	t_vec3 result;

	result.x = v1.x / n;
	result.y = v1.y / n;
	result.z = v1.z / n;
	return (result);
}

t_vec3		align_vector(t_vec3 v1)
{
	t_vec3 result;

	result = vec3_cross_product(new_vec3(0, 1, 0), v1);
	if (result.x == 0 && result.y == 0 && result.z == 0)
		result = vec3_cross_product(new_vec3(0, 0, 1), v1);
	return (vec3_normalize(result));
}

t_vec3		vec3_project(t_vec3 v1, t_vec3 v2)
{
	return (vec3_multiply(v1, vec3_dot_product(v1, v2)));
}

int			is_equal(double a, double b)
{
	return (fabs(a - b) <= MY_EPSILON);
}
