/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 18:33:30 by ssentine          #+#    #+#             */
/*   Updated: 2021/01/24 18:33:31 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "start_minirt.h"

static void		intersect_ray_plane(t_hit *hit, t_plane *plane, t_solve *solve)
{
	float	denom;
	float	denom2;
	t_vec3	p0l0;

	denom = vec3_dot_product(plane->orientation, hit->dir);
	denom2 = vec3_dot_product(vec3_negative(plane->orientation), hit->dir);
	if (denom > MY_EPSILON || denom2 > MY_EPSILON)
	{
		p0l0 = vec3_subtract(plane->center, hit->orig);
		solve->x0 = vec3_dot_product(p0l0, plane->orientation) / denom;
		if (solve->x0 < 0)
			solve->x0 = INFINITY;
	}
	else
		solve->x0 = INFINITY;
	if (solve->x0 < 0)
		solve->x0 = INFINITY;
	solve->temp_color = plane->color;
	solve->temp_vector = plane->orientation;
}

void			trace_ray_plane(t_hit *hit, t_scene *scene)
{
	t_list		*tmp_list;
	t_solve		solve;

	tmp_list = scene->plane_list;
	while (tmp_list != NULL)
	{
		intersect_ray_plane(hit, tmp_list->content, &solve);
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
