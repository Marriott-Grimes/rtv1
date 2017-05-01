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

int		find_min(float dist[NUM], int len)
{
	int		ans;
	int		i;
	float	min;

	ans = -1;
	i = 0;
	min = 1000.0;
	while (i < len)
	{
		if (dist[i] > 0.0001 && dist[i] < min)
		{
			min = dist[i];
			ans = i;
		}
		i++;
	}
	return (ans);
}

int		mini_hit(t_vec base, t_vec ray, t_window *w)
{
	float	dist[NUM];
	int		i;

	i = 0;
	while (i < NUM)
	{
		dist[i] = intersection(base, ray, i, w);
		i++;
	}
	return (find_min(dist, NUM));
}

int		hit(t_vec base, t_vec ray, t_window *w)
{
	int		i;

	i = mini_hit(base, ray, w);
	if (i == -1)
		return (0);
	return (color(ray, i, w));
}

t_vec	compute_offset(int x, int y, t_window *w)
{
	t_vec hor;
	t_vec vert;

	hor = rotate('y', -PI / 2.0, w->camn);
	hor = normalize(proj(hor, (t_vec){0, 1.0, 0}));
	vert = cross(w->camn, hor);
	hor = sc_mult((x - WINWIDTH / 2.0) * 0.001, hor);
	vert = sc_mult((WINHEIGHT / 2.0 - y) * 0.001, vert);
	return (vec_add(hor, vert));
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
			image[x + y * WINWIDTH] =
				hit(w->campos,
				normalize(vec_add(compute_offset(x, y, w), w->camn)), w);
			y++;
		}
		x++;
	}
	ft_putstr("100%%\n");
	mlx_put_image_to_window(w->mlx, w->win, w->buf, 0, 0);
}
