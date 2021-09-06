/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 18:33:30 by ssentine          #+#    #+#             */
/*   Updated: 2021/01/24 18:33:31 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "start_minirt.h"

static void		intersect_ray_tr(t_hit *hit, t_triangle *tr, t_solve *solve)
{
	t_triangle_solve	t;

	t.ab = vec3_subtract(tr->b, tr->a);
	t.ac = vec3_subtract(tr->c, tr->a);
	t.p_vec = vec3_cross_product(hit->dir, t.ac);
	t.det = vec3_dot_product(t.ab, t.p_vec);
	if (fabs(t.det) < MY_EPSILON)
		return ;
	t.inv_det = 1 / t.det;
	t.t_vec = vec3_subtract(hit->orig, tr->a);
	t.u = vec3_dot_product(t.t_vec, t.p_vec) * t.inv_det;
	if (t.u < 0 || t.u > 1)
		return ;
	t.q_vec = vec3_cross_product(t.t_vec, t.ab);
	t.v = vec3_dot_product(hit->dir, t.q_vec) * t.inv_det;
	if (t.v < 0 || t.u + t.v > 1)
		return ;
	solve->x0 = vec3_dot_product(t.ac, t.q_vec) * t.inv_det;
	if (solve->x0 < 0)
		solve->x0 = INFINITY;
	solve->temp_color = tr->color;
	solve->temp_vector = vec3_normalize(vec3_cross_product(t.ab, t.ac));
}

void			trace_ray_triangle(t_hit *hit, t_scene *scene)
{
	t_solve		solve;
	t_list		*tmp_list;

	tmp_list = scene->triangle_list;
	while (tmp_list != NULL)
	{
		solve.x0 = INFINITY;
		solve.x1 = INFINITY;
		intersect_ray_tr(hit, tmp_list->content, &solve);
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
