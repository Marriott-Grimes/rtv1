/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrimes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 17:28:01 by mgrimes           #+#    #+#             */
/*   Updated: 2017/04/14 17:28:03 by mgrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTVONE_H
# define RTVONE_H

# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "mlx.h"
# include "libft/libft.h"

# define WINWIDTH 1600
# define WINHEIGHT 1200
# define PI 3.14159

typedef	struct	s_vec
{
	float		x;
	float		y;
	float		z;
}				t_vec;

typedef	struct	s_color
{
	float		r;
	float		g;
	float		b;
}				t_color;

typedef	struct	s_material
{
	t_color		spec;
	t_color		diff;
	t_color		amb;
	int			shine;
}				t_material;

typedef	struct	s_sphere
{
	t_vec		pos;
	float		radius;
	t_material	m;
}				t_sphere;

typedef	struct	s_cylinder
{
	t_vec		pos;
	t_vec		axis;
	float		radius;
	t_material	m;
}				t_cylinder;

typedef	struct	s_cone
{
	t_vec		pos;
	t_vec		axis;
	float		theta;
	t_material	m;
}				t_cone;

typedef	struct	s_plane
{
	t_vec		pos;
	t_vec		n;
	t_material	m;
}				t_plane;

// typedef	struct	s_scene
// {
// 	int			ltnum;
// 	t_vec		*lights;
// 	int			sphnum;
// 	t_sphere	*spheres;
// 	int			cylnum;
// 	t_cylinder	*cyls;
// 	int			cnum;
// 	t_cone		*cones;
// 	int			plnum;
// 	t_plane		*planes;
// }				t_scene;

typedef	struct	s_window
{
	void		*mlx;
	void		*win;
	void		*buf;
	int			wwd;
	int			wht;
	int			bpp;
	int			bytewd;
	int			endian;
	t_vec		light;
	t_sphere	a;
	t_plane		b;
	t_cylinder	c;
	t_cone		d;
}				t_window;

void	draw_frame(t_window *win_ptr);
t_vec	vec_add(t_vec a, t_vec b);
t_vec	sc_mult(float a, t_vec v);
float	dot(t_vec a, t_vec b);
float	get_dist(t_vec a, t_vec b);
t_vec	normalize(t_vec v);
t_color	color_add(t_color a, t_color b);
t_color	color_scale(t_color c, float i);
int		color_convert(t_color c);
float	sq(float a);
float	quadratic_formula(float a, float b, float c);
float	sphere_intersection(t_vec base, t_vec v, t_window *w);
int		sphere_color(t_vec v, t_window *w);
float	plane_intersection(t_vec v, t_window *w);
int		plane_color(t_vec v, t_window *w);
float	cyl_intersection(t_vec base, t_vec v, t_window *w);
int		cyl_color(t_vec v, t_window *w);
float	cone_intersection(t_vec base, t_vec v, t_window *w);
int		cone_color(t_vec v, t_window *w);
int		hit(t_vec base, t_vec ray, t_window *w);
t_vec	proj(t_vec v, t_vec perp);

#endif
