/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrimes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 13:26:22 by mgrimes           #+#    #+#             */
/*   Updated: 2017/04/09 13:26:24 by mgrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_sphere	make_sphere(void)
{
	t_sphere s;

	s.pos = (t_vec){0, 0, 2.0};
	s.radius = 1.0;
	return (s);
}

t_window	struct_init(void)
{
	t_window	wndow;

	wndow.mlx = mlx_init();
	wndow.win = mlx_new_window(wndow.mlx, WINWIDTH, WINHEIGHT, "rtv1");
	wndow.buf = mlx_new_image(wndow.mlx, WINWIDTH, WINHEIGHT);
	wndow.wwd = WINWIDTH;
	wndow.wht = WINHEIGHT;
	wndow.bpp = 32;
	wndow.endian = 0;
	wndow.bytewd = 4 * WINWIDTH;
	wndow.light = (t_vec){-0.5, -1.0, 0};
	wndow.sphere = make_sphere();
	return (wndow);
}

int	key_stuff(int keycode, void *param)
{
	t_window *w;

	w = (t_window *)param;
	if (keycode == 53)
		exit(0);
	if (keycode == 0)
		w->light.x = w->light.x - 1.0;
	if (keycode == 2)
		w->light.x = w->light.x + 1.0;
	if (keycode == 1)
		w->light.y = w->light.y - 1.0;
	if (keycode == 13)
		w->light.y = w->light.y + 1.0;
	draw_frame(w);
	return (0);
}


int			main()
{
	t_window	wndow;

	wndow = struct_init();
	draw_frame(&wndow);
	mlx_key_hook(wndow.win, key_stuff, &wndow);
	mlx_loop(wndow.mlx);
	return (0);
}