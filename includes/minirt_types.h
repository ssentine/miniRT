/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 18:33:30 by ssentine          #+#    #+#             */
/*   Updated: 2021/01/24 18:33:31 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_TYPES_H
# define MINIRT_TYPES_H

typedef struct		s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct		s_amb_light
{
	int				is_specified;
	double			ratio;
	t_vec3			color;
}					t_amb_light;

typedef struct		s_resolution
{
	int				is_specified;
	int				x;
	int				y;
}					t_resolution;

typedef struct		s_image
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_image;

typedef struct		s_cam
{
	t_vec3			position;
	t_vec3			orientation;
	int				fov;
}					t_cam;

typedef struct		s_light
{
	t_vec3			light_point;
	double			ratio;
	t_vec3			color;
}					t_light;

typedef struct		s_sphere
{
	t_vec3			center;
	double			radius;
	t_vec3			color;
}					t_sphere;

typedef struct		s_square
{
	t_vec3			center;
	t_vec3			orientation;
	double			side;
	t_vec3			color;
}					t_square;

typedef struct		s_plane
{
	t_vec3			center;
	t_vec3			orientation;
	t_vec3			color;
}					t_plane;

typedef struct		s_cylinder
{
	t_vec3			center;
	t_vec3			orientation;
	double			radius;
	double			height;
	t_vec3			color;
}					t_cylinder;

typedef struct		s_triangle
{
	t_vec3			a;
	t_vec3			b;
	t_vec3			c;
	t_vec3			color;
}					t_triangle;

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct		s_disriminant
{
	double			a;
	double			b;
	double			c;
	double			q;
	t_vec3			oc;
	t_vec3			v_comp;
	t_vec3			p_comp;
	double			d;
}					t_discriminant;

typedef struct		s_triangle_solve
{
	t_vec3			ab;
	t_vec3			ac;
	t_vec3			t_vec;
	t_vec3			p_vec;
	t_vec3			q_vec;
	float			det;
	float			inv_det;
	float			u;
	float			v;
}					t_triangle_solve;

typedef struct		s_split
{
	char			**t;
	int				i;
	int				j;
	int				k;
	int				words;
}					t_split;

typedef struct		s_solve
{
	double			x0;
	double			x1;
	t_vec3			temp_color;
	t_vec3			temp_vector;
	t_vec3			temp_vector2;
}					t_solve;

typedef struct		s_dir_light
{
	t_vec3			amb;
	t_vec3			dif;
	t_vec3			spec;
	t_vec3			result;
}					t_dir_light;

typedef struct		s_hit
{
	t_vec3			dir;
	t_vec3			orig;
	t_vec3			p_hit;
	t_vec3			n_hit;
	double			t;
	t_vec3			color;
	int				final_color;
}					t_hit;

typedef double		t_matrix44f[4][4];

typedef struct		s_rt
{
	void			*mlx_ptr;
	void			*mlx_window;
	t_cam			*current_cam;
	int				cam_number;
	t_image			image;
	t_matrix44f		cam_to_world;
}					t_rt;

typedef struct		s_scene
{
	t_resolution	resolution;
	t_amb_light		amb_light;
	t_list			*cam_list;
	t_list			*light_list;
	t_list			*sphere_list;
	t_list			*plane_list;
	t_list			*square_list;
	t_list			*cylinder_list;
	t_list			*triangle_list;
	t_rt			mini_rt;
	int				save;
	int				image_changed;
}					t_scene;

#endif
