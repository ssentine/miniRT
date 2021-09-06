/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 16:00:15 by ssentine          #+#    #+#             */
/*   Updated: 2021/02/27 16:00:16 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_hooks.h"

int		key_hook(int keycode, t_scene *scene)
{
	if (keycode == KEY_ESC)
		ft_close(scene);
	else if (keycode == KEY_ENTER)
		change_cam(scene, &scene->mini_rt);
	else if (keycode == KEY_S)
		save_image(scene, "image.bmp", &scene->mini_rt, scene->resolution.x);
	return (0);
}

void	change_cam(t_scene *scene, t_rt *mini_rt)
{
	t_list		*tmp;
	int			count;

	count = 0;
	tmp = scene->cam_list;
	if (tmp->next != NULL)
	{
		while (tmp != NULL)
		{
			if (mini_rt->cam_number == count)
			{
				mini_rt->current_cam = tmp->content;
				mini_rt->cam_number++;
				break ;
			}
			tmp = tmp->next;
			count++;
		}
		if (count != 0 && tmp == NULL)
		{
			mini_rt->current_cam = scene->cam_list->content;
			mini_rt->cam_number = 1;
		}
		scene->image_changed = 0;
	}
}

int		ft_close(t_scene *scene)
{
	free_scene(scene);
	free(scene);
	exit(1);
	return (0);
}
