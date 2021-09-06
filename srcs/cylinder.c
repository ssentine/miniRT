/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 15:44:25 by ssentine          #+#    #+#             */
/*   Updated: 2021/02/27 15:44:28 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "start_minirt.h"

static int	point_in_height(t_hit *hit, t_cylinder *cy, double value)
{
	t_vec3 q;
	double dot;

	q = vec3_add(hit->orig, vec3_multiply(hit->dir, value));
	dot = vec3_dot_product(cy->orientation, vec3_subtract(q, cy->center));
	if (dot < 0 || dot > cy->height)
		return (0);
	return (1);
}

static void	check_height(t_hit *hit, t_cylinder *cylinder, t_solve *solve)
{
	double temp;

	if (solve->x0 > solve->x1)
	{
		temp = solve->x0;
		solve->x0 = solve->x1;
		solve->x1 = temp;
	}
	if (solve->x0 < 0 || !point_in_height(hit, cylinder, solve->x0))
	{
		solve->x0 = solve->x1;
		if (solve->x0 < 0 || !point_in_height(hit, cylinder, solve->x0))
			solve->x0 = INFINITY;
	}
}

static void	intersect_ray_cylinder(t_hit *hit, t_cylinder *cy, t_solve *solve)
{
	t_discriminant d;

	cy->orientation = vec3_normalize(cy->orientation);
	d.oc = vec3_subtract(hit->orig, cy->center);
	d.v_comp = vec3_subtract(hit->dir, vec3_project(cy->orientation, hit->dir));
	d.p_comp = vec3_subtract(d.oc, vec3_project(cy->orientation, d.oc));
	d.a = vec3_dot_product(d.v_comp, d.v_comp);
	d.b = 2 * vec3_dot_product(d.v_comp, d.p_comp);
	d.c = vec3_dot_product(d.p_comp, d.p_comp) - (cy->radius * cy->radius);
	d.d = d.b * d.b - 4 * d.a * d.c;
	solve->x1 = INFINITY;
	if (is_equal(d.d, 0))
		solve->x0 = -0.5 * d.b / d.a;
	else if (d.d < 0)
		solve->x0 = INFINITY;
	else
	{
		d.q = (d.b > 0) ? -0.5 * (d.b + sqrt(d.d)) : -0.5 * (d.b - sqrt(d.d));
		solve->x0 = d.q / d.a;
		solve->x1 = d.c / d.q;
	}
	solve->temp_color = cy->color;
	solve->temp_vector = cy->orientation;
	solve->temp_vector2 = cy->center;
	check_height(hit, cy, solve);
}

void		trace_ray_cylinder(t_hit *hit, t_scene *scene)
{
	t_solve		solve;
	t_list		*tmp_list;
	t_vec3		l_hit;

	tmp_list = scene->cylinder_list;
	while (tmp_list != NULL)
	{
		intersect_ray_cylinder(hit, tmp_list->content, &solve);
		if (hit->t > solve.x0)
		{
			hit->color = solve.temp_color;
			hit->p_hit = vec3_add(hit->orig, vec3_multiply(hit->dir, solve.x0));
			l_hit = vec3_subtract(hit->p_hit, solve.temp_vector2);
			hit->n_hit = vec3_normalize(vec3_subtract(l_hit,
vec3_multiply(solve.temp_vector, vec3_dot_product(solve.temp_vector, l_hit))));
			hit->n_hit = vec3_normalize(vec3_multiply(hit->n_hit,
			vec3_dot_product(hit->n_hit, vec3_negative(hit->dir))));
			hit->t = solve.x0;
		}
		tmp_list = tmp_list->next;
	}
}
