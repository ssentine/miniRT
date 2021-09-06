/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 18:33:30 by ssentine          #+#    #+#             */
/*   Updated: 2021/01/24 18:33:31 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H

# include "minirt.h"

# define MY_EPSILON 1e-7

t_vec3		new_vec3(double x, double y, double z);
t_vec3		vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3		vec3_subtract(t_vec3 v1, t_vec3 v2);
t_vec3		vec3_multiply(t_vec3 v1, double n);
t_vec3		vec3_multiply_two_vec(t_vec3 v1, t_vec3 v2);
t_vec3		vec3_divide(t_vec3 v1, double n);
double		vec3_dot_product(t_vec3 v1, t_vec3 v2);
t_vec3		vec3_cross_product(t_vec3 v1, t_vec3 v2);
double		vec3_len(t_vec3 v1);
t_vec3		vec3_normalize(t_vec3 v1);
t_vec3		vec3_negative(t_vec3 v1);
int			vec3_equal(t_vec3 v1, t_vec3 v2);
t_vec3		align_vector(t_vec3 v1);
t_vec3		vec3_project(t_vec3 v1, t_vec3 v2);
t_vec3		multiply_dir_matrix(t_vec3 v1, t_matrix44f matrix);
t_vec3		multiply_vec_matrix(t_vec3 v1, t_matrix44f matrix);
void		identity_matrix(double result[4][4]);
void		create_cam_to_world_matrix(t_rt *mini_rt);
int			is_equal(double a, double b);

#endif
