/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 18:33:30 by ssentine          #+#    #+#             */
/*   Updated: 2021/01/24 18:33:31 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "start_minirt.h"

static void		intersect_ray_square2(t_hit *hit, t_square *sq, t_solve *solve)
{
	t_vec3 local_x;
	t_vec3 local_z;
	t_vec3 local_y;
	t_vec3 l_hit;

	local_y = vec3_normalize(sq->orientation);
	local_z = align_vector(local_y);
	local_x = vec3_normalize(vec3_cross_product(local_z, local_y));
	local_z = vec3_normalize(vec3_cross_product(local_y, local_x));
	l_hit = vec3_add(hit->orig, vec3_multiply(hit->dir, solve->x0));
	l_hit = vec3_subtract(l_hit, sq->center);
	if (fabs(vec3_dot_product(local_x, l_hit)) > sq->side ||
fabs(vec3_dot_product(local_z, l_hit)) > sq->side)
		solve->x0 = INFINITY;
}

static void		intersect_ray_square(t_hit *hit, t_square *sq, t_solve *solve)
{
	float		denom;
	t_vec3		p0l0;

	sq->orientation = vec3_normalize(sq->orientation);
	denom = vec3_dot_product(sq->orientation, hit->dir);
	if (fabs(denom) > MY_EPSILON)
	{
		p0l0 = vec3_subtract(sq->center, hit->orig);
		solve->x0 = vec3_dot_product(p0l0, sq->orientation) / denom;
		if (solve->x0 <= 0)
			solve->x0 = INFINITY;
		else
			intersect_ray_square2(hit, sq, solve);
	}
	else
		solve->x0 = INFINITY;
	if (solve->x0 <= 0)
		solve->x0 = INFINITY;
	solve->temp_color = sq->color;
	solve->temp_vector = sq->orientation;
}

void			trace_ray_square(t_hit *hit, t_scene *scene)
{
	t_solve		solve;
	t_list		*tmp_list;

	tmp_list = scene->square_list;
	while (tmp_list != NULL)
	{
		intersect_ray_square(hit, tmp_list->content, &solve);
		if (solve.x0 < hit->t)
		{
			hit->color = solve.temp_color;
			hit->n_hit = solve.temp_vector;
			hit->p_hit = vec3_add(hit->orig, vec3_multiply(hit->dir, solve.x0));
			hit->n_hit = vec3_normalize(vec3_multiply(hit->n_hit,
vec3_dot_product(hit->n_hit, vec3_negative(hit->dir))));
			hit->t = solve.x0;
		}
		tmp_list = tmp_list->next;
	}
}
