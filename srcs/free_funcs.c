/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 15:50:25 by ssentine          #+#    #+#             */
/*   Updated: 2021/01/23 15:50:26 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_list(t_list *lst)
{
	t_list *temp;

	while (lst != NULL)
	{
		temp = lst->next;
		free(lst);
		lst = NULL;
		lst = temp;
	}
}

void	free_scene(t_scene *scene)
{
	free_list(scene->cam_list);
	free_list(scene->light_list);
	free_list(scene->sphere_list);
	free_list(scene->plane_list);
	free_list(scene->square_list);
	free_list(scene->cylinder_list);
	free_list(scene->triangle_list);
}

void	free_array(char **array)
{
	int i;

	i = 0;
	while (array[i] != 0)
	{
		free(array[i]);
		array[i++] = NULL;
	}
	free(array);
	array = NULL;
}

int		correct_args(int ac, char **av, t_scene *scene)
{
	int rt;
	int save;
	int i;

	i = 0;
	if (ac == 1)
		return (0);
	while (av[1][i + 3] != '\0')
		i++;
	rt = (av[1][i] == '.' && av[1][i + 1] == 'r' && av[1][i + 2] == 't');
	if (ac == 2)
		return (rt);
	else if (ac == 3 && rt)
	{
		save = !ft_strcmp(av[2], "--save");
		scene->save = 1;
		return (save);
	}
	else
		return (0);
}
