/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:48:36 by ssentine          #+#    #+#             */
/*   Updated: 2021/02/27 17:48:38 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "start_minirt.h"

void			trace_ray(t_hit *hit, t_scene *scene)
{
	hit->t = INFINITY;
	trace_ray_sphere(hit, scene);
	trace_ray_plane(hit, scene);
	trace_ray_square(hit, scene);
	trace_ray_triangle(hit, scene);
	trace_ray_cylinder(hit, scene);
	apply_light(hit, scene);
	hit->color.x = (hit->color.x > 1) ? 1 : hit->color.x;
	hit->color.y = (hit->color.y > 1) ? 1 : hit->color.y;
	hit->color.z = (hit->color.z > 1) ? 1 : hit->color.z;
	hit->final_color = create_trgb(0, hit->color.x * 255,
	hit->color.y * 255, hit->color.z * 255);
}

static t_vec3	dif(t_light *light, t_hit *hit, t_vec3 light_vec)
{
	double q;

	q = fmax(vec3_dot_product(hit->n_hit, light_vec), 0.0);
	return (vec3_multiply(light->color, q));
}

static t_vec3	spec(t_light *light, t_hit *hit, t_vec3 light_vec)
{
	t_vec3 reflect_dir;
	double spec;

	reflect_dir = vec3_subtract(light_vec, vec3_multiply(hit->n_hit,
	vec3_dot_product(light_vec, hit->n_hit) * 2));
	spec = pow(fmax(vec3_dot_product(hit->dir, reflect_dir), 0.0), 32);
	return (vec3_multiply(light->color, light->ratio * spec));
}

static int		in_shadow(t_light *light, t_scene *scene, t_hit *hit)
{
	t_hit	new_hit;
	double	max_dis;

	new_hit.t = INFINITY;
	new_hit.orig = vec3_add(hit->p_hit, vec3_multiply(hit->n_hit, 0.00001));
	new_hit.dir = vec3_subtract(light->light_point, hit->p_hit);
	max_dis = vec3_len(new_hit.dir);
	new_hit.dir = vec3_normalize(new_hit.dir);
	trace_ray_sphere(&new_hit, scene);
	if (new_hit.t != INFINITY && max_dis > new_hit.t)
		return (1);
	trace_ray_plane(&new_hit, scene);
	if (new_hit.t != INFINITY && max_dis > new_hit.t)
		return (1);
	trace_ray_square(&new_hit, scene);
	if (new_hit.t != INFINITY && max_dis > new_hit.t)
		return (1);
	trace_ray_triangle(&new_hit, scene);
	if (new_hit.t != INFINITY && max_dis > new_hit.t)
		return (1);
	trace_ray_cylinder(&new_hit, scene);
	if (new_hit.t != INFINITY && max_dis > new_hit.t)
		return (1);
	return (0);
}

void			apply_light(t_hit *hit, t_scene *scene)
{
	t_list		*tmp_list;
	t_dir_light	all;
	t_vec3		result;
	t_vec3		light_vec;
	t_light		*cur;

	ft_bzero(&all, sizeof(t_dir_light));
	all.amb = vec3_multiply(scene->amb_light.color, scene->amb_light.ratio);
	tmp_list = scene->light_list;
	while (tmp_list != NULL)
	{
		cur = tmp_list->content;
		light_vec = vec3_normalize(vec3_subtract(cur->light_point, hit->p_hit));
		if (!signbit(vec3_dot_product(hit->n_hit, light_vec)))
		{
			if (!in_shadow(tmp_list->content, scene, hit))
			{
				all.dif = vec3_add(all.dif, dif(cur, hit, light_vec));
				all.spec = vec3_add(all.spec, spec(cur, hit, light_vec));
			}
		}
		tmp_list = tmp_list->next;
	}
	result = vec3_add(vec3_add(all.amb, all.dif), all.spec);
	hit->color = vec3_multiply_two_vec(hit->color, result);
}
