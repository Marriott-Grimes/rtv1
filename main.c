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

t_window	struct_init(int argc, char **argv)
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
	if (argc == 1)
		fd = open("scene1", O_RDONLY);
	else
		fd = open(argv[1], O_RDONLY);
	load_scene(fd, &wndow);
	return (wndow);
}

int			main(int argc, char **argv)
{
	t_window	wndow;

	wndow = struct_init(argc, argv);
	draw_frame(&wndow);
	mlx_key_hook(wndow.win, key_stuff, &wndow);
	mlx_loop(wndow.mlx);
	return (0);
}
