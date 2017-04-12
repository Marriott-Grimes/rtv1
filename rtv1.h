#ifndef RTVONE_H
# define RTVONE_H

# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "mlx.h"

# define WINWIDTH 1600
# define WINHEIGHT 1200

typedef	struct	s_vec
{
	float		x;
	float		y;
	float		z;
}				t_vec;

typedef	struct	s_material
{
	int			spec;
	int			diff;
	int			amb;
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
	t_vec		rot;
	t_material	m;
}				t_cylinder;

typedef	struct	s_plane
{
	t_vec		pos;
	t_vec		rot;
	t_material	m;
}				t_plane;

typedef	struct	s_light
{
	t_vec		pos;
	t_vec		dir;
}				t_light;

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
}				t_window;

void	draw_frame(t_window *win_ptr);
t_vec	vec_add(t_vec a, t_vec b);
t_vec	sc_mult(float a, t_vec v);
float	dot(t_vec a, t_vec b);
float	get_dist(t_vec a, t_vec b);
t_vec	normalize(t_vec v);
int		gradient(int startcolor, int endcolor, float i);
int		color_add(int a, int b);
int		color_scale(int color, float i);
float	sq(float a);

#endif