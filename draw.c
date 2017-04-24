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

int		find_min(float	dist[NUM], int len)
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

float	intersection(t_vec base, t_vec ray, int i, t_window *w)
{
	if (w->a[i].type == 0)
		return (sphere_intersection(base, ray, i, w));
	if (w->a[i].type == 1)
		return (plane_intersection(base, ray, i, w));
	if (w->a[i].type == 2)
		return (cyl_intersection(base, ray, i, w));
	else
		return (cone_intersection(base, ray, i, w));
}

int		color(t_vec ray, int i, t_window *w)
{
	if (w->a[i].type == 0)
		return (sphere_color(ray, i, w));
	if (w->a[i].type == 1)
		return (plane_color(ray, i, w));
	if (w->a[i].type == 2)
		return (cyl_color(ray, i, w));
	else
		return (cone_color(ray, i, w));
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
	// float	dist[NUM];
	int		i;

	// i = 0;
	// while (i < NUM)
	// {
	// 	dist[i] = intersection(base, ray, i, w);
	// 	i++;
	// }
	// i = find_min(dist, NUM);
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
	int counter = 1;

	image = (int *)mlx_get_data_addr(w->buf, &(w->bpp),
									&(w->bytewd), &(w->endian));
	x = 0;
	while (x < WINWIDTH)
	{
		y = 0;
		while (y < WINHEIGHT)
		{
			if (x + y * WINWIDTH > counter * WINHEIGHT * WINWIDTH / 100)
			{
				printf("%d%%\n", counter);
				counter++;
			}
			image[x + y * WINWIDTH] =
				hit((t_vec){0, 0, 0},
				normalize((t_vec){(x - WINWIDTH / 2.0) * 0.001,
				(y - WINHEIGHT / 2.0) * 0.001, 1.0}), w);
			y++;
		}
		x++;
	}
	printf("100%%\n");
	mlx_put_image_to_window(w->mlx, w->win, w->buf, 0, 0);
}
