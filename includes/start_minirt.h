/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minirt.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 18:33:30 by ssentine          #+#    #+#             */
/*   Updated: 2021/01/24 18:33:31 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef START_MINIRT_H
# define START_MINIRT_H

# include "minirt.h"
# include <mlx.h>

void	start_minirt(t_scene *scene);
void	create_img(t_scene *scene, t_rt *mini_rt);
void	change_cam(t_scene *scene, t_rt *mini_rt);
void	render(t_scene *scene, double width, double height, t_rt *mini_rt);
void	save_image(t_scene *scene, char *fn, t_rt *mini_rt, int width);
void	trace_ray(t_hit *hit, t_scene *scene);
void	trace_ray_sphere(t_hit *hit, t_scene *scene);
void	trace_ray_plane(t_hit *hit, t_scene *scene);
void	trace_ray_square(t_hit *hit, t_scene *scene);
void	trace_ray_triangle(t_hit *hit, t_scene *scene);
void	trace_ray_cylinder(t_hit *hit, t_scene *scene);
int		create_trgb(int t, int r, int g, int b);
void	apply_light(t_hit *hit, t_scene *scene);
void	my_mlx_pixel_put(t_image *data, int x, int y, int color);

#endif
