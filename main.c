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

t_sphere	make_sphere(t_vec v, float r, t_material mat)
{
	t_sphere s;

	s.pos = v;
	s.radius = r;
	s.m = mat;
	return (s);
}

t_plane	make_plane(t_vec v, t_vec n, t_material mat)
{
	t_plane s;

	s.pos = v;
	s.n = n;
	s.m = mat;
	return (s);
}

// t_scene		make_scene(t_scene s)
// {
// 	s.ltnum = 1;
// 	s.sphnum = 1;
// 	s.cylnum = 0;
// 	s.cnum = 0;
// 	s.plnum = 1;
// 	s.lights = (t_vec *)malloc(sizeof(t_vec) * s.ltnum);
// 	s.spheres = (t_sphere *)malloc(sizeof(t_sphere) * s.sphnum);
// 	s.cyls = NULL;
// 	s.cones = NULL;
// 	s.planes = (t_plane *)malloc(sizeof(t_plane) * s.plnum);
// 	s->light = (t_vec){-0.5, -1.0, 0};
// 	s->spheres = make_sphere((t_vec){-0.5, 0, 2.0}, 0.75,
// 		(t_material){
// 			(t_color){0.5, 0.2, 0.4},
// 			(t_color){0.25, 0.0, 0.25},
// 			(t_color){0.125, 0.0, 0.125},
// 			10});
// 	s->planes = make_plane((t_vec){0, 1.0, 0}, (t_vec){0, 1.0, 0},
// 		(t_material){
// 			(t_color){0.12, 0.18, 0.18},
// 			(t_color){0.05, 0.5, 0.55},
// 			(t_color){0.02, 0.12, 0.18},
// 			16});
// 	return (s);
// }

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
	wndow.a = make_sphere((t_vec){-0.5, 0, 2.0}, 0.15,
		(t_material){
			(t_color){0.5, 0.2, 0.4},
			(t_color){0.25, 0.0, 0.25},
			(t_color){0.125, 0.0, 0.125},
			10});
	wndow.b = make_plane((t_vec){0, 1.0, 0}, (t_vec){0.0, 1.0, 0},
		(t_material){
			(t_color){0.12, 0.18, 0.18},
			(t_color){0.05, 0.5, 0.55},
			(t_color){0.02, 0.12, 0.18},
			16});
	wndow.c = (t_cylinder){(t_vec){2.0, 0.75, 3.0},
			normalize((t_vec){1.0, 1.0, 0.1}), 0.25,
			(t_material){
				(t_color){0.0, 0.18, 0.08},
				(t_color){0.02, 0.5, 0.05},
				(t_color){0.01, 0.32, 0.03},
				6}};
	wndow.d = (t_cone){(t_vec){0.0, 0.2, 3.5},
			normalize((t_vec){1.0, 1.0, 0.0}), 0.7,
			(t_material){
				(t_color){0.3, 0.04, 0.01},
				(t_color){0.2, 0.05, 0.05},
				(t_color){0.21, 0.12, 0.03},
				10}};
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
