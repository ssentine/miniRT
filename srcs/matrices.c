/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 18:33:30 by ssentine          #+#    #+#             */
/*   Updated: 2021/01/24 18:33:31 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

t_vec3		multiply_vec_matrix(t_vec3 v1, t_matrix44f m)
{
	t_vec3 result;
	double w;

	result.x = v1.x * m[0][0] + v1.y * m[1][0] + v1.z * m[2][0] + m[3][0];
	result.y = v1.x * m[0][1] + v1.y * m[1][1] + v1.z * m[2][1] + m[3][1];
	result.z = v1.x * m[0][2] + v1.y * m[1][2] + v1.z * m[2][2] + m[3][2];
	w = v1.x * m[0][3] + v1.y * m[1][3] + v1.z * m[2][3] + m[3][3];
	result.x = result.x / w;
	result.y = result.y / w;
	result.z = result.z / w;
	return (result);
}

t_vec3		multiply_dir_matrix(t_vec3 v1, t_matrix44f m)
{
	t_vec3 result;

	result.x = v1.x * m[0][0] + v1.y * m[1][0] + v1.z * m[2][0];
	result.y = v1.x * m[0][1] + v1.y * m[1][1] + v1.z * m[2][1];
	result.z = v1.x * m[0][2] + v1.y * m[1][2] + v1.z * m[2][2];
	return (result);
}

void		identity_matrix(double result[4][4])
{
	result[0][0] = 1;
	result[0][1] = 0;
	result[0][2] = 0;
	result[0][3] = 0;
	result[1][0] = 0;
	result[1][1] = 1;
	result[1][2] = 0;
	result[1][3] = 0;
	result[2][0] = 0;
	result[2][1] = 0;
	result[2][2] = 1;
	result[2][3] = 0;
	result[3][0] = 0;
	result[3][1] = 0;
	result[3][2] = 0;
	result[3][3] = 1;
}

void		create_cam_to_world_matrix(t_rt *mini_rt)
{
	t_vec3 x_vector;
	t_vec3 y_vector;
	t_vec3 z_vector;

	y_vector = new_vec3(0, 2, 0);
	z_vector = vec3_normalize(vec3_negative(mini_rt->current_cam->orientation));
	x_vector = vec3_normalize(vec3_cross_product(y_vector, z_vector));
	y_vector = vec3_normalize(vec3_cross_product(z_vector, x_vector));
	identity_matrix(mini_rt->cam_to_world);
	mini_rt->cam_to_world[0][0] = x_vector.x;
	mini_rt->cam_to_world[0][1] = x_vector.y;
	mini_rt->cam_to_world[0][2] = x_vector.z;
	mini_rt->cam_to_world[1][0] = y_vector.x;
	mini_rt->cam_to_world[1][1] = y_vector.y;
	mini_rt->cam_to_world[1][2] = y_vector.z;
	mini_rt->cam_to_world[2][0] = z_vector.x;
	mini_rt->cam_to_world[2][1] = z_vector.y;
	mini_rt->cam_to_world[2][2] = z_vector.z;
	mini_rt->cam_to_world[3][0] = mini_rt->current_cam->position.x;
	mini_rt->cam_to_world[3][1] = mini_rt->current_cam->position.y;
	mini_rt->cam_to_world[3][2] = mini_rt->current_cam->position.z;
}
