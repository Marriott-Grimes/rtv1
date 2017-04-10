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

float	sq(float a)
{
	return (a * a);
}

char	sphere_intersection(t_vec v, t_window *w)
{
	t_vec p;

	p = w->sphere.pos;
	if (sq(dot(p, v)) >= dot(v, v) * (dot(p, p) - sq(w->sphere.radius)))
		return (1);
	return (0);
}

float	quadratic_formula(t_vec v, t_vec p, float r)
{
	return (
	(dot(p, v) - sqrt(sq(dot(p, v)) - dot(v, v) * (dot(p,p) - r * r))) / dot(v, v)
	);
}

int		sphere_color(t_vec v, t_window *w)
{
	int 	color;
	float	t;
	t_vec	p;
	t_vec	N;
	t_vec	Lm;
	t_vec	Rm;

	p = w->sphere.pos;
	color = 0x00240024;
	t = quadratic_formula(v, w->sphere.pos, w->sphere.radius);
	N = vec_add(sc_mult(t, v), (t_vec){0, 0, -2.0});
	Lm = normalize(vec_add(w->light, sc_mult(-t, v)));
	Rm = vec_add(sc_mult(2.0 * dot(Lm, N), N), sc_mult(-1.0, Lm));
	color += color_scale(0x00400040, dot(Lm, N));
	color += color_scale(0x00803070, pow(dot(Rm, normalize(v)), 10));
	return (color);
}

int		fire_ray(int x, int y, t_window *w)
{
	t_vec	ray;

	ray = (t_vec){(x - WINWIDTH / 2.0) * 0.001, (y - WINHEIGHT / 2.0) * 0.001, 1.0};
	if (sphere_intersection(ray, w))
		return (sphere_color(ray, w));
	return (0);
}

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
			image[x + y * WINWIDTH] = fire_ray(x, y, w);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(w->mlx, w->win, w->buf, 0, 0);
}
