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
#include <stdio.h>

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
	int i = -1;

	image = (int *)mlx_get_data_addr(w->buf, &(w->bpp),
									&(w->bytewd), &(w->endian));
	while (++i < 4)
	{
		printf("%f %f %f\n", w->a[i].pos.x, w->a[i].pos.y, w->a[i].pos.z);
		printf("%f %f %f\n", w->a[i].axis.x, w->a[i].axis.y, w->a[i].axis.z);
		printf("%f\n", w->a[i].radius);
		printf("%f %f %f\n", w->a[i].m.spec.r, w->a[i].m.spec.g, w->a[i].m.spec.b);
		printf("%f %f %f\n", w->a[i].m.diff.r, w->a[i].m.diff.g, w->a[i].m.diff.b);
		printf("%f %f %f\n", w->a[i].m.amb.r, w->a[i].m.amb.g, w->a[i].m.amb.b);
		printf("%d %d\n", w->a[i].m.shine, w->a[i].type);

	}
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
