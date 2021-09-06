/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 18:33:30 by ssentine          #+#    #+#             */
/*   Updated: 2021/01/24 18:33:31 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "start_minirt.h"

static void		intersect_ray_sphere(t_hit *hit, t_sphere *sp, t_solve *solve)
{
	t_discriminant d;

	d.oc = vec3_subtract(hit->orig, sp->center);
	d.a = vec3_dot_product(hit->dir, hit->dir);
	d.b = 2 * vec3_dot_product(d.oc, hit->dir);
	d.c = vec3_dot_product(d.oc, d.oc) - sp->radius * sp->radius;
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
	solve->temp_color = sp->color;
	solve->temp_vector = sp->center;
}

static double	find_closest(t_solve *solve, double closest)
{
	double temp;

	if (solve->x0 > solve->x1)
	{
		temp = solve->x0;
		solve->x0 = solve->x1;
		solve->x1 = temp;
	}
	if (solve->x0 < 0)
	{
		solve->x0 = solve->x1;
		if (solve->x0 < 0)
		{
			solve->x0 = INFINITY;
			solve->x1 = INFINITY;
		}
	}
	if (closest < solve->x0)
		return (closest);
	else
		return (solve->x0);
}

void			trace_ray_sphere(t_hit *hit, t_scene *scene)
{
	double		closest;
	t_solve		solve;
	t_list		*tmp_list;

	closest = INFINITY;
	tmp_list = scene->sphere_list;
	ft_bzero(&hit->color, sizeof(t_vec3));
	while (tmp_list != NULL)
	{
		intersect_ray_sphere(hit, tmp_list->content, &solve);
		closest = find_closest(&solve, closest);
		if (is_equal(closest, solve.x0))
		{
			hit->color = solve.temp_color;
			hit->p_hit = vec3_add(hit->orig, vec3_multiply(hit->dir, closest));
			hit->n_hit = vec3_normalize(vec3_subtract(hit->p_hit,
solve.temp_vector));
			hit->n_hit = vec3_normalize(vec3_multiply(hit->n_hit,
vec3_dot_product(hit->n_hit, vec3_negative(hit->dir))));
			hit->t = solve.x0;
		}
		tmp_list = tmp_list->next;
	}
}
