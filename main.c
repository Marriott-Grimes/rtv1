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

t_window	struct_init(void)
{
	t_window	wndow;
	int			fd;

	wndow.mlx = mlx_init();
	wndow.win = mlx_new_window(wndow.mlx, WINWIDTH, WINHEIGHT, "rtv1");
	wndow.buf = mlx_new_image(wndow.mlx, WINWIDTH, WINHEIGHT);
	wndow.wwd = WINWIDTH;
	wndow.wht = WINHEIGHT;
	wndow.bpp = 32;
	wndow.endian = 0;
	wndow.bytewd = 4 * WINWIDTH;
	fd = open("scene1", O_RDONLY);
	load_scene(fd, &wndow);
	// wndow.light = (t_vec){-0.5, -1.0, 0};
	// wndow.a[0] = (t_shape){(t_vec){-0.5, 0, 2.0}, (t_vec){0, 0, 0}, 0.15, //sphere
	// 	(t_material){
	// 		(t_color){0.5, 0.2, 0.4},
	// 		(t_color){0.25, 0.0, 0.25},
	// 		(t_color){0.125, 0.0, 0.125},
	// 		10}, 0};
	// wndow.a[1] = (t_shape){(t_vec){0, 1.0, 0}, (t_vec){0.0, 1.0, 0}, 0.0, //plane
	// 	(t_material){
	// 		(t_color){0.12, 0.18, 0.18},
	// 		(t_color){0.05, 0.5, 0.55},
	// 		(t_color){0.02, 0.12, 0.18},
	// 		16}, 1};
	// wndow.a[2] = (t_shape){(t_vec){2.0, 0.75, 3.0}, //cyl
	// 		normalize((t_vec){1.0, 1.0, 0.1}), 0.25,
	// 		(t_material){
	// 			(t_color){0.0, 0.18, 0.08},
	// 			(t_color){0.02, 0.5, 0.05},
	// 			(t_color){0.01, 0.32, 0.03},
	// 			6}, 2};
	// wndow.a[3] = (t_shape){(t_vec){0.0, 0.2, 3.5}, //cone
	// 		normalize((t_vec){1.0, 1.0, 0.0}), 0.7,
	// 		(t_material){
	// 			(t_color){0.3, 0.04, 0.01},
	// 			(t_color){0.2, 0.05, 0.05},
	// 			(t_color){0.21, 0.12, 0.03},
	// 			10}, 3};
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
		w->light.y = w->light.y + 1.0;
	if (keycode == 13)
		w->light.y = w->light.y - 1.0;
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
