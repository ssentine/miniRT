/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minirt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 18:33:30 by ssentine          #+#    #+#             */
/*   Updated: 2021/01/24 18:33:31 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "start_minirt.h"

static int		update_img(t_scene *scene)
{
	if (scene->image_changed == 0)
	{
		render(scene, scene->resolution.x, scene->resolution.y,
		&scene->mini_rt);
		mlx_put_image_to_window(scene->mini_rt.mlx_ptr,
		scene->mini_rt.mlx_window, scene->mini_rt.image.img, 0, 0);
		scene->image_changed = 1;
	}
	return (1);
}

void			start_minirt(t_scene *scene)
{
	int	sizex;
	int	sizey;

	scene->mini_rt.mlx_ptr = mlx_init();
	mlx_get_screen_size(scene->mini_rt.mlx_ptr, &sizex, &sizey);
	if (scene->resolution.x > sizex)
		scene->resolution.x = sizex;
	if (scene->resolution.y > sizey)
		scene->resolution.y = sizey;
	create_img(scene, &scene->mini_rt);
	if (scene->save == 1)
	{
		save_image(scene, "image.bmp", &scene->mini_rt, scene->resolution.x);
		ft_close(scene);
	}
	scene->mini_rt.mlx_window = mlx_new_window(scene->mini_rt.mlx_ptr,
	scene->resolution.x, scene->resolution.y, "miniRT");
	mlx_loop_hook(scene->mini_rt.mlx_ptr, update_img, scene);
	mlx_key_hook(scene->mini_rt.mlx_window, key_hook, scene);
	mlx_hook(scene->mini_rt.mlx_window, 17, 1L << 0, ft_close, scene);
	mlx_loop(scene->mini_rt.mlx_ptr);
}

void			create_img(t_scene *scene, t_rt *mini_rt)
{
	t_image		img;
	t_list		*tmp;

	tmp = scene->cam_list;
	if (tmp != NULL)
	{
		mini_rt->current_cam = tmp->content;
		mini_rt->cam_number = 1;
		img.img = mlx_new_image(mini_rt->mlx_ptr, scene->resolution.x,
		scene->resolution.y);
		if (img.img == NULL)
			handle_error("", "Fail to create an image\n\n");
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
		&img.line_length, &img.endian);
		if (img.addr == NULL)
			handle_error("", "Fail to get an image data\n\n");
		mini_rt->image = img;
		render(scene, scene->resolution.x, scene->resolution.y,
		&scene->mini_rt);
	}
}

void			render(t_scene *scene, double w, double height, t_rt *mini_rt)
{
	unsigned int	i;
	unsigned int	j;
	double			scale;
	t_vec3			ray;
	t_hit			hit;

	j = -1;
	create_cam_to_world_matrix(mini_rt);
	hit.orig = mini_rt->current_cam->position;
	scale = tan((mini_rt->current_cam->fov * 0.5) * (M_PI / 180));
	while (++j < height)
	{
		i = -1;
		while (++i < w)
		{
			ray.x = (2 * ((i + 0.5) / w) - 1) * (w / height) * scale;
			ray.y = (1 - 2 * ((j + 0.5) / height)) * scale;
			ray.z = -1;
			hit.dir = vec3_normalize(ray);
			hit.dir = vec3_normalize(multiply_dir_matrix(hit.dir,
			mini_rt->cam_to_world));
			trace_ray(&hit, scene);
			my_mlx_pixel_put(&mini_rt->image, i, j, hit.final_color);
		}
	}
}
