/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 18:33:30 by ssentine          #+#    #+#             */
/*   Updated: 2021/01/24 18:33:31 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "minirt_types.h"
# include "get_next_line.h"
# include "start_minirt.h"
# include "ft_math.h"
# include "key_hooks.h"
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>

void			parse_line(char *line, t_scene *scene);
void			handle_error(char *line, char *msg);
void			parse_resolution(char **array, t_scene *scene, char *line);
void			parse_amb_ligth(char **array, t_scene *scene, char *line);
void			add_cam(char **array, t_scene *scene, char *line);
void			add_ligth(char **array, t_scene *scene, char *line);
void			add_sphere(char **array, t_scene *scene, char *line);
void			add_plane(char **array, t_scene *scene, char *line);
void			add_square(char **array, t_scene *scene, char *line);
void			add_cylinder(char **array, t_scene *scene, char *line);
void			add_triangle(char **array, t_scene *scene, char *line);
void			validate_scene(t_scene *scene);
void			check_resolution(t_resolution *resolution);
void			check_cam(t_list *cam_list);
void			check_light(t_amb_light amb_light, t_list *light_list);
unsigned char	check_color(char *line, int nbr);
double			check_ratio(char *line, double ratio);
double			check_unsigned(char *line, double diameter);
double			check_normalized(char *line, double d);
void			check_zero_vec(char *line, t_vec3 v1);
int				check_fov(char *line, int fov);
void			ft_bzero(void *s, size_t n);
char			**ft_split(char const *s);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_atoi(const char *nptr);
double			ft_atof(char *str);
t_list			*ft_lstnew(void *content);
void			ft_lstadd_back(t_list **alst, t_list *new);
int				ft_lstsize(t_list *lst);
void			ft_lstiter(t_list *lst, void (*f)(void *));
char			*ft_strdup(const char *s1);
void			ft_lstclear(t_list **lst);
size_t			ft_strlen(const char *s);
void			*ft_calloc(size_t count, size_t size);
void			free_scene(t_scene *scene);
void			free_array(char **array);
void			free_list(t_list *lst);
int				correct_args(int ac, char **av, t_scene *scene);

#endif
