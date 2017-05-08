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

#ifndef RTV1_H
# define RTV1_H

# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "mlx.h"
# include "libft/libft.h"

# define WINWIDTH 1600
# define WINHEIGHT 1200
# define PI 3.14159
# define NUM 7

typedef	struct	s_vec
{
	double		x;
	double		y;
	double		z;
}				t_vec;

typedef	struct	s_color
{
	double		r;
	double		g;
	double		b;
}				t_color;

typedef	struct	s_material
{
	t_color		spec;
	t_color		diff;
	t_color		amb;
	int			shine;
}				t_material;

typedef	struct	s_conevars
{
	t_vec		p;
	t_vec		u;
	t_vec		q;
	double		sn;
	double		a;
	double		b;
	double		c;
}				t_conevars;

typedef	struct	s_cvars
{
	t_vec		n;
	t_vec		lm;
	t_vec		rm;
}				t_cvars;

typedef	struct	s_shape
{
	t_vec		pos;
	t_vec		axis;
	double		radius;
	t_material	m;
	int			type:3;
}				t_shape;

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
	t_vec		campos;
	t_vec		camn;
	t_vec		light;
	t_shape		a[7];
	int			total;
}				t_window;

void			draw_frame(t_window *win_ptr);
t_vec			vec_add(t_vec a, t_vec b);
t_vec			sc_mult(double a, t_vec v);
double			dot(t_vec a, t_vec b);
t_vec			cross(t_vec a, t_vec b);
t_vec			normalize(t_vec v);
t_vec			proj(t_vec v, t_vec perp);
t_color			color_add(t_color a, t_color b);
t_color			color_scale(t_color c, double i);
int				color_convert(t_color c);
double			sq(double a);
double			quadratic_formula(double a, double b, double c);
double			intersection(t_vec base, t_vec ray, int i, t_window *w);
double			sphere_intersection(
								t_vec base, t_vec v, int i, t_window *w);
double			plane_intersection(t_vec base, t_vec v, int i, t_window *w);
double			cyl_intersection(t_vec base, t_vec v, int i, t_window *w);
double			cone_intersection(t_vec base, t_vec v, int i, t_window *w);
int				sphere_color(t_vec v, int i, t_window *w);
int				plane_color(t_vec v, int i, t_window *w);
int				cyl_color(t_vec v, int i, t_window *w);
int				cone_color(t_vec v, int i, t_window *w);
int				hit(t_vec base, t_vec ray, t_window *w);
int				mini_hit(t_vec base, t_vec ray, t_window *w);
double			ft_atof(char *str);
void			load_scene(int fd, t_window *w);
t_vec			cyl_normal(double t, t_vec v, int i, t_window *w);
t_vec			cone_normal(double t, t_vec v, int i, t_window *w);
int				color(t_vec v, int i, t_window *w);
t_vec			read_vector(char *line);
char			*next_car(char *s, char c);
t_vec			rotate(char ax, double a, t_vec v);
void			rot_tr(t_window *w);
int				key_stuff(int keycode, void *param);
t_vec			read_vector(char *line);
t_color			read_color(char *line);

#endif
