/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 18:33:06 by ssentine          #+#    #+#             */
/*   Updated: 2021/01/24 18:33:08 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

double		vec3_dot_product(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec3		vec3_cross_product(t_vec3 v1, t_vec3 v2)
{
	t_vec3 result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return (result);
}

double		vec3_len(t_vec3 v1)
{
	return (sqrt(fabs(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z)));
}

t_vec3		vec3_normalize(t_vec3 v1)
{
	t_vec3 result;
	double len;

	len = vec3_len(v1);
	result.x = v1.x / len;
	result.y = v1.y / len;
	result.z = v1.z / len;
	return (result);
}

t_vec3		vec3_negative(t_vec3 v1)
{
	t_vec3 result;

	result.x = -v1.x;
	result.y = -v1.y;
	result.z = -v1.z;
	return (result);
}
