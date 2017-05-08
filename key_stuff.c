/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrimes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 14:07:40 by mgrimes           #+#    #+#             */
/*   Updated: 2017/05/01 14:07:41 by mgrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	rotate_all(char ax, double rad, t_window *w)
{
	int i;

	i = 0;
	w->light = vec_add(w->light, (t_vec){0, 0, -2.0});
	w->light = rotate(ax, rad, w->light);
	w->light = vec_add(w->light, (t_vec){0, 0, 2.0});
	while (i < w->total)
	{
		w->a[i].pos = vec_add(w->a[i].pos, (t_vec){0, 0, -2.0});
		w->a[i].pos = rotate(ax, rad, w->a[i].pos);
		w->a[i].pos = vec_add(w->a[i].pos, (t_vec){0, 0, 2.0});
		w->a[i].axis = rotate(ax, rad, w->a[i].axis);
		i++;
	}
}

void	translate_all(t_vec v, t_window *w)
{
	int i;

	i = 0;
	w->light = vec_add(w->light, v);
	while (i < w->total)
	{
		w->a[i].pos = vec_add(w->a[i].pos, v);
		i++;
	}
}

void	move_cam(int keycode, t_window *w)
{
	if (keycode == 123)
		rotate_all('y', PI / 6.0, w);
	if (keycode == 124)
		rotate_all('y', -PI / 6.0, w);
	if (keycode == 125)
		translate_all((t_vec){0, 1.0, 0}, w);
	if (keycode == 126)
		translate_all((t_vec){0, -1.0, 0}, w);
}

int		key_stuff(int keycode, void *param)
{
	t_window	*w;

	w = (t_window *)param;
	if (keycode == 53)
		exit(0);
	if (keycode == 15 || keycode == 17)
		rot_tr(w);
	if (keycode == 0)
		w->light.x = w->light.x - 1.0;
	if (keycode == 2)
		w->light.x = w->light.x + 1.0;
	if (keycode == 1)
		w->light.y = w->light.y - 1.0;
	if (keycode == 13)
		w->light.y = w->light.y + 1.0;
	if (123 <= keycode && keycode <= 126)
		move_cam(keycode, w);
	draw_frame(w);
	return (0);
}
