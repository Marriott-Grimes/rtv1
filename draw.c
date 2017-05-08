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

int		find_min(double dist[NUM], int len)
{
	int		ans;
	int		i;
	double	min;

	ans = -1;
	i = 0;
	min = 1000000.0;
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
	double	dist[NUM];
	int		i;

	i = 0;
	while (i < w->total)
	{
		dist[i] = intersection(base, ray, i, w);
		i++;
	}
	return (find_min(dist, w->total));
}

int		hit(t_vec base, t_vec ray, t_window *w)
{
	int		i;

	i = mini_hit(base, ray, w);
	if (i == -1)
		return (0);
	return (color(ray, i, w));
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
				hit((t_vec){0, 0, 0}, normalize(
					(t_vec){(x - WINWIDTH / 2.0) * 0.001,
						(WINHEIGHT / 2.0 - y) * 0.001, 1.0}), w);
			y++;
		}
		x++;
	}
	ft_putstr("100%%\n");
	mlx_put_image_to_window(w->mlx, w->win, w->buf, 0, 0);
}
