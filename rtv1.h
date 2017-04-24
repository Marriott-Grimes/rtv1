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

typedef	struct		s_vec
{
	float			x;
	float			y;
	float			z;
}					t_vec;

typedef	struct		s_color
{
	float			r;
	float			g;
	float			b;
}					t_color;

typedef	struct		s_material
{
	t_color			spec;
	t_color			diff;
	t_color			amb;
	int				shine;
}					t_material;

typedef	struct		s_shape
{
	t_vec			pos;
	t_vec			axis;
	float			radius;
	t_material		m;
	unsigned int	type:2;
}					t_shape;

typedef	struct		s_window
{
	void			*mlx;
	void			*win;
	void			*buf;
	int				wwd;
	int				wht;
	int				bpp;
	int				bytewd;
	int				endian;
	t_vec			light;
	t_shape			a[7];
}					t_window;

void				draw_frame(t_window *win_ptr);
t_vec				vec_add(t_vec a, t_vec b);
t_vec				sc_mult(float a, t_vec v);
float				dot(t_vec a, t_vec b);
float				get_dist(t_vec a, t_vec b);
t_vec				normalize(t_vec v);
t_vec				proj(t_vec v, t_vec perp);
t_color				color_add(t_color a, t_color b);
t_color				color_scale(t_color c, float i);
int					color_convert(t_color c);
float				sq(float a);
float				quadratic_formula(float a, float b, float c);
float				sphere_intersection(t_vec base, t_vec v, int i, t_window *w);
float				plane_intersection(t_vec base, t_vec v, int i, t_window *w);
float				cyl_intersection(t_vec base, t_vec v, int i, t_window *w);
float				cone_intersection(t_vec base, t_vec v, int i, t_window *w);
int					sphere_color(t_vec v, int i, t_window *w);
int					plane_color(t_vec v, int i, t_window *w);
int					cyl_color(t_vec v, int i, t_window *w);
int					cone_color(t_vec v, int i, t_window *w);
int					hit(t_vec base, t_vec ray, t_window *w);
int					mini_hit(t_vec base, t_vec ray, t_window *w);
float				ft_atof(char *str);
void				load_scene(int fd, t_window *w);

#endif
