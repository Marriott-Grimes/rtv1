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

int		find_min(float	dist[4], int len)
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

int		hit(t_vec base, t_vec ray, t_window *w)
{
	float	dist[4];
	int		index;

	dist[0] = sphere_intersection(base, ray, w);
	dist[1] = plane_intersection(ray, w);
	dist[2] = cyl_intersection(base, ray, w);
	dist[3] = cone_intersection(base, ray, w);
	index = find_min(dist, 4);
	if (index == 0)
		return (sphere_color(ray, w));
	if (index == 1)
		return (plane_color(ray, w));
	if (index == 2)
		return (cyl_color(ray, w));
	if (index == 3)
		return (cone_color(ray, w));
	else
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
			image[x + y * WINWIDTH] =
				hit((t_vec){0, 0, 0},
				normalize((t_vec){(x - WINWIDTH / 2.0) * 0.001,
				(y - WINHEIGHT / 2.0) * 0.001, 1.0}), w);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(w->mlx, w->win, w->buf, 0, 0);
}
