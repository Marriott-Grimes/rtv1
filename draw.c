/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrimes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 13:25:56 by mgrimes           #+#    #+#             */
/*   Updated: 2017/04/09 13:25:58 by mgrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float	quadratic_formula(t_vec v, t_vec p, float r)
{
	return (
	(
	dot(p, v) - sqrt(sq(dot(p, v)) - dot(v, v) * (dot(p,p) - r * r))
	) / dot(v, v)
	);
}

float	sphere_intersection(t_vec base, t_vec v, t_window *w)
{
	t_vec	p;
	float	dist;

	p = vec_add(w->a.pos, sc_mult(-1.0, base));
	dist = 0;
	if (sq(dot(p, v)) > dot(v, v) * (dot(p, p) - sq(w->a.radius)) + 0.01)
		dist = quadratic_formula(v, p, w->a.radius);
	// p = w->b.pos;
	// if (sq(dot(p, v)) > dot(v, v) * (dot(p, p) - sq(w->b.radius)) + 0.01)
	// {
	// 	if (dist == 0 || quadratic_formula(v, p, w->b.radius) < dist)
	// 		return ('b');
	// }
	// if (dist != 0)
	// 	return ('a');
	// return (0);
	return (dist);
}

int		sphere_color(t_vec v, t_window *w)
{
	int 		color;
	float		t;
	t_sphere	sphere;
	t_vec		N;
	t_vec		Lm;
	t_vec		Rm;

	// if (s == 'a')
	// 	sphere = w->a;
	// else
	// 	sphere = w->b;
	sphere = w->a;
	color = sphere.m.amb;
	t = quadratic_formula(v, sphere.pos, sphere.radius);
	N = vec_add(sc_mult(t, v), sc_mult(-1.0, sphere.pos));
	Lm = normalize(vec_add(w->light, sc_mult(-t, v)));
	Rm = vec_add(sc_mult(2.0 * dot(Lm, N), N), sc_mult(-1.0, Lm));
	if (dot(Lm, N) > 0.0)
		color += color_scale(sphere.m.diff, dot(Lm, N));
	color += color_scale(sphere.m.spec, pow(dot(Rm, normalize(v)), sphere.m.shine));
	return (color);
}

float	plane_intersection(t_vec v, t_window *w)
{

	if (v.y != 0 && w->b.pos.y / v.y > 0)
		return (w->b.pos.y / v.y);
	return (0);
}

int		plane_color(t_vec v, t_window *w)
{
	int		color;
	float	t;
	t_vec	N;
	t_vec	Lm;
	t_vec	Rm;

	color = w->b.m.amb;
	t = w->b.pos.y / v.y;
	N = (t_vec){0, 1.0, 0};
	Lm = normalize(vec_add(w->light, sc_mult(-t, v)));
	Rm = vec_add(sc_mult(2.0 * dot(Lm, N), N), sc_mult(-1.0, Lm));
	if (!sphere_intersection(sc_mult(t,v), Lm, w))
		color += color_scale(w->b.m.diff, dot(Lm, N));
	color += color_scale(w->b.m.spec, pow(dot(Rm, normalize(v)), w->b.m.shine));
	return (color);

}

int		hit(t_vec base, t_vec ray, t_window *w)
{
	int color;
	float dist;
	float temp;

	(void)base;
	color = 0;
	if (!plane_intersection(ray, w))
	{
		if (!sphere_intersection((t_vec){0, 0, 0}, ray, w))
			return (0);
		return (sphere_color(ray, w));
	}
	dist = plane_intersection(ray, w);
	temp = sphere_intersection((t_vec){0, 0, 0}, ray, w);
	if (temp == 0 || temp > dist)
		return (plane_color(ray, w));
	return (sphere_color(ray, w));
	// dist = sphere_intersection((t_vec){0, 0, 0}, ray, w);
	// if (dist == 0 || dist > plane_intersection(ray, w))
	// 	color = plane_color(ray, w);
	// else if (dist != 0)
	// 	color = sphere_color(ray, w);
	return (color);
}

// int		fire_ray(t_vec base, t_vec ray, t_window *w)
// {
// 	char	s;

// 	(void)base;
// 	if ((s = sphere_intersection(ray, w)))
// 		return (sphere_color(ray, s, w));
// 	return (0);
// }

void	draw_frame(t_window *w)
{
	int x;
	int y;
	int *image;

	image = (int *)mlx_get_data_addr(w->buf, &(w->bpp),
									&(w->bytewd), &(w->endian));
	x = 0;
	while (x < WINWIDTH)
	{
		y = 0;
		while (y < WINHEIGHT)
		{
			image[x + y * WINWIDTH] =
				hit((t_vec){0, 0, 0},
				(t_vec){(x - WINWIDTH / 2.0) * 0.001,
				(y - WINHEIGHT / 2.0) * 0.001, 1.0}, w);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(w->mlx, w->win, w->buf, 0, 0);
}
