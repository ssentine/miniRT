/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 18:33:06 by ssentine          #+#    #+#             */
/*   Updated: 2021/01/24 18:33:08 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

t_vec3		new_vec3(double x, double y, double z)
{
	t_vec3 result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

t_vec3		vec3_add(t_vec3 v1, t_vec3 v2)
{
	t_vec3 result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_vec3		vec3_subtract(t_vec3 v1, t_vec3 v2)
{
	t_vec3 result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

t_vec3		vec3_multiply(t_vec3 v1, double n)
{
	t_vec3 result;

	result.x = v1.x * n;
	result.y = v1.y * n;
	result.z = v1.z * n;
	return (result);
}

t_vec3		vec3_multiply_two_vec(t_vec3 v1, t_vec3 v2)
{
	t_vec3 result;

	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;
	result.z = v1.z * v2.z;
	return (result);
}
